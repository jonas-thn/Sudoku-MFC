
// Sudoku MFC.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// CSudokuMFCApp:
// Siehe Sudoku MFC.cpp für die Implementierung dieser Klasse
//

class CSudokuMFCApp : public CWinApp
{
public:
	CSudokuMFCApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern CSudokuMFCApp theApp;
