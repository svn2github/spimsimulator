// SPIM S20 MIPS simulator.
// Definitions for the SPIM S20.
//
// Copyright (C) 1990-2004 by James Larus (larus@cs.wisc.edu).
// ALL RIGHTS RESERVED.
// Changes for DOS and Windows versions by David A. Carley (dac@cs.wisc.edu)
//
// SPIM is distributed under the following conditions:
//
//   You may make copies of SPIM for your own use and modify those copies.
//
//   All copies of SPIM must retain my name and copyright notice.
//
//   You may not sell SPIM or distributed SPIM in conjunction with a
//   commerical product or service without the expressed written consent of
//   James Larus.
//
// THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
// PURPOSE.

/* $Header: /Software/SPIM/PCSpim/SpimReg.h 7     3/14/04 7:51p Larus $ */

#ifndef SPIMREG_H
#define SPIMREG_H

#define SPIM_REG_SPIMROOT		"Software\\UW-Madison\\PCSpim"
#define SPIM_REG_DEFAULTSETTINGS	SPIM_REG_SPIMROOT "\\Default Settings"
#define SPIM_REG_SETTINGS		SPIM_REG_SPIMROOT "\\Settings"

#define SPIM_REG_BARE			"Bare Machine"
#define SPIM_REG_DELAYEDBRANCHES	"Simulate Delayed Branches"
#define SPIM_REG_DELAYEDLOADS		"Simulate Delayed Loads"
#define SPIM_REG_PSEUDO			"Accept Pseudo Instructions"
#define SPIM_REG_LOADEXCEPTION		"Load Exception Handler"
#define SPIM_REG_MAPPEDIO		"Mapped IO"
#define SPIM_REG_QUIET			"Quiet"
#define SPIM_REG_EXCEPTIONFILE		"Exception File"
#define SPIM_REG_FPREG_HEX		"FP Regs in Hex"
#define SPIM_REG_GENREG_HEX		"General Regs in Hex"
#define	SPIM_REG_CHECK_UNDEF		"Uncheck Undefined Symbols"

#define SPIM_REG_SAVEWINPOS		"Save Window Positions"

#define SPIM_REG_MAINWINPOS		"Main Window Position"
#define SPIM_REG_MESSAGESPOS		"Message Window Position"
#define SPIM_REG_MESSAGESMINMAX		"Message Window State"
#define SPIM_REG_REGISTERSPOS		"Register Window Position"
#define SPIM_REG_REGISTERSMINMAX	"Register Window State"
#define SPIM_REG_TEXTSEGPOS		"Text Segment Window Position"
#define SPIM_REG_TEXTSEGMINMAX		"Text Segment Window State"
#define SPIM_REG_DATASEGPOS		"Data Segment Window Position"
#define SPIM_REG_DATASEGMINMAX		"Data Segment Window State"
#define SPIM_REG_CONSOLEPOS		"Console Window Position"

#define SPIM_REG_FONTFACE		"Window Font Face"
#define SPIM_REG_FONTHEIGHT		"Window Font Height"
#define SPIM_REG_FONTWEIGHT		"Window Font Weight"
#define SPIM_REG_FONTITALIC		"Window Font Italic"

#endif // SPIMREG_H
