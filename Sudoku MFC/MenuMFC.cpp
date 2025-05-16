// MenuMFC.cpp: Implementierungsdatei

#include "pch.h"
#include "Sudoku MFC.h"
#include "afxdialogex.h"
#include "MenuMFC.h"
#include "Sudoku MFCDlg.h"


// MenuMFC-Dialog

IMPLEMENT_DYNAMIC(MenuMFC, CDialogEx)

MenuMFC::MenuMFC(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MENU_MFC_DIALOG, pParent)
{
}

MenuMFC::~MenuMFC()
{
}

void MenuMFC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(MenuMFC, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &MenuMFC::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &MenuMFC::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &MenuMFC::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &MenuMFC::OnBnClickedButton4)
END_MESSAGE_MAP()

void MenuMFC::OpenSudoku(Difficulty difficulty)
{
	CSudokuMFCDlg dlg(nullptr, difficulty);
	INT_PTR nResponse = dlg.DoModal();
}

void MenuMFC::OnBnClickedButton1()
{
	OpenSudoku(Difficulty::Easy);
}

void MenuMFC::OnBnClickedButton2()
{
	OpenSudoku(Difficulty::Medium);
}

void MenuMFC::OnBnClickedButton3()
{
	OpenSudoku(Difficulty::Hard);
}

void MenuMFC::OnBnClickedButton4()
{
	OpenSudoku(Difficulty::Impossible);
}

