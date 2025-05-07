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
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
END_MESSAGE_MAP()

BOOL CSudokuMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	LONG style = GetStyle();
	style &= ~WS_THICKFRAME;  //resize frame negieren / deaktivieren       
	SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

	sudoku.Init();
	sudoku.LoadFromFile("./sudokus/Sudoku1.txt", "./sudokus/Sudoku1_Save.txt");
	userInterface.InitUnserInerface();
	userInterface.UpdateSudoku(sudoku.GetFields());

	SetWindowPos(nullptr, 0, 0, 469, 570, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	MoveWindow(0, 0, 469, 570, TRUE);

	SetTimer(1, 100, nullptr);

	return TRUE; 
}

void CSudokuMFCDlg::OnPaint()
{
	CPaintDC dc(this);

	if (!IsIconic())
	{
		userInterface.GetSpriteList().RedrawAll(&dc, 0, 0);
	}

	CDialogEx::OnPaint();
}

void CSudokuMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{


	CDialogEx::OnLButtonDown(nFlags, point);
}

void CSudokuMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int i = 0;

	Update();
	Draw();

	i++;
	CDialogEx::OnTimer(nIDEvent);
}

void CSudokuMFCDlg::Update()
{

}

void CSudokuMFCDlg::Draw()
{
	CClientDC dc(this);
	userInterface.GetSpriteList().Update(&dc, 0, 0);
}
