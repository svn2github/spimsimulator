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

/* $Header: /Software/SPIM/PCSpim/PCSpimView.cpp 17    3/14/04 8:25p Larus $ */

// PCSpimView.cpp : implementation of the CPCSpimView class
//

#include "stdafx.h"
#include "PCSpim.h"

#include "PCSpimDoc.h"
#include "PCSpimView.h"
#include "MainFrm.h"
#include "ConsoleWnd.h"
#include "util.h"
#include "SpimReg.h"



#ifndef EXCEPTION_FILE_PATH
#define EXCEPTION_FILE_PATH "D:\\Larus\\Software\\SPIM\\src\\exceptions.s"
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCSpimView

IMPLEMENT_DYNCREATE(CPCSpimView, CView)

BEGIN_MESSAGE_MAP(CPCSpimView, CView)
//{{AFX_MSG_MAP(CPCSpimView)
ON_WM_CREATE()
ON_COMMAND(ID_SIMULATOR_REINITIALIZE, OnSimulatorReinitialize)
ON_COMMAND(ID_SIMULATOR_CLEAR_REGISTERS, OnSimulatorClearRegisters)
ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
ON_COMMAND(ID_SIMULATOR_GO, OnSimulatorRun)
ON_COMMAND(ID_SIMULATOR_BREAKPOINTS, OnSimulatorBreakpoints)
ON_COMMAND(ID_SIMULATOR_SETVALUE, OnSimulatorSetvalue)
ON_COMMAND(ID_SIMULATOR_BREAK, OnSimulatorBreak)
ON_COMMAND(ID_SIMULATOR_SETTINGS, OnSimulatorSettings)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_RELOAD, OnUpdateSimulatorReload)
ON_COMMAND(ID_SIMULATOR_RELOAD, OnSimulatorReload)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_BREAK, OnUpdateSimulatorBreak)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_GO, OnUpdateSimulatorRun)
ON_COMMAND(ID_SIMULATOR_STEP, OnSimulatorStep)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_STEP, OnUpdateSimulatorStep)
ON_COMMAND(ID_SIMULATOR_MULTISTEP, OnSimulatorMultistep)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_MULTISTEP, OnUpdateSimulatorMultistep)
ON_COMMAND(ID_SIMULATOR_DISPLAYSYMBOLS, OnSimulatorDisplaysymbols)
ON_COMMAND(ID_WINDOW_CASCADE, OnWindowCascade)
ON_COMMAND(ID_WINDOW_NEXT, OnWindowNext)
ON_COMMAND(ID_WINDOW_PREVIOUS, OnWindowPrevious)
ON_COMMAND(ID_WINDOW_TILE, OnWindowTile)
ON_COMMAND(ID_WINDOW_CLEAR_CONSOLE, OnWindowClearConsole)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_SETVALUE, OnUpdateSimulatorSetvalue)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_BREAKPOINTS, OnUpdateSimulatorBreakpoints)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_DISPLAYSYMBOLS, OnUpdateSimulatorDisplaysymbols)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_CLEAR_REGISTERS, OnUpdateSimulatorClearRegisters)
ON_UPDATE_COMMAND_UI(ID_SIMULATOR_REINITIALIZE, OnUpdateSimulatorReinitialize)
ON_COMMAND(ID_WINDOW_MESSAGES, OnWindowMessages)
ON_COMMAND(ID_WINDOW_REGISTERS, OnWindowRegisters)
ON_COMMAND(ID_WINDOW_TEXTSEG, OnWindowTextseg)
ON_COMMAND(ID_WINDOW_DATASEG, OnWindowDataseg)
ON_COMMAND(ID_WINDOW_CONSOLE, OnWindowConsole)
ON_WM_DESTROY()
ON_COMMAND(ID_WINDOW_ARRANGEICONS, OnWindowArrangeicons)
ON_COMMAND(ID_FILE_SAVE_LOG, OnFileSaveLog)
ON_COMMAND(ID_INDICATOR_BARE, CMainFrame::UpdateSettingsStatus)
ON_COMMAND(ID_INDICATOR_DELAY_BR, CMainFrame::UpdateSettingsStatus)
ON_COMMAND(ID_INDICATOR_DELAY_LD, CMainFrame::UpdateSettingsStatus)
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCSpimView construction/destruction

CPCSpimView::CPCSpimView()
{
  g_fRunning = FALSE;

  m_fStackInitialized = FALSE;
  m_fCapture = FALSE;
  m_nForceStop = 0;
  m_fConsoleMinimized = TRUE;
  m_fSimulatorInitialized = FALSE;

  m_strCurFilename.Empty();
}


CPCSpimView::~CPCSpimView()
{
}


/////////////////////////////////////////////////////////////////////////////
// CPCSpimView drawing

void CPCSpimView::OnDraw(CDC* pDC)
{
  CPCSpimDoc* pDoc = GetDocument();
  ASSERT_VALID(pDoc);

  if (!pDC->IsPrinting())
    {
      RECT r;
      GetClientRect(&r);
      pDC->FillSolidRect(&r, GetSysColor(COLOR_3DFACE));
    }
}


/////////////////////////////////////////////////////////////////////////////
// CPCSpimView diagnostics

#ifdef _DEBUG
void CPCSpimView::AssertValid() const
{
  CView::AssertValid();
}

void CPCSpimView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}

