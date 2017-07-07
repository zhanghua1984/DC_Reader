// Reader.h : main header file for the Reader application
//

#if !defined(AFX_COMMTEST_H__094EF004_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_)
#define AFX_COMMTEST_H__094EF004_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CReaderApp:
// See Reader.cpp for the implementation of this class
//

class CReaderApp : public CWinApp
{
public:
	CReaderApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CReaderApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CReaderApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_READER_H__094EF004_CBE0_11D7_B4F9_00E04C74763F__INCLUDED_)
