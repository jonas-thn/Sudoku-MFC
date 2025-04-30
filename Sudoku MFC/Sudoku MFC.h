#pragma once

#ifndef __AFXWIN_H__
	#error "'pch.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		

class CSudokuMFCApp : public CWinApp
{
public:
	CSudokuMFCApp();

public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

extern CSudokuMFCApp theApp;
