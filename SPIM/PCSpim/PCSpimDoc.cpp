// PCSpimDoc.cpp : implementation of the CPCSpimDoc class
//

#include "stdafx.h"
#include "PCSpim.h"

#include "PCSpimDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPCSpimDoc

IMPLEMENT_DYNCREATE(CPCSpimDoc, CDocument)

BEGIN_MESSAGE_MAP(CPCSpimDoc, CDocument)
	//{{AFX_MSG_MAP(CPCSpimDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPCSpimDoc construction/destruction

CPCSpimDoc::CPCSpimDoc()
{
	// TODO: add one-time construction code here

}


CPCSpimDoc::~CPCSpimDoc()
{
}


BOOL CPCSpimDoc::OnNewDocument()
{
  if (!CDocument::OnNewDocument())
    return FALSE;

  // TODO: add reinitialization code here
  // (SDI documents will reuse this document)

  return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CPCSpimDoc serialization

void CPCSpimDoc::Serialize(CArchive& ar)
{
  if (ar.IsStoring())
    {
      // TODO: add storing code here
    }
  else
    {
      // TODO: add loading code here
    }
}


/////////////////////////////////////////////////////////////////////////////
// CPCSpimDoc diagnostics

#ifdef _DEBUG
void CPCSpimDoc::AssertValid() const
{
  CDocument::AssertValid();
}


void CPCSpimDoc::Dump(CDumpContext& dc) const
{
  CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPCSpimDoc commands
