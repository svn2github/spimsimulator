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

/* $Header: /Software/SPIM/PCSpim/SetValueDlg.cpp 6     3/14/04 7:51p Larus $ */

// SetValueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PCSpim.h"
#include "SetValueDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetValueDlg dialog


CSetValueDlg::CSetValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetValueDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSetValueDlg)
	m_strAddress = _T("");
	m_strValue = _T("");
	//}}AFX_DATA_INIT
}


void CSetValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetValueDlg)
	DDX_Text(pDX, IDC_ADDRESS, m_strAddress);
	DDX_Text(pDX, IDC_VALUE, m_strValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetValueDlg, CDialog)
	//{{AFX_MSG_MAP(CSetValueDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetValueDlg message handlers

void CSetValueDlg::OnOK()
{
  int reg_no;
  char *eptr;
  char *szAddress;

  UpdateData();

  m_strAddress.MakeLower();

  int nValue = strtol(m_strValue, &eptr, 0);

  szAddress = m_strAddress.GetBuffer(0);
  reg_no = register_name_to_number(szAddress);
  m_strAddress.ReleaseBuffer();

  if (reg_no < 0)
    {
      if (m_strAddress[0] == '$' || m_strAddress[0] == 'r')
	{
	  szAddress = m_strAddress.GetBuffer(0);
	  reg_no = register_name_to_number(szAddress + 1);
	  m_strAddress.ReleaseBuffer();
	}
    }

  if (reg_no == 0)
    {
      MessageBox("Cannot modify register 0.");
      return;
    }
  else if (reg_no > 0)
    R[reg_no] = nValue;
  else if (streq(m_strAddress, "status"))
    CP0_Status = nValue;
  else if (streq(m_strAddress, "pc"))
    PC = nValue;
  else if (streq (m_strAddress, "epc"))
    CP0_EPC = nValue;
  else
    {
      mem_addr addr;

      /* Try to parse string as a number */
      addr = strtoul(m_strAddress, &eptr, 0);
      if (eptr == m_strAddress)
	{
	  MessageBox("Please enter either a register name or a valid address.");
	  return;
	}
      else
	set_mem_word (addr, nValue);
    }

  CDialog::OnOK();
}