CPCSpimDoc* CPCSpimView::GetDocument() // non-debug version is inline
{
  ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPCSpimDoc)));
  return (CPCSpimDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPCSpimView message handlers

#define GETCHILDWININFO(szRegPathStub)	\
  if (g_fSaveWinPos)	\
{		\
      if (pApp->GetSetting(szRegPathStub##POS, &r))	\
      pr = &r;	\
      \
      dwStyle = WS_CHILD;	\
      nMinMax = pApp->GetSetting(szRegPathStub##MINMAX, SW_SHOW);	\
}		\
  else	\
{		\
      r.left = r.top = r.right = r.bottom = 0; pr = NULL;	\
      nMinMax = SW_SHOW ;	\
}


static void
InitSpimWins(CEdit& Win, RECT& r, int nMinMax, BOOL ScrollVert, BOOL ScrollHorz)
{
  Win.ShowWindow(nMinMax);

  if (ScrollVert)
    Win.ShowScrollBar(SB_VERT, TRUE);
  if (ScrollHorz)
    Win.ShowScrollBar(SB_HORZ, TRUE);
}


int CPCSpimView::OnCreate(LPCREATESTRUCT pcs)
{
  if (CView::OnCreate(pcs) == -1)
    return -1;

  // The simulation support code needs to be able to access this.
  g_pView = this;

  // Don't draw over the top of the children.
  DWORD dwStyle = GetWindowLong(m_hWnd, GWL_STYLE);
  dwStyle |= WS_CLIPCHILDREN;
  SetWindowLong(m_hWnd, GWL_STYLE, dwStyle);

  CPCSpimApp *pApp = (CPCSpimApp *)AfxGetApp();

  RECT r, *pr;
  int nMinMax;

  // Console is a special case.  We save position, but not minmax.
  if (g_fSaveWinPos && pApp->GetSetting(SPIM_REG_CONSOLEPOS, &r))
    {
      pr = &r;
    }
  else
    {
      pr = NULL;
    }
  m_wndConsole.Create(NULL,
		      "Console",
		      pr,
		      ES_AUTOHSCROLL | ES_AUTOVSCROLL,
		      0,
		      WS_POPUP);
  m_wndConsole.m_fActAsConsole = TRUE;

  // Messages window
  GETCHILDWININFO(SPIM_REG_MESSAGES);
  m_wndMessages.Create(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
		       r,
		       this,
		       1);
  InitSpimWins(m_wndMessages, r, nMinMax, TRUE, TRUE);

  // Data segment window
  GETCHILDWININFO(SPIM_REG_DATASEG);
  m_wndDataSeg.Create(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
		      r,
		      this,
		      1);
  InitSpimWins(m_wndDataSeg, r, nMinMax, TRUE, TRUE);
  m_wndDataSeg.SetLimitText(0x7FFFFFFE);	  // Allow lots of space

  // Text segment window
  GETCHILDWININFO(SPIM_REG_TEXTSEG);
  m_wndTextSeg.Create(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE | ES_NOHIDESEL,
		      r,
		      this,
		      1);
  InitSpimWins(m_wndTextSeg, r, nMinMax, TRUE, TRUE);
  m_wndTextSeg.SetLimitText(0x7FFFFFFE);	  // Allow lots of space

  // Register window
  GETCHILDWININFO(SPIM_REG_REGISTERS);
  m_wndRegisters.Create(ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE,
			r,
			this,
			1);
  InitSpimWins(m_wndRegisters, r, nMinMax, TRUE, TRUE);


  // Get font info from registry and use to set windows' font.
  //
  LOGFONT lf;
  memset(&lf, 0, sizeof(LOGFONT));

  strcpy(lf.lfFaceName, (char*)pApp->GetSetting(SPIM_REG_FONTFACE, "Courier"));	/* Default: Courier 16pt, normal weight */
  lf.lfHeight = pApp->GetSetting(SPIM_REG_FONTHEIGHT, 16);
  lf.lfWeight = pApp->GetSetting(SPIM_REG_FONTWEIGHT, 400);
  lf.lfItalic = pApp->GetSetting(SPIM_REG_FONTITALIC, 0);

  SetSpimFont(&lf);


  // Load settings
  Initialize();

  // Create the breakpoint window (should be initially hidden)
  m_dlgBP.Create(this);

  return 0;
}


void CPCSpimView::WriteToMessage(LPCTSTR szText)
{
  if (m_fCapture)
    {
      TCHAR *szTemp = MakeCRLFValid(szText);
      m_strMsgCaptureBuf += szTemp;
      delete [] szTemp;
    }
  else
    {
      CString buf ('\0', m_wndMessages.GetWindowTextLength());
      m_wndMessages.GetWindowText(buf);
      char* text2 = MakeCRLFValid(szText);
      buf += text2;
      delete text2;
      m_wndMessages.SetWindowText(buf);

      // Position last few lines in window.
      m_wndMessages.LineScroll(m_wndMessages.GetLineCount() - 4, 0) ;
      m_wndMessages.UpdateWindow();
    }
}


void CPCSpimView::WriteToConsole(LPCTSTR szText)
{
  m_wndConsole.WriteText(szText);
}


void CPCSpimView::Initialize()
{
  CPCSpimApp *pApp = (CPCSpimApp *)AfxGetApp();

  // Load the settings from the registry.
  bare_machine = pApp->GetSetting(SPIM_REG_BARE, FALSE);
  delayed_branches = pApp->GetSetting(SPIM_REG_DELAYEDBRANCHES, FALSE);
  delayed_loads = pApp->GetSetting(SPIM_REG_DELAYEDLOADS, FALSE);
  accept_pseudo_insts = pApp->GetSetting(SPIM_REG_PSEUDO, TRUE);
  quiet = pApp->GetSetting(SPIM_REG_QUIET, FALSE);
  mapped_io = pApp->GetSetting(SPIM_REG_MAPPEDIO, TRUE);
  g_fLoadExceptionHandler = pApp->GetSetting(SPIM_REG_LOADEXCEPTION, TRUE);
  g_fGenRegHex = pApp->GetSetting(SPIM_REG_GENREG_HEX, TRUE);
  g_fFPRegHex = pApp->GetSetting(SPIM_REG_FPREG_HEX, FALSE);
  g_checkUndefinedSymbols = pApp->GetSetting(SPIM_REG_CHECK_UNDEF, TRUE);

  LPCTSTR szBuf = pApp->GetSetting(SPIM_REG_EXCEPTIONFILE, EXCEPTION_FILE_PATH);
  delete [] exception_file_name;
  exception_file_name = new TCHAR[lstrlen(szBuf) + 1];
  lstrcpy(exception_file_name, szBuf);

  if (lstrlen(exception_file_name) == 0)
    {
      g_fLoadExceptionHandler = FALSE;
    }

  if (bare_machine)
    {
      delayed_branches = 1;
      delayed_loads = 1;
    }

  // We're using these just as unique identifiers in the output code.
  message_out.i = 0, console_out.i = 1;

  // Now that we've set all of the defaults, and loaded the
  // registry settings, process the commandline for overrides.
  ProcessCommandLine();

  InitializeSimulator();

  if (!m_strCurFilename.IsEmpty())
  {
    LoadFile(m_strCurFilename);	// From command line
  }
}

void CPCSpimView::InitializeSimulator()
{
  OFSTRUCT ofs;

  m_wndConsole.Clear();
  m_wndMessages.Clear();

 l_TestExceptionExists:
  if (g_fLoadExceptionHandler &&
      (HFILE_ERROR == OpenFile(exception_file_name, &ofs, OF_EXIST)))
    {
      int nRet
	= MessageBox(
		     "The exception file specified in the Settings dialog does not exist.\n"
		     "Please specify an existing file, or turn off exception file loading.\n"
		     "\n"
		     "Would you like to open the Settings dialog?",
		     NULL, MB_YESNO | MB_ICONEXCLAMATION);

      if (nRet == IDYES)
	{
	  SendMessage(WM_COMMAND, MAKEWPARAM(ID_SIMULATOR_SETTINGS, 0), NULL);
	  goto l_TestExceptionExists;
	}

      return;
    }
  else
    {
      write_startup_message();

      initialize_world(g_fLoadExceptionHandler ? exception_file_name : NULL);

      // We need to set up the stack for the next time we run.
      m_fStackInitialized = FALSE;

      m_fSimulatorInitialized = TRUE;

      UpdateStatusDisplay();
      HighlightCurrentInstruction();
    }
}


void CPCSpimView::OnSimulatorReinitialize()
{
  InitializeSimulator();
  m_strCurFilename.Empty();
  write_output(message_out, "Memory and registers cleared and the simulator reinitialized.\n\n");
}


void CPCSpimView::OnSimulatorClearRegisters()
{
  initialize_registers();
  UpdateStatusDisplay();

  write_output(message_out, "Registers cleared.\n\n");
}


void CPCSpimView::OnFileOpen()
{
  TCHAR szFilters[] = "Assembly files (*.s; *.asm)|*.s;*.asm|All Files (*.*)|*.*||";
  // Prompt for a filename.
  CFileDialog dlg(TRUE,
		  NULL,
		  NULL,
		  OFN_HIDEREADONLY | OFN_FILEMUSTEXIST,
		  szFilters,
		  this);

  if (dlg.DoModal() != IDOK)
    return;

  // Load the file
  LoadFile(dlg.GetPathName());
}


void CPCSpimView::InitStack(LPCTSTR szCmdLine)
{
  int argc = 0;
  char *argv[10000];
  char *a;
  char *argsOrig = new char[lstrlen(szCmdLine) + 1];
  char *args = argsOrig;
  lstrcpy(args, szCmdLine);

  if (m_fStackInitialized)
    {
      return;
    }

  while (*args != '\0')
    {
      /* Skip leading blanks */
      while (*args == ' ' || *args == '\t') args++;

      /* First non-blank char */
      a = args;

      /* Last non-blank, non-null char */
      while (*args != ' ' && *args != '\t' && *args != '\0') args++;

      /* Terminate word */
      if (a != args)
	{
	  if (*args != '\0')
	    *args++ = '\0';	/* Null terminate */
	  argv [argc++] = a;
	}
    }

  initialize_run_stack (argc, argv);
  m_fStackInitialized = TRUE;

  delete [] argsOrig;
}



#include "RunDlg.h"
void CPCSpimView::OnSimulatorRun()
{
  mem_addr addr;

  CRunDlg dlg;
  if (IDCANCEL == dlg.DoModal())
    {
      return;
    }

  InitStack(g_strCmdLine);
  addr = strtoul(dlg.m_strAddress, NULL, 0);

  if (addr == 0)
    {
      addr = starting_address ();
    }

  if (addr != 0)
    {
      ExecuteProgram(addr, DEFAULT_RUN_STEPS, 0, 0);
    }
}



void CPCSpimView::ExecuteProgram(mem_addr pc,
				 int steps,
				 int display,
				 int cont_bkpt)
{
  g_fRunning = TRUE;
  ShowRunning();

  while (1)
    {
      if (0 != run_program(pc, steps, display, cont_bkpt))
	{
	  UpdateStatusDisplay();
	  HighlightCurrentInstruction();

	  // If we hit a breakpoint, and the user doesn't
	  // want to continue, then stop.
	  if (!AskContinue(FALSE))
	    {
	      break;
	    }

	  // Step over breakpoint
	  run_program(PC, 1, 0, 1);
	  pc = PC;
	}
      else
	{
	  break;
	}
    }

  if (::IsWindow(m_hWnd))	// We may have ended while running.
    {
      UpdateStatusDisplay();
      HighlightCurrentInstruction();

      g_fRunning = FALSE;
      ShowRunning();
    }
}


void CPCSpimView::UpdateStatusDisplay()
{
  DisplayDataSegment();
  DisplayTextSegment();
  DisplayRegisters();
}


void CPCSpimView::DisplayRegisters()
{
  static char buf[8 * K];
  int max_buf_len = 8 * K;
  int string_len = 0;

  if (!m_fSimulatorInitialized)
    {
      return;
    }

  registers_as_string (buf,
		       &max_buf_len,
		       &string_len,
		       g_fGenRegHex,
		       g_fFPRegHex);
  char* buf2 = MakeCRLFValid(buf);
  int top_line = m_wndRegisters.GetFirstVisibleLine();	// Remember window's top line
  m_wndRegisters.SetWindowText(buf2);
  m_wndRegisters.LineScroll(top_line, 0);		// Put that line at top again
  delete buf2;
}


void CPCSpimView::DisplayDataSegment()
{
  static char *buf = NULL;
  static int max_buf_len = 16 * K;
  int string_len = 0;

  if (!m_fSimulatorInitialized)
    return;

  if (!data_modified)
    return;

  if (buf == NULL)
    buf = (char *) malloc (max_buf_len);
  *buf = '\0';

  buf = data_seg_as_string(buf, &max_buf_len, &string_len);

  data_modified = 0;
  char* buf2 = MakeCRLFValid(buf);
  int top_line = m_wndDataSeg.GetFirstVisibleLine();	// Remember window's top line
  m_wndDataSeg.SetWindowText(buf2);
  m_wndDataSeg.LineScroll(top_line, 0);		// Put that line at top again
  delete buf2;
}


char * CPCSpimView::DumpMemValues(mem_addr from,
				  mem_addr to,
				  char* buf,
				  int *limit,
				  int *n)
{
  return mem_as_string (from, to, buf, limit, n);
}


void CPCSpimView::DisplayTextSegment()
{
  static char *buf =  NULL;
  static int max_buf_len = 16 * K;
  int string_len = 0;

  if (!m_fSimulatorInitialized)
    return;

  if (!text_modified)
    return;

  if (buf == NULL)
    buf = (char *) malloc (max_buf_len);
  *buf = '\0';

  buf = insts_as_string (TEXT_BOT, text_top, buf, &max_buf_len, &string_len);
  sprintf (&buf[string_len], "\n\tKERNEL\n");
  string_len += strlen (&buf[string_len]);
  buf = insts_as_string (K_TEXT_BOT, k_text_top, buf, &max_buf_len, &string_len);

  text_modified = 0;
  char* buf2 = MakeCRLFValid(buf);
  int top_line = m_wndTextSeg.GetFirstVisibleLine();	// Remember window's top line
  m_wndTextSeg.SetWindowText(buf2);
  m_wndTextSeg.LineScroll(top_line, 0);		// Put that line at top again
  delete buf2;
}


void CPCSpimView::OnSimulatorBreakpoints()
{
  m_dlgBP.ShowWindow(SW_NORMAL);
}


void CPCSpimView::SetMessageCapture(BOOL fOn)
{
  if (!fOn)
    m_strMsgCaptureBuf.Empty();

  m_fCapture = fOn;
}


LPCTSTR CPCSpimView::GetMessageCaptureBuf()
{
  return m_strMsgCaptureBuf;
}


void CPCSpimView::HighlightCurrentInstruction()
{
  char pattern[100];

  if (PC < TEXT_BOT || (PC > text_top && (PC < K_TEXT_BOT || PC > k_text_top)))
    return;

  sprintf (pattern, "[0x%08x]", PC);

  CString text;
  m_wndTextSeg.GetWindowText(text);
  int start = text.Find(pattern);
  if (start != -1)
    {
      int end = text.Find("\n", start + 1);
      if (end != - 1)
	{
	  // Reverse parameters so beginning of line is in window (!)
	  m_wndTextSeg.SetSel(end, start, FALSE);
	}
    }
}


#include "SetValueDlg.h"
void CPCSpimView::OnSimulatorSetvalue()
{
  CSetValueDlg dlg;
  dlg.DoModal();

  UpdateStatusDisplay();
}


// Functions both as Break and Continue
void CPCSpimView::OnSimulatorBreak()
{
  if (g_fRunning)	// "Break" mode
    {
      UpdateStatusDisplay();
      HighlightCurrentInstruction();

      if (!AskContinue(TRUE))
	force_break = 1;
    }
  else	// "Continue" mode
    {
      ExecuteProgram(PC, DEFAULT_RUN_STEPS, 0, 0);
    }
}


void CPCSpimView::OnUpdateSimulatorBreak(CCmdUI* pCmdUI)
{
  if (!m_fSimulatorInitialized)
    {
      pCmdUI->Enable(FALSE);
      return;
    }

  // NOTE:  We might want a flag for this instead.
  pCmdUI->Enable(PC != 0);

  if (g_fRunning || (PC == 0))
    pCmdUI->SetText("Break");
  else
    pCmdUI->SetText("Continue");
}


#include "SettingsDlg.h"
void CPCSpimView::OnSimulatorSettings()
{
  CSettingsDlg dlg;
  dlg.DoModal();	// It takes care of everything.

  if (m_fSimulatorInitialized)
    {
    ((CMainFrame*)AfxGetMainWnd())->GetActiveDocument()->UpdateAllViews(NULL);
    }
}


void CPCSpimView::OnUpdateSimulatorReload(CCmdUI* pCmdUI)
{
  pCmdUI->SetText("Re&load " + m_strCurFilename);
  pCmdUI->Enable(!m_strCurFilename.IsEmpty() && m_fSimulatorInitialized);
}


void CPCSpimView::OnSimulatorReload()
{
  LoadFile(m_strCurFilename);
}

extern "C" int parse_error_occurred;	// Import from parser
void CPCSpimView::LoadFile(LPCTSTR strFilename)
{
  int nLoaded;
  CString strLoadMsg;
  int result;

 l_TryLoad:

  if (m_strCurFilename.IsEmpty())
  {
    // Reset the simulator before loading first file
    OnSimulatorReinitialize();
  }
  else if (IDYES == (result = MessageBox("Clear program and reinitialize simulator before loading?",
					  NULL, MB_YESNOCANCEL | MB_ICONQUESTION)))
  {
    // Reset the simulator if requested
    OnSimulatorReinitialize();
  }
  else if (IDCANCEL == result)
  {
    // Quit before loading file
    return;
  }

  g_pView->SetMessageCapture(TRUE);
  nLoaded = read_assembly_file((char *)strFilename);
  strLoadMsg = g_pView->GetMessageCaptureBuf();
  g_pView->SetMessageCapture(FALSE);

  // Trim the white space off the front and rear.
  strLoadMsg.TrimLeft();
  strLoadMsg.TrimRight();

  if (nLoaded != 0)
    {
      strLoadMsg.Format("Could not open %s for reading.", strFilename);
      MessageBox(strLoadMsg, NULL, MB_OK | MB_ICONEXCLAMATION);
    }
  else if (!strLoadMsg.IsEmpty())
    {
      CString strMsg;

	  if (parse_error_occurred)
	  {
		strMsg.Format(
		    "An error occurred while loading the file.\n"
		    "The message are:\n"
		    "\n"
		    "%s\n"
		    "\n"
		    "Would you like to open the Settings dialog box to verify simulator settings?",
		    strLoadMsg);
		if (IDYES == MessageBox(strMsg, NULL, MB_YESNO | MB_ICONEXCLAMATION))
		{
		  SendMessage(WM_COMMAND, MAKEWPARAM(ID_SIMULATOR_SETTINGS, 0), NULL);

		  if (IDYES == MessageBox("Would you like to try to load the file again?",
								  NULL, MB_YESNO | MB_ICONQUESTION))
			goto l_TryLoad;
		}

		// They didn't want to try to reload.
		write_output(message_out,"Load terminated. Check code and simulator settings and try again.\n");
	  }
	  else
	  {
		strMsg.Format(
		    "Loading the file produced warnings.\n"
		    "The messages are:\n"
		    "\n"
		    "%s\n"
		    "\n"
		    "Would you like to open the Settings dialog box to verify simulator settings?",
		    strLoadMsg);
		if (IDYES == MessageBox(strMsg, NULL, MB_YESNO | MB_ICONEXCLAMATION))
		{
		  SendMessage(WM_COMMAND, MAKEWPARAM(ID_SIMULATOR_SETTINGS, 0), NULL);
		}
	  }
    }
  else
    {
      // Save the filename
      m_strCurFilename = strFilename;

      PC = find_symbol_address (DEFAULT_RUN_LOCATION);
      UpdateStatusDisplay();
      HighlightCurrentInstruction();

      write_output(message_out, "%s successfully loaded\n", strFilename);
    }
}


BOOL CPCSpimView::AskContinue(BOOL fBreak)
{
  CString strMsg;

  if (fBreak)
    strMsg.Format("Execution paused by the user at 0x%08x.\n", PC);
  else
    strMsg.Format("Breakpoint encountered at 0x%08x.\n", PC);

  strMsg += "\nContinue execution?";

  return (IDYES == MessageBox(strMsg, NULL, MB_YESNO | MB_ICONQUESTION));
}


void CPCSpimView::ShowRunning()
{
  CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();

  CString strTitle = pWnd->GetTitleBase();
  if (g_fRunning)
    strTitle += " [Running]";

  pWnd->SetWindowText(strTitle);
}


void CPCSpimView::OnUpdateSimulatorRun(CCmdUI* pCmdUI)
{
  CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();
  pWnd->UpdateSettingsStatus();

  pCmdUI->Enable(!g_fRunning && m_fSimulatorInitialized);
}


void CPCSpimView::OnSimulatorStep()
{
  ExecuteProgram(PC, 1, 1, 1);
}


void CPCSpimView::OnUpdateSimulatorStep(CCmdUI* pCmdUI)
{
  CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();
  pWnd->UpdateSettingsStatus();

  pCmdUI->Enable(!g_fRunning && m_fSimulatorInitialized);
}

#include "MultiStepDlg.h"
void CPCSpimView::OnSimulatorMultistep()
{
  CMultiStepDlg dlg;

  if (IDCANCEL == dlg.DoModal())
    return;

  ExecuteProgram(PC, dlg.m_cSteps, 1, 1);
}


void CPCSpimView::OnUpdateSimulatorMultistep(CCmdUI* pCmdUI)
{
  CMainFrame *pWnd = (CMainFrame *)AfxGetMainWnd();
  pWnd->UpdateSettingsStatus();

  pCmdUI->Enable(!g_fRunning && m_fSimulatorInitialized);
}


void CPCSpimView::OnSimulatorDisplaysymbols()
{
  print_symbols();
}


void CPCSpimView::OnWindowNext()
{
  CWnd *pWndTop, *pWndNext;

  pWndTop = GetTopWindow();
  if (pWndTop == NULL)
    return;

  while (!pWndTop->IsWindowVisible())
    {
      pWndTop = pWndTop->GetNextWindow();
    }

  pWndNext = pWndTop->GetNextWindow();
  if (pWndNext == NULL)
    return;

  while (!pWndNext->IsWindowVisible())
    {
      pWndNext = pWndNext->GetNextWindow();
    }

  pWndTop->SetWindowPos(&CWnd::wndBottom, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
  pWndNext->BringWindowToTop();
  pWndNext->SetFocus();
}


void CPCSpimView::OnWindowPrevious()
{
  CWnd *pWndTop, *pWndBottom;

  pWndTop = GetTopWindow();
  if (pWndTop == NULL)
    return;

  pWndBottom = pWndTop->GetWindow(GW_HWNDLAST);
  while (!pWndBottom->IsWindowVisible())
    {
      pWndBottom = pWndBottom->GetWindow(GW_HWNDPREV);
    }

  if (pWndBottom == pWndTop)
    return;

  pWndBottom->BringWindowToTop();
  pWndBottom->SetFocus();
}


void CPCSpimView::OnWindowCascade()
{
  CWnd *pWnd;
  long x, y, cx, cy;
  long cpixTitlebar = GetSystemMetrics(SM_CYCAPTION) +
    GetSystemMetrics(SM_CYFRAME);
  x = 0;
  y = 0;

  RECT r;
  GetClientRect(&r);
  cx = (r.right - r.left) - (10 * cpixTitlebar);
  cy = (r.bottom - r.top) - (10 * cpixTitlebar);

  HDWP hdwp = BeginDeferWindowPos(5);	// Just a guess at the number
  pWnd = GetTopWindow()->GetWindow(GW_HWNDLAST);
  while (pWnd != NULL)
    {
      if (!pWnd->IsIconic())
	{
	  DeferWindowPos(hdwp,
			 pWnd->m_hWnd,
			 NULL,
			 x,
			 y,
			 cx,
			 cy,
			 SWP_NOZORDER | SWP_NOACTIVATE);

	  x += cpixTitlebar;
	  y += cpixTitlebar;
	}

      pWnd = pWnd->GetNextWindow(GW_HWNDPREV);
    }
  EndDeferWindowPos(hdwp);
}


void CPCSpimView::OnWindowTile()
{
  RECT r;
  GetClientRect(&r);

  TileWindows(r.right - r.left, r.bottom - r.top, r.bottom);
}


//
// Tile windows in a reasonable order:
//    Register
//    Text
//    Data
//    Messages
//
void CPCSpimView::TileWindows(long cx, long cy, long bottom)
{
  long cTileWnds = 0;

  if (!m_wndRegisters.IsIconic()) cTileWnds ++;
  if (!m_wndTextSeg.IsIconic()) cTileWnds ++;
  if (!m_wndDataSeg.IsIconic()) cTileWnds ++;
  if (!m_wndMessages.IsIconic()) cTileWnds ++;

 if (cTileWnds == 0)
    return;

  long y = 0;

  cy = cy / cTileWnds;

  HDWP hdwp = BeginDeferWindowPos(5);
  if (!m_wndRegisters.IsIconic())
    {
      DeferWindowPos(hdwp, m_wndRegisters.m_hWnd, NULL, 0, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);

      y += cy;
      if ((bottom - y) < (2 * cy))
        cy = bottom - y;
    }
    if (!m_wndTextSeg.IsIconic())
    {
      DeferWindowPos(hdwp, m_wndTextSeg.m_hWnd, NULL, 0, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);

      y += cy;
      if ((bottom - y) < (2 * cy))
        cy = bottom - y;
    }
    if (!m_wndDataSeg.IsIconic())
    {
      DeferWindowPos(hdwp, m_wndDataSeg.m_hWnd, NULL, 0, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);

      y += cy;
      if ((bottom - y) < (2 * cy))
        cy = bottom - y;
    }
    if (!m_wndMessages.IsIconic())
    {
      DeferWindowPos(hdwp, m_wndMessages.m_hWnd, NULL, 0, y, cx, cy, SWP_NOZORDER | SWP_NOACTIVATE);

      y += cy;
      if ((bottom - y) < (2 * cy))
        cy = bottom - y;
    }
  EndDeferWindowPos(hdwp);
}


CConsoleWnd * CPCSpimView::GetConsole()
{
  return &m_wndConsole;
}


void CPCSpimView::MakeConsoleVisible()
{
  if (!m_fConsoleMinimized)
    {
      if (::IsWindow(m_hWnd))
	{
	  m_wndConsole.ShowWindow(SW_NORMAL);
	  m_wndConsole.BringWindowToTop();
	}
    }
}


void CPCSpimView::BringConsoleToTop()
{
  if (!m_fConsoleMinimized)
    {
      if (::IsWindow(m_hWnd))
	{
	  MakeConsoleVisible();
	  m_wndConsole.SetFocus();
	}
    }
}


void CPCSpimView::OnWindowClearConsole()
{
  m_wndConsole.Clear();
}


void CPCSpimView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
  ((CMainFrame*)AfxGetMainWnd())->UpdateSettingsStatus();
}


void CPCSpimView::OnWindowConsole()
{
  MakeConsoleVisible();
}

void CPCSpimView::OnUpdateSimulatorSetvalue(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_fSimulatorInitialized);
}


void CPCSpimView::OnUpdateSimulatorBreakpoints(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_fSimulatorInitialized);
}


void CPCSpimView::OnUpdateSimulatorDisplaysymbols(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_fSimulatorInitialized);
}


void CPCSpimView::OnUpdateSimulatorClearRegisters(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_fSimulatorInitialized);
}


