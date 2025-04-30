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

	if (!dog.Load("./sprites/dogs.bmp", CSize(187, 107)))
	{
		AfxMessageBox(L"Dog Error");
	}
	dog.SetZ((20));
	dog.SetPosition(-300, 120);

	if (!background.Load("./sprites/snow.bmp", CSize(450, 200)))
	{
		AfxMessageBox(L"BG Error");
	}
	background.SetZ(0);

	framebuffer.Load("./sprites/snow.bmp");

	spriteList.SetWorkspace(&framebuffer);
	spriteList.Insert(&dog);
	spriteList.Insert(&background);

	/*SetWindowPos(nullptr, 0, 0, background.DibWidth() + 100, background.DibHeight() + 100, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	MoveWindow(0, 0, background.DibWidth() + 100, background.DibHeight() + 100, TRUE);*/

	SetTimer(1, 100, nullptr);

	return TRUE; 
}

void CSudokuMFCDlg::OnPaint()
{
	CPaintDC dc(this);

	if (!IsIconic())
	{
		spriteList.RedrawAll(&dc, 0, 0);
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
	CClientDC dc(this);

	dog.SetSpriteNumber(0, i % 7);
	if (dog.GetXPos() > background.DibWidth())
	{
		dog.SetPosition(-300, 120);
	}
	else
	{
		dog.SetPosition(dog.GetXPos() + 40, dog.GetYPos());
	}
	spriteList.Update(&dc, 0, 0);
	i++;

	CDialogEx::OnTimer(nIDEvent);
}
