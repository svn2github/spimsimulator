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

/* $Header: /Software/SPIM/SPIM/PCSpim/MultiStepDlg.cpp 1     1/02/05 8:03p Larus $ */

// MultiStepDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "MultiStepDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMultiStepDlg dialog


CMultiStepDlg::CMultiStepDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMultiStepDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMultiStepDlg)
	m_cSteps = 0;
	//}}AFX_DATA_INIT
}


void CMultiStepDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMultiStepDlg)
	DDX_Text(pDX, IDC_STEPS, m_cSteps);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMultiStepDlg, CDialog)
	//{{AFX_MSG_MAP(CMultiStepDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMultiStepDlg message handlers