void CPCSpimView::OnUpdateSimulatorReinitialize(CCmdUI* pCmdUI)
{
  pCmdUI->Enable(m_fSimulatorInitialized);
}


void CPCSpimView::OnWindowMessages()
{
  m_wndMessages.ShowWindow(SW_NORMAL);
  m_wndMessages.BringWindowToTop();
}


void CPCSpimView::OnWindowRegisters()
{
  m_wndRegisters.ShowWindow(SW_NORMAL);
  m_wndRegisters.BringWindowToTop();
}


void CPCSpimView::OnWindowTextseg()
{
  m_wndTextSeg.ShowWindow(SW_NORMAL);
  m_wndTextSeg.BringWindowToTop();
}


void CPCSpimView::OnWindowDataseg()
{
  m_wndDataSeg.ShowWindow(SW_NORMAL);
  m_wndDataSeg.BringWindowToTop();
}


#define WHITESPACE	" \t\n\r"
void CPCSpimView::ProcessCommandLine()
{
  LPTSTR argv[256];
  int argc;
  int i;
  
  // Initialize argc & argv variables.
  LPTSTR szCmdLine = GetCommandLine();
  if (szCmdLine[0] == '"')
    argv[0] = strtok(szCmdLine, "\"");
  else
    argv[0] = strtok(GetCommandLine(), WHITESPACE);
  
  for (argc = 1; ; argc += 1)
  {
    LPTSTR szParam = strtok(NULL, WHITESPACE);
    if (szParam == NULL)
      break;
    
    argv[argc] = szParam;
  }
  
  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] == '/')
      argv[i][0] = '-';     /* Canonicalize commands */
    
    if (streq (argv [i], "-asm")
      || streq (argv [i], "-a"))
    {
      bare_machine = 0;
      delayed_branches = 0;
      delayed_loads = 0;
    }
    else if (streq (argv [i], "-bare")
      || streq (argv [i], "-b"))
    {
      bare_machine = 1;
      delayed_branches = 1;
      delayed_loads = 1;
      quiet = 1;
    }
    else if (streq (argv [i], "-delayed_branches")
      || streq (argv [i], "-db"))
    { delayed_branches = 1; }
    else if (streq (argv [i], "-delayed_loads")
      || streq (argv [i], "-dl"))
    { delayed_loads = 1; }
    else if (streq (argv [i], "-exception")
      || streq (argv [i], "-e"))
    { g_fLoadExceptionHandler = 1; }
    else if (streq (argv [i], "-noexception")
      || streq (argv [i], "-ne"))
    { g_fLoadExceptionHandler = 0; }
    else if (streq (argv [i], "-exception_file")
      || streq (argv [i], "-ef"))
    {
      exception_file_name = argv[++i];
      g_fLoadExceptionHandler = 1;
    }
    else if (streq (argv [i], "-mapped_io")
      || streq (argv [i], "-mio"))
    { mapped_io = 1; }
    else if (streq (argv [i], "-nomapped_io")
      || streq (argv [i], "-nmio"))
    { mapped_io = 0; }
    else if (streq (argv [i], "-pseudo")
      || streq (argv [i], "-p"))
    { accept_pseudo_insts = 1; }
    else if (streq (argv [i], "-nopseudo")
      || streq (argv [i], "-np"))
    { accept_pseudo_insts = 0; }
    else if (streq (argv [i], "-quiet")
      || streq (argv [i], "-q"))
    { quiet = 1; }
    else if (streq (argv [i], "-noquiet")
      || streq (argv [i], "-nq"))
    { quiet = 0; }
    else if (streq (argv [i], "-stext")
      || streq (argv [i], "-st"))
    { initial_text_size = atoi (argv[++i]); }
    else if (streq (argv [i], "-sdata")
      || streq (argv [i], "-sd"))
    { initial_data_size = atoi (argv[++i]); }
    else if (streq (argv [i], "-ldata")
      || streq (argv [i], "-ld"))
    { initial_data_limit = atoi (argv[++i]); }
    else if (streq (argv [i], "-sstack")
      || streq (argv [i], "-ss"))
    { initial_stack_size = atoi (argv[++i]); }
    else if (streq (argv [i], "-lstack")
      || streq (argv [i], "-ls"))
    { initial_stack_limit = atoi (argv[++i]); }
    else if (streq (argv [i], "-sktext")
      || streq (argv [i], "-skt"))
    { initial_k_text_size = atoi (argv[++i]); }
    else if (streq (argv [i], "-skdata")
      || streq (argv [i], "-skd"))
    { initial_k_data_size = atoi (argv[++i]); }
    else if (streq (argv [i], "-lkdata")
      || streq (argv [i], "-lkd"))
    { initial_k_data_limit = atoi (argv[++i]); }
    else if ((streq (argv [i], "-file")
      || streq (argv [i], "-f"))
      && (i + 1 < argc))
    {
      m_strCurFilename = argv[++i];
      
      g_strCmdLine = "";
      for (int j = i; j < argc; j++)
      {
	g_strCmdLine += argv[j];
	g_strCmdLine += " ";
      }
      g_strCmdLine.TrimRight();
      break;
    }
    else if (argv [i][0] != '-')
    {
    /* Assume this is a file name and everything else are arguments
	     to program */
      m_strCurFilename = argv[++i];
      
      g_strCmdLine = "";
      for (int j = i; j < argc; j++)
      {
	g_strCmdLine += argv[j];
	g_strCmdLine += " ";
      }
      g_strCmdLine.TrimRight();
      break;
    }
    else
      goto l_ErrorMsg;
    }
    
    return;
    
