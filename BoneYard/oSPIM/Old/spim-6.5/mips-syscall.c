/* SPIM S20 MIPS simulator.
   Execute SPIM syscalls, both in simulator and bare mode.
   Execute MIPS syscalls in bare mode, when running on MIPS systems.

   Copyright (C) 1990-2000 by James Larus (larus@cs.wisc.edu).
   ALL RIGHTS RESERVED.

   Improved by Emin Gun Sirer.
   Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)

   SPIM is distributed under the following conditions:

     You may make copies of SPIM for your own use and modify those copies.

     All copies of SPIM must retain my name and copyright notice.

     You may not sell SPIM or distributed SPIM in conjunction with a
     commerical product or service without the expressed written consent of
     James Larus.

   THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE. */


/* $Header: /Software/SPIM/SPIM/Old/spim-6.5/mips-syscall.c 1     1/02/05 8:03p Larus $ */


#include <stdio.h>
#include <sys/types.h>

#ifdef sgi
#define _BSD_SIGNALS
#endif
#include <signal.h>

#ifdef DJGPP
#define SIGBUS SIGUSR1
#elif defined(_MSC_VER)
#define SIGBUS SIGSEGV
#endif

#ifdef RS
/* This is problem on HP Snakes, which define RS in syscall.h */
#undef RS
#endif

#if (mips && dec)
#include <limits.h>
#include <sys/syscall.h>
#endif

#ifdef WIN32
#include <io.h>
#endif

#include "spim.h"
#include "inst.h"
#include "mem.h"
#include "reg.h"
#include "sym-tbl.h"
#include "spim-syscall.h"
#include "mips-syscall.h"

#ifndef WIN32
/* Imported variables: */
extern int errno;
#endif

/* Imported functions: */

#ifdef __STDC__
extern int close (int);
extern int dup (int);
extern int select ();
#else
extern int close ();
extern int dup ();
extern int select ();
#endif


/* Local functions: */

#ifdef __STDC__
static void do_sigreturn (mem_addr sigptr);
static int reverse_fds (int fd);
static void setup_signal_stack (void);
static int unixsyscall (void);
#else
static void do_sigreturn ();
static int reverse_fds ();
static void setup_signal_stack ();
static int unixsyscall ();
#endif

#ifndef OPEN_MAX
#define OPEN_MAX 32
#endif

#ifndef NSIG
#define NSIG 128
#endif

/* Local variables: */

static int prog_sigmask = 0;	/* Copy of sigmask passed to system */

#if (mips && dec)
static mem_addr exception_address[NSIG]; /* trampoline addresses for */
					 /* each signal handler */

static struct sigvec sighandler[NSIG]; /* Map to program handlers */
#endif

static int prog_fds[OPEN_MAX];	/* Map from program fds to simulator fds */

static int fds_initialized = 0;	/* FD map initialized? */


#define REG_ERR 7



/* Table describing arguments to syscalls. */

typedef struct
{
  int syscall_num;
  int syscall_type;
  int arg0;
  int arg1;
  int arg2;
  int arg3;
  int arg4;
  char *syscall_name;
} syscall_desc;

enum {BAD_SYSCALL, UNIX_SYSCALL, SPC_SYSCALL};

enum {NO_ARG, INT_ARG, ADDR_ARG, STR_ARG, FD_ARG};  /* Type of argument */

