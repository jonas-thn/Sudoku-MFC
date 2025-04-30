
#include "pch.h"
#include "framework.h"
#include "Sudoku MFC.h"
#include "Sudoku MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CSudokuMFCDlg::CSudokuMFCDlg(CWnd* pParent)
	: CDialogEx(IDD_SUDOKU_MFC_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSudokuMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSudokuMFCDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()

BOOL CSudokuMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	return TRUE; 
}

void CSudokuMFCDlg::OnPaint()
{
	CPaintDC dc(this);
	dc.TextOutW(0, 0, _T("Sudoku MFC"));
}