l_ErrorMsg:
  CString strMsg;
  strMsg.Format("Error processing command line option #%d: \"%s\"\n"
		"Usage: spim \n\
	   -bare			Bare machine (no pseudo-ops, delayed branches and loads)\n\
	   -asm			Extended machine (pseudo-ops, no delayed branches and loads) (default)\n\
	   -delayed_branches	Execute delayed branches\n\
	   -delayed_loads		Execute delayed loads\n\
	   -exception		Load exception handler (default)\n\
	   -noexception		Do not load exception handler\n\
	   -exception_file <file>	Specify exception handler in place of default\n\
	   -quiet			Do not print warnings\n\
	   -noquiet		Print warnings (default)\n\
	   -mapped_io		Enable memory-mapped IO\n\
	   -nomapped_io		Do not enable memory-mapped IO (default)\n\
	   -file <file> <args>	Assembly code file and arguments to program\n"
		"Note that if -file is specified, it must be the last option.",
		i,
		argv[i],
		argv[0]);

  MessageBox(strMsg, "PCSpim -- Error processing command line.",
	     MB_OK | MB_ICONEXCLAMATION);

  exit(-1);
}


void CPCSpimView::OnDestroy()
{
  CPCSpimApp *pApp = (CPCSpimApp *)AfxGetApp();
  WINDOWPLACEMENT wp;

  if (g_fSaveWinPos)
    {
      // Save the main window's position
      AfxGetMainWnd()->GetWindowPlacement(&wp);
      pApp->WriteSetting(SPIM_REG_MAINWINPOS, &wp.rcNormalPosition);

      // Save the child windows positions
      m_wndConsole.GetWindowPlacement(&wp);
      pApp->WriteSetting(SPIM_REG_CONSOLEPOS, &wp.rcNormalPosition);

      m_wndDataSeg.GetWindowPlacement(&wp);
      pApp->WriteSetting(SPIM_REG_DATASEGPOS, &wp.rcNormalPosition);
      pApp->WriteSetting(SPIM_REG_DATASEGMINMAX, wp.showCmd);

      m_wndMessages.GetWindowPlacement(&wp);
      pApp->WriteSetting(SPIM_REG_MESSAGESPOS, &wp.rcNormalPosition);
      pApp->WriteSetting(SPIM_REG_MESSAGESMINMAX, wp.showCmd);

      m_wndRegisters.GetWindowPlacement(&wp);
      pApp->WriteSetting(SPIM_REG_REGISTERSPOS, &wp.rcNormalPosition);
      pApp->WriteSetting(SPIM_REG_REGISTERSMINMAX, wp.showCmd);

      m_wndTextSeg.GetWindowPlacement(&wp);
      pApp->WriteSetting(SPIM_REG_TEXTSEGPOS, &wp.rcNormalPosition);
      pApp->WriteSetting(SPIM_REG_TEXTSEGMINMAX, wp.showCmd);
    }

  pApp->WriteSetting(SPIM_REG_CHECK_UNDEF, g_checkUndefinedSymbols);

  CView::OnDestroy();
}


