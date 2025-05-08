#pragma once
#include "afxdialogex.h"
#include "Sudoku.h"


// MenuMFC-Dialog

class MenuMFC : public CDialogEx
{
	DECLARE_DYNAMIC(MenuMFC)

public:
	MenuMFC(CWnd* pParent = nullptr);   // Standardkonstruktor
	virtual ~MenuMFC();

// Dialogfelddaten
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU_MFC_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung

	DECLARE_MESSAGE_MAP()
public:
	void OpenSudoku(Difficulty difficulty);

	afx_msg void OnBnClickedButton1();

	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