static syscall_desc syscall_table[] =
{
#if (mips && dec)
  {SYS_syscall, SPC_SYSCALL, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG,
     "syscall"},
  {SYS_exit, SPC_SYSCALL, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "exit"},
  {SYS_fork, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "fork"},
  {SYS_read, UNIX_SYSCALL, FD_ARG, ADDR_ARG, INT_ARG, NO_ARG, NO_ARG, "read"},
  {SYS_write, UNIX_SYSCALL, FD_ARG, STR_ARG, INT_ARG, NO_ARG, NO_ARG, "write"},
  {SYS_open, SPC_SYSCALL, STR_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, "open"},
  {SYS_close, SPC_SYSCALL, FD_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "close"},
  {7, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_creat, SPC_SYSCALL, STR_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, "creat"},
  {SYS_link, UNIX_SYSCALL, STR_ARG, STR_ARG, NO_ARG, NO_ARG, NO_ARG, "link"},
  {SYS_unlink, UNIX_SYSCALL, STR_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "unlink"},
  {SYS_execv, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "execv"},
  {SYS_chdir, UNIX_SYSCALL, STR_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "chdir"},
  {13, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_mknod, UNIX_SYSCALL, STR_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG,
     "mknod"},
  {SYS_chmod, UNIX_SYSCALL, STR_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, "chmod"},
  {SYS_chown, UNIX_SYSCALL, STR_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG,
     "chown"},
  {SYS_brk, SPC_SYSCALL, ADDR_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "brk"},
  {18, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_lseek, UNIX_SYSCALL, FD_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, "lseek"},
  {SYS_getpid, UNIX_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "getpid"},
  {SYS_mount, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "mount"},
  {SYS_umount, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "umount"},
  {23, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_getuid, UNIX_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "getuid"},
  {25, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_ptrace, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "ptrace"},
  {27, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {28, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {29, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {30, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {31, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {32, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_access, UNIX_SYSCALL, STR_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG,
     "access"},
  {34, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {35, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_sync, UNIX_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "sync"},
  {SYS_kill, UNIX_SYSCALL, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, "kill"},
  {SYS_stat, UNIX_SYSCALL, STR_ARG, ADDR_ARG, NO_ARG, NO_ARG, NO_ARG, "stat"},
  {39, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_lstat, UNIX_SYSCALL, STR_ARG, ADDR_ARG, NO_ARG, NO_ARG, NO_ARG,
     "lstat"},
  {SYS_dup, SPC_SYSCALL, FD_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "dup"},
  {SYS_pipe, UNIX_SYSCALL, ADDR_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "pipe"},
  {43, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_profil, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "profil"},
  {45, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {46, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_getgid, UNIX_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "getgid"},
  {48, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {49, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {50, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_acct, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "acct"},
  {52, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {53, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_ioctl, UNIX_SYSCALL, FD_ARG, INT_ARG, ADDR_ARG, NO_ARG, NO_ARG,
     "ioctl"},
  {SYS_reboot, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "reboot"},
  {56, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_symlink, UNIX_SYSCALL, STR_ARG, STR_ARG, NO_ARG, NO_ARG, NO_ARG,
     "symlink"},
  {SYS_readlink, UNIX_SYSCALL, ADDR_ARG, ADDR_ARG, INT_ARG, NO_ARG, NO_ARG,
     "readlink"},
  {SYS_execve, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "execve"},
  {SYS_umask, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "umask"},
  {SYS_chroot, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "chroot"},
  {SYS_fstat, UNIX_SYSCALL, FD_ARG, ADDR_ARG, NO_ARG, NO_ARG, NO_ARG, "fstat"},
  {63, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_getpagesize, UNIX_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getpagesize"},
  {SYS_mremap, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "mremap"},
  {SYS_vfork, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "vfork"},
  {67, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {68, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_sbrk, SPC_SYSCALL, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "sbrk"},
  {SYS_sstk, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "sstk"},
  {SYS_mmap, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "mmap"},
  {SYS_vadvise, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "vadvise"},
  {SYS_munmap, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "munmap"},
  {SYS_mprotect, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "mprotect"},
  {SYS_madvise, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "madvise"},
  {SYS_vhangup, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "vhangup"},
  {77, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_mincore, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "mincore"},
  {SYS_getgroups, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getgroups"},
  {SYS_setgroups, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setgroups"},
  {SYS_getpgrp, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getpgrp"},
  {SYS_setpgrp, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setpgrp"},
  {SYS_setitimer, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setitimer"},
  {SYS_wait3, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "wait3"},
  {SYS_swapon, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "swapon"},
  {SYS_getitimer, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getitimer"},
  {SYS_gethostname, UNIX_SYSCALL, STR_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG,
     "gethostname"},
  {SYS_sethostname, UNIX_SYSCALL, STR_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sethostname"},
  {SYS_getdtablesize, UNIX_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getdtablesize"},
  {SYS_dup2, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "dup2"},
  {SYS_getdopt, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getdopt"},
  {SYS_fcntl, UNIX_SYSCALL, FD_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, "fcntl"},
  {SYS_select, SPC_SYSCALL, INT_ARG, ADDR_ARG, ADDR_ARG, ADDR_ARG, ADDR_ARG,
     "select"},
  {SYS_setdopt, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setdopt"},
  {SYS_fsync, UNIX_SYSCALL, FD_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "fsync"},
  {SYS_setpriority, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setpriority"},
  {SYS_socket, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "socket"},
  {SYS_connect, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "connect"},
  {SYS_accept, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "accept"},
  {SYS_getpriority, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getpriority"},
  {SYS_send, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "send"},
  {SYS_recv, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "recv"},
  {SYS_sigreturn, SPC_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sigreturn"},
  {SYS_bind, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "bind"},
  {SYS_setsockopt, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setsockopt"},
  {SYS_listen, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "listen"},
  {107, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_sigvec, SPC_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "sigvec"},
  {SYS_sigblock, SPC_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sigblock"},
  {SYS_sigsetmask, SPC_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sigsetmask"},
  {SYS_sigpause, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sigpause"},
  {SYS_sigstack, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sigstack"},
  {SYS_recvmsg, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "recvmsg"},
  {SYS_sendmsg, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sendmsg"},
  {115, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_gettimeofday, UNIX_SYSCALL, ADDR_ARG, ADDR_ARG, NO_ARG, NO_ARG, NO_ARG,
     "gettimeofday"},
  {SYS_getrusage, UNIX_SYSCALL, INT_ARG, ADDR_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getrusage"},
  {SYS_getsockopt, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getsockopt"},
  {119, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_readv, UNIX_SYSCALL, FD_ARG, ADDR_ARG, INT_ARG, NO_ARG, NO_ARG,
     "readv"},
  {SYS_writev, UNIX_SYSCALL, FD_ARG, ADDR_ARG, INT_ARG, NO_ARG, NO_ARG,
     "writev"},
  {SYS_settimeofday, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "settimeofday"},
  {SYS_fchown, UNIX_SYSCALL, FD_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG,
     "fchown"},
  {SYS_fchmod, UNIX_SYSCALL, FD_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG,
     "fchmod"},
  {SYS_recvfrom, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "recvfrom"},
  {SYS_setreuid, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setreuid"},
  {SYS_setregid, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setregid"},
  {SYS_rename, UNIX_SYSCALL, STR_ARG, STR_ARG, NO_ARG, NO_ARG, NO_ARG,
     "rename"},
  {SYS_truncate, UNIX_SYSCALL, STR_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG,
     "truncate"},
  {SYS_ftruncate, UNIX_SYSCALL, FD_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG,
     "ftruncate"},
  {SYS_flock, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "flock"},
  {132, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_sendto, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "sendto"},
  {SYS_shutdown, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "shutdown"},
  {SYS_socketpair, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "socketpair"},
  {SYS_mkdir, UNIX_SYSCALL, STR_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, "mkdir"},
  {SYS_rmdir, UNIX_SYSCALL, STR_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "rmdir"},
  {SYS_utimes, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "utimes"},
  {SYS_sigcleanup, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sigcleanup"},
  {SYS_adjtime, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "adjtime"},
  {SYS_getpeername, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getpeername"},
  {SYS_gethostid, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "gethostid"},
  {SYS_sethostid, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "sethostid"},
  {SYS_getrlimit, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getrlimit"},
  {SYS_setrlimit, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setrlimit"},
  {SYS_killpg, UNIX_SYSCALL, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG,
     "killpg"},
  {147, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_setquota, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "setquota"},
  {SYS_quota, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, "quota"},
  {SYS_getsockname, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "getsockname"},
  {SYS_sysmips, SPC_SYSCALL, INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG,
     "sysmips"},
  {SYS_cacheflush, SPC_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "cacheflush"},
  {SYS_cachectl, SPC_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "cachectl"},
  {154, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, ""},
  {SYS_atomic_op, BAD_SYSCALL, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG,
     "atomic_op"},
#else
  {0}
#endif
};


#define MAX_SYSCALL	(sizeof(syscall_table)/ sizeof(syscall_table[0]))


static int syscall_usage[MAX_SYSCALL]; /* Track system calls */

#define SYSCALL_ARG(REGOFF, ARG, REG)					\
  ((syscall_table[R[REGOFF]].ARG == ADDR_ARG) ?				\
     (R[REG] == 0 ? (void*)NULL : MEM_ADDRESS(R[REG])) :		\
   (syscall_table[R[REGOFF]].ARG == STR_ARG) ? MEM_ADDRESS(R[REG])  :	\
   (((syscall_table[R[REGOFF]].ARG == FD_ARG)				\
     && (R[REG] < OPEN_MAX) && (R[REG] >= 0)))  ? (void*)prog_fds[R[REG]] : (void*)R[REG])

#define SYSCALL_COUNT(SYSCALL)						\
  if (SYSCALL < MAX_SYSCALL && SYSCALL >= 0) syscall_usage[SYSCALL]++;



/* Decides which syscall to execute or simulate.  Returns zero upon
   exit syscall and non-zero to continue execution. */

#ifdef __STDC__
int
do_syscall (void)
#else
int
do_syscall ()
#endif
{
  SYSCALL_COUNT(R[REG_V0]);
  if (source_file)
    {
      /* Syscalls for the source-language version of SPIM.  These are
	 easier to use than the real syscall and are portable to non-MIPS
	 (non-Unix?) operating systems. */

      switch (R[REG_V0])
	{
	case PRINT_INT_SYSCALL:
	  write_output (console_out, "%d", R[REG_A0]);
	  break;

	case PRINT_FLOAT_SYSCALL:
	  {
	    float val = FPR_S (REG_FA0);

	    write_output (console_out, "%.18f", val);
	    break;
	  }

	case PRINT_DOUBLE_SYSCALL:
	  write_output (console_out, "%.18g", FPR[REG_FA0/2]);
	  break;

	case PRINT_STRING_SYSCALL:
	  write_output (console_out, "%s", MEM_ADDRESS (R[REG_A0]));
	  break;

	case READ_INT_SYSCALL:
	  {
	    static char str [256];

	    read_input (str, 256);
	    R[REG_RES] = atol (str);
	    break;
	  }

	case READ_FLOAT_SYSCALL:
	  {
	    static char str [256];

	    read_input (str, 256);
	    FGR [REG_FRES] = (float) atof (str);
	    break;
	  }

	case READ_DOUBLE_SYSCALL:
	  {
	    static char str [256];

	    read_input (str, 256);
	    FPR [REG_FRES] = atof (str);
	    break;
	  }

	case READ_STRING_SYSCALL:
	  {
	    read_input ( (char *) MEM_ADDRESS (R[REG_A0]), R[REG_A1]);
	    data_modified = 1;
	    break;
	  }

	case SBRK_SYSCALL:
	  {
	    mem_addr x = data_top;
	    expand_data (R[REG_A0]);
	    R[REG_RES] = x;
	    data_modified = 1;
	    break;
	  }

	case PRINT_CHARACTER_SYSCALL:
	  write_output (console_out, "%c", R[REG_A0]);
	  break;

	case READ_CHARACTER_SYSCALL:
	  {
	    static char str [2];

	    read_input (str, 2);
	    if (*str == '\0') *str = '\n';      /* makes xspim = spim */
	    R[REG_RES] = (long) str[0];
	    break;
	  }

	case EXIT_SYSCALL:
	  return (0);

	case OPEN_SYSCALL:
	  {
#ifdef WIN32
	    R[REG_RES] = _open(MEM_ADDRESS(R[REG_A0]), R[REG_A1], R[REG_A2]);
#else
	    R[REG_RES] = open(MEM_ADDRESS(R[REG_A0]), R[REG_A1], R[REG_A2]);
#endif
	    break;
	  }
		
	case READ_SYSCALL:
	  {
	    /* Test if address is valid */
	    MEM_ADDRESS(R[REG_A1] + R[REG_A2] - 1);
#ifdef WIN32
	    R[REG_RES] = _read(R[REG_A0], MEM_ADDRESS(R[REG_A1]), R[REG_A2]);
#else
	    R[REG_RES] = read(R[REG_A0], MEM_ADDRESS(R[REG_A1]), R[REG_A2]);
#endif
	    data_modified = 1;
	    break;
	  }

	case WRITE_SYSCALL:
	  {
	    /* Test if address is valid */
	    MEM_ADDRESS(R[REG_A1] + R[REG_A2] - 1);
#ifdef WIN32
	    R[REG_RES] = _write(R[REG_A0], MEM_ADDRESS(R[REG_A1]), R[REG_A2]);
#else
	    R[REG_RES] = write(R[REG_A0], MEM_ADDRESS(R[REG_A1]), R[REG_A2]);
#endif
	    break;
	  }

	case CLOSE_SYSCALL:
	  {
#ifdef WIN32
	    R[REG_RES] = _close(R[REG_A0]);
#else
	    R[REG_RES] = close(R[REG_A0]);
#endif
	    break;
	  }

	default:
	  run_error ("Unknown system call: %d\n", R[REG_V0]);
	  break;
	}
    }
  else
#if (mips && dec)
    {
      if (!fds_initialized)
	{
	  initialize_prog_fds ();
	  fds_initialized = 1;
	}

      /* Use actual MIPS system calls. First translate arguments from
	 simulated memory to actual memory and correct file descriptors. */
      if (R[REG_V0] < 0 || R[REG_V0] > MAX_SYSCALL)
	{
	  run_error ("Illegal system call: %d\n", R[REG_V0]);
	}

      switch (syscall_table[R[REG_V0]].syscall_type)
	{
	case BAD_SYSCALL:
	  run_error ("Unknown system call: %d\n", R[REG_V0]);
	  break;

	case UNIX_SYSCALL:
	  unixsyscall ();
	  break;

	case SPC_SYSCALL:
	  /* These syscalls need to be simulated specially: */
	  switch (R[REG_V0])
	    {
	    case SYS_syscall:
	      R[REG_V0] = R[REG_A0];
	      R[REG_A0] = R[REG_A1];
	      R[REG_A1] = R[REG_A2];
	      R[REG_A2] = R[REG_A3];
	      READ_MEM_WORD (R[REG_A3], R[REG_SP] + 16);
	      do_syscall ();
	      break;

	    case SYS_sysmips:
	      {
		/* The table smipst maps from the sysmips arguments to syscall
		   numbers */
		int callno;
		static int smipst[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
				       7, 7, SYS_getrusage, SYS_wait3,
				       SYS_cacheflush, SYS_cachectl};
		callno= R[REG_A0];
		callno= ( (callno >0x100) ? smipst[callno - 0x100 + 10]
			  : smipst[callno]);
		R[REG_V0] = callno;
		R[REG_A0] = R[REG_A1];
		R[REG_A1] = R[REG_A2];
		R[REG_A2] = R[REG_A3];
		READ_MEM_WORD (R[REG_A3], R[REG_SP] + 16);
		do_syscall ();
		break;
	      }

	    case SYS_exit:
	      {
		kill_prog_fds ();

		return (0);
	      }

	    case SYS_close:
	      if (unixsyscall () >= 0)
		prog_fds[R[REG_A0]] = -1; /* Mark file descriptor closed */
	      break;

	    case SYS_open:
	    case SYS_creat:
	    case SYS_dup:
	      {
		int ret = unixsyscall ();

		if (ret >= 0)
		  prog_fds[ret] = ret; /* Update fd translation table */

		break;
	      }

	    case SYS_pipe:
	      {
		/* This isn't too useful unless we implement fork () or other
		   fd passing mechanisms */
		int fd1, fd2;

		if (unixsyscall () >= 0)
		  {
		    READ_MEM_WORD (fd1, MEM_ADDRESS (R[REG_A0]));
		    READ_MEM_WORD (fd2, MEM_ADDRESS (R[REG_A0]));
		    prog_fds[fd1] = fd1;
		    prog_fds[fd2] = fd2;
		  }
		break;
	      }

	    case SYS_select:
	      {
		int fd;
		/*
		 * We have to use this kludge to circumvent typechecking
		 * because the memory read macros take the lefthand side
		 * as an argument instead of simply returnign the value
		 * at the address
		 */
		mem_addr kludge;
		fd_set a, b, c;
		fd_set *readfds = &a, *writefds = &b, *exceptfds = &c;
		struct timeval *timeout;

		FD_ZERO (readfds);
		FD_ZERO (writefds);
		FD_ZERO (exceptfds);
		READ_MEM_WORD (kludge, R[REG_SP] + 16);
		if (kludge == NULL)
		  timeout = NULL;
		else
		  timeout = (struct timeval *) MEM_ADDRESS (kludge);

		if (R[REG_A1] == NULL)
		  readfds = NULL;
		else
		  for (fd = 0; fd < R[REG_A0]; fd++)
		    if (FD_ISSET (fd, (fd_set *) MEM_ADDRESS (R[REG_A1])))
		      FD_SET (prog_fds[fd], readfds);

		if (R[REG_A2] == NULL)
		  writefds = NULL;
		else
		  for (fd = 0; fd < R[REG_A0]; fd++)
		    if (FD_ISSET (fd, (fd_set *) MEM_ADDRESS (R[REG_A2])))
		      FD_SET (prog_fds[fd], writefds);

		if (R[REG_A3] == NULL)
		  exceptfds = NULL;
		else
		  for (fd = 0; fd < R[REG_A0]; fd++)
		    if (FD_ISSET (fd, (fd_set *) MEM_ADDRESS (R[REG_A3])))
		      FD_SET (prog_fds[fd], exceptfds);

		R[REG_RES] = select (R[REG_A0], readfds, writefds, exceptfds,
				     timeout);
		if (readfds == NULL)
		  R[REG_A1] = NULL;
		else
		  for (fd = 0; fd < R[REG_A0]; fd++)
		    if (FD_ISSET (fd, readfds))
		      FD_SET (reverse_fds (fd),
			      (fd_set *) MEM_ADDRESS (R[REG_A1]));

		if (writefds == NULL)
		  R[REG_A2] = NULL;
		else
		  for (fd = 0; fd < R[REG_A0]; fd++)
		    if (FD_ISSET (fd, writefds))
		      FD_SET (reverse_fds (fd),
			      (fd_set *) MEM_ADDRESS (R[REG_A2]));

		if (exceptfds == NULL)
		  R[REG_A3] = NULL;
		else
		  for (fd = 0; fd < R[REG_A0]; fd++)
		    if (FD_ISSET (fd, exceptfds))
		      FD_SET (reverse_fds (fd),
			      (fd_set *) MEM_ADDRESS (R[REG_A3]));

		if (R[REG_RES] < 0)
		  {
		    R[REG_ERR] = -1;
		    R[REG_RES] = errno;
		    return (-1);
		  }
		else
		  {
		    R[REG_ERR] = 0;
		    return (R[REG_RES]);
		  }
	      }

	    case SYS_sbrk:
	      {
		expand_data (R[REG_A0]);
		R[REG_RES] = program_break;
		program_break += R[REG_A0];
		R[REG_ERR] = 0;
		break;
	      }

	    case SYS_brk:
	      /* Round up to 4096 byte (page) boundary */
	      if ( ( (int) R[REG_A0] - (int) data_top) > 0)
		expand_data (ROUND_UP (R[REG_A0], 4096)- (int)data_top);
	      R[REG_RES] = program_break;
	      program_break = ROUND_UP (R[REG_A0], 4096);
	      R[REG_ERR] = 0;
	      break;

	    case SYS_sigvec:
	      {
		int x;

		if (R[REG_A2] != 0)
		  * (struct sigvec *) MEM_ADDRESS (R[REG_A2]) = sighandler[R[REG_A0]];
		READ_MEM_WORD (x, R[REG_A1]);
		sighandler[R[REG_A0]].sv_handler = (void (*) ()) x;
		READ_MEM_WORD (x,R[REG_A1] + sizeof (int *));
		sighandler[R[REG_A0]].sv_mask = x;
		READ_MEM_WORD (x,R[REG_A1] + sizeof (int *)
			       + sizeof (sigset_t));
		sighandler[R[REG_A0]].sv_flags = x;
		exception_address[R[REG_A0]] = R[REG_A3];
		R[REG_ERR] = 0;
		break;
	      }

	    case SYS_sigreturn:
	      do_sigreturn (MEM_ADDRESS (R[REG_A0]));
	      R[REG_ERR] = 0;
	      break;

	    case SYS_sigsetmask:
	      R[REG_RES] = prog_sigmask;
	      prog_sigmask = R[REG_A0];
	      R[REG_ERR] = 0;
	      break;

	    case SYS_sigblock:
	      R[REG_RES] = prog_sigmask;
	      prog_sigmask |= R[REG_A0];
	      R[REG_ERR] = 0;
	      break;

	    case SYS_cacheflush:
#if 0
	      R[REG_RES] = cache_flush ((void*)MEM_ADDRESS (R[REG_A0]),
					R[REG_A1],
					R[REG_A2]);
#endif
	      R[REG_ERR] = 0;
	      break;

	    case SYS_cachectl:
#if 0
	      R[REG_RES] = cache_ctl ((void*)MEM_ADDRESS (R[REG_A0]),
				      R[REG_A1],R
				      [REG_A2]);
#endif
	      R[REG_ERR] = 0;
	      break;

	    default:
	      run_error ("Unknown special system call: %d\n",R[REG_V0]);
	      break;
	    }
	  break;

	default:
	  run_error ("Unknown type for syscall: %d\n", R[REG_V0]);
	  break;
	}
    }
#else
  run_error ("Can't use MIPS syscall on non-MIPS system\n");
#endif

  return (1);
}



/* Execute a Unix system call.  Returns negative on error. */
#if (mips && dec)
#ifdef __STDC__
static int
unixsyscall (void)
#else
static int
unixsyscall ()
#endif
{
  void* arg0, arg1, arg2, arg3;

  arg0 = SYSCALL_ARG (REG_V0,arg0, REG_A0);
  arg1 = SYSCALL_ARG (REG_V0,arg1, REG_A1);
  arg2 = SYSCALL_ARG (REG_V0,arg2, REG_A2);
  arg3 = SYSCALL_ARG (REG_V0,arg3, REG_A3);
  R[REG_RES] = syscall (R[REG_V0], arg0, arg1, arg2, arg3);

  /* See if an error has occurred during the system call. If so, the
     libc wrapper must be notifified by setting register 7 to be less than
     zero and the return value should be errno. If not, register 7 should
     be zero. r7 acts like the carry flag in the old days.  */

  if (R[REG_RES] < 0)
    {
      R[REG_ERR] = -1;
      R[REG_RES] = errno;
      return (-1);
    }
  else
    {
      R[REG_ERR] = 0;
      return (R[REG_RES]);
    }
}
#endif


#if (mips && dec)
#ifdef __STDC__
static int
reverse_fds (int fd)
#else
static int
reverse_fds (fd)
     int fd;
#endif
{
  int i;

  for (i = 0; i < OPEN_MAX; i++)
    if (prog_fds[i] == fd)
      return (i);

  run_error ("Couldn't reverse translate fds\n");
  return (-1);
}
#endif


#ifdef __STDC__
void
print_syscall_usage (void)
#else
void
print_syscall_usage ()
#endif
{
  int x;

  printf ("System call counts...\n\n");
  printf ("Call#\t\tFrequency\n");
  for (x = 0; x < MAX_SYSCALL; x ++)
    if (syscall_usage[x] > 0)
      printf("%d(%s)\t\t%d\n",
	     x, syscall_table[x].syscall_name, syscall_usage[x]);
  printf ("\n");
}


#ifdef __STDC__
void
initialize_prog_fds (void)
#else
void
initialize_prog_fds ()
#endif
{
  int x;

  for (x = 0; x < OPEN_MAX; prog_fds[x++] = -1);
  if (((prog_fds[0] = dup(0)) < 0) ||
      ((prog_fds[1] = dup(1)) < 0) ||
      ((prog_fds[2] = dup(2)) < 0))
    error("init_prog_fds");
}


/* clear out programs file descriptors, close necessary files */

#ifdef __STDC__
void
kill_prog_fds (void)
#else
void
kill_prog_fds ()
#endif
{
  int x;

  for (x = 0; x < OPEN_MAX; x++)
    if (prog_fds[x] != -1) close(prog_fds[x]);
}



#ifdef __STDC__
void
handle_exception (void)
#else
void
handle_exception ()
#endif
{
  if (!quiet && ((Cause >> 2) & 0xf) != INT_EXCPT)
    error ("Exception occurred at PC=0x%08x\n", EPC);

  exception_occurred = 0;
  PC = EXCEPTION_ADDR;

  switch ((Cause >> 2) & 0xf)
    {
    case INT_EXCPT:
      if (!source_file)
	R[REG_A0] = SIGINT;
      break;

    case ADDRL_EXCPT:
      if (!source_file)
	R[REG_A0] = SIGSEGV;
      if (!quiet)
	error ("  Unaligned address in inst/data fetch: 0x%08x\n",BadVAddr);
      break;

    case ADDRS_EXCPT:
      if (!source_file)
	R[REG_A0] = SIGSEGV;
      if (!quiet)
	error ("  Unaligned address in store: 0x%08x\n", BadVAddr);
      break;

    case IBUS_EXCPT:
      if (!source_file)
	R[REG_A0] = SIGBUS;
      if (!quiet)
	error ("  Bad address in text read: 0x%08x\n", BadVAddr);
      break;

    case DBUS_EXCPT:
      if (!source_file)
	R[REG_A0] = SIGBUS;
      if (!quiet)
	error ("  Bad address in data/stack read: 0x%08x\n", BadVAddr);
      break;

    case BKPT_EXCPT:
      exception_occurred = 0;
      return;

    case SYSCALL_EXCPT:
      if (!quiet)
	error ("  Error in syscall\n");
      break;

    case RI_EXCPT:
      if (!quiet)
	error ("  Reserved instruction execution\n");
      break;

    case OVF_EXCPT:
      if (!source_file)
	R[REG_A0] = SIGFPE;
      if (!quiet)
	error ("  Arithmetic overflow\n");
      break;

    default:
      if (!quiet)
	error ("Unknown exception: %d\n", Cause >> 2);
      break;
    }

  if (!source_file)
    {
#if (mips && dec)
      if ((prog_sigmask & (1 << R[REG_A0])) == 1)
	return;

      if((int) sighandler[R[REG_A0]].sv_handler == 0)
	run_error ("Exception occurred at PC=0x%08x\nNo handler for it.\n",
		   EPC);

      setup_signal_stack();
      R[REG_A1] = 48;

      R[REG_A2] = R[29];
      R[REG_A3] = (int) sighandler[R[REG_A0]].sv_handler;
      if ((PC = exception_address[R[REG_A0]]) == 0)
	PC = (int) find_symbol_address ("sigvec") + 44;
#endif
    }
}

#if (mips && dec)
#ifdef __STDC__
static void
setup_signal_stack (void)
#else
static void
setup_signal_stack ()
#endif
{
  int i;
  struct sigcontext *sc;

  R[29] -= sizeof(struct sigcontext) + 4;
  sc = (struct sigcontext *) MEM_ADDRESS (R[29]);
  sc->sc_onstack = 0		/**/;
  sc->sc_mask = prog_sigmask;
  sc->sc_pc = EPC;
  for(i=0; i < 32; ++i)		/* general purpose registers */
    sc->sc_regs[i] = R[i];
  sc->sc_mdlo = LO;		/* mul/div low */
  sc->sc_mdhi = HI;
  sc->sc_ownedfp = 0;		/* fp has been used */
  for(i=0; i < 32; ++i)		/* FPU registers */
    sc->sc_fpregs[i] = FPR[i];
  sc->sc_fpc_csr = 0;		/* floating point control and status reg */
  sc->sc_fpc_eir = 0;
  sc->sc_cause = Cause;		/* cp0 cause register */
  sc->sc_badvaddr = BadVAddr;	/* cp0 bad virtual address */
  sc->sc_badpaddr = 0;		/* cpu bd bad physical address */
}
#endif

#if (mips && dec)
#ifdef __STDC__
static void
do_sigreturn (mem_addr sigptr)
#else
static void
do_sigreturn (sigptr)
  mem_addr sigptr;
#endif
{
  int i;
  struct sigcontext *sc;

  sc = (struct sigcontext *) sigptr;
  prog_sigmask = sc->sc_mask;
  PC = sc->sc_pc - BYTES_PER_WORD;
  for(i=0; i < 32; ++i)
    R[i] = sc->sc_regs[i];
  LO = sc->sc_mdlo;
  HI = sc->sc_mdhi;
  for(i=0; i < 32; ++i)		/* FPU registers */
    FPR[i] = sc->sc_fpregs[i];
  Cause = sc->sc_cause;
  BadVAddr = sc->sc_badvaddr;
  R[29] += sizeof(struct sigcontext) + 4;
}
#endif