// NOTE:  If this is called with a valid CDC, it will _not_
// output to the FILE*, even if it is valid.
void CPCSpimView::OutputLog(CString &strBuf)
{
  CString strTemp;

  strBuf.Empty();

#define LINE_SEPARATOR "\n=========================\n"

  m_wndMessages.GetWindowText(strTemp);
  strBuf += "Messages" LINE_SEPARATOR + strTemp + "\n\n";

  m_wndRegisters.GetWindowText(strTemp);
  strBuf += "Registers" LINE_SEPARATOR + strTemp + "\n\n";

  m_wndConsole.GetWindowText(strTemp);
  strBuf += "Console" LINE_SEPARATOR + strTemp + "\n\n";

  m_wndTextSeg.GetWindowText(strTemp);
  strBuf += "Text Segment" LINE_SEPARATOR + strTemp + "\n\n";

  m_wndDataSeg.GetWindowText(strTemp);
  strBuf += "Data Segment" LINE_SEPARATOR + strTemp + "\n\n";
}


void CPCSpimView::OnWindowArrangeicons()
{
  ArrangeIconicWindows();
}


void CPCSpimView::OnFileSaveLog()
{
  CString strBuf;
  LPTSTR szBuf;

  CFileDialog dlg(FALSE, NULL, "PCSpim.log");
  dlg.m_ofn.lpstrFilter = "Log Files (*.log)\0*.log\0Text Files (*.txt)\0*.txt\0\0";
  dlg.DoModal();

  FILE *f = fopen(dlg.GetPathName(), "wb");
  OutputLog(strBuf);
  szBuf = strBuf.GetBuffer(0);
  while (*szBuf != NULL)
    {
      if (*szBuf == '\n')
	fputs("\r\n", f);
      else if (*szBuf == '\t')
	fputs("        ", f);
      else if (*szBuf != '\r')
	fputc(*szBuf, f);

      ++szBuf;
    }
  strBuf.ReleaseBuffer();
  fclose(f);
}


CFont* CPCSpimView::GetSpimFont()
{
  return m_wndTextSeg.GetFont();
}


void CPCSpimView::SetSpimFont(LOGFONT* lf)
{
  CFont* font = new CFont;
  VERIFY(font->CreateFontIndirect(lf));  // create the font

  m_wndMessages.SetFont(font, TRUE);
  m_wndRegisters.SetFont(font, TRUE);
  m_wndConsole.SetFont(font, TRUE);
  m_wndTextSeg.SetFont(font, TRUE);
  m_wndDataSeg.SetFont(font, TRUE);

  CPCSpimApp *pApp = (CPCSpimApp *)AfxGetApp();
  pApp->WriteSetting(SPIM_REG_FONTFACE, lf->lfFaceName );
  pApp->WriteSetting(SPIM_REG_FONTHEIGHT, lf->lfHeight);
  pApp->WriteSetting(SPIM_REG_FONTWEIGHT, lf->lfWeight);
  pApp->WriteSetting(SPIM_REG_FONTITALIC, lf->lfItalic);
}
