#include "pch.h"
#include "framework.h"
#include "Sudoku MFCDlg.h"
#include "Sudoku MFC.h"
#include "MenuMFC.h"	

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CSudokuMFCApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CSudokuMFCApp::CSudokuMFCApp()
{
	
}

CSudokuMFCApp theApp;

BOOL CSudokuMFCApp::InitInstance()
{
	CWinApp::InitInstance();

	//App mit Menü starten
	MenuMFC menu;
	m_pMainWnd = &menu;
	INT_PTR nResponse = menu.DoModal();

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	return FALSE;
}



