#include "pch.h"
#include "framework.h"
#include "Sudoku MFC.h"
#include "Sudoku MFCDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "MenuMFC.h"

CSudokuMFCDlg::CSudokuMFCDlg(CWnd* pParent, Difficulty difficulty)
	: CDialogEx(IDD_SUDOKU_MFC_DIALOG, pParent)
{
	this->difficulty = difficulty;
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
	ON_BN_CLICKED(IDC_BUTTON5, &CSudokuMFCDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON2, &CSudokuMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CSudokuMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CSudokuMFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CSudokuMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSudokuMFCDlg::OnBnClickedButton4)
END_MESSAGE_MAP()

BOOL CSudokuMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	LONG style = GetStyle();
	style &= ~WS_THICKFRAME;  //resize frame negieren / deaktivieren       
	SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

	sudoku.Init(difficulty);
	sudoku.LoadFromFile();
	userInterface.Init(sudoku.GetFields());

	SetWindowPos(nullptr, 0, 0, 469, 570, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	MoveWindow(0, 0, 469, 570, TRUE);

	SetTimer(1, 100, nullptr);

	//Menü schließen
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd)
	{
		pMainWnd->PostMessage(WM_CLOSE);
	}

	//Sudoku zu neuem main window machen
	AfxGetApp()->m_pMainWnd = this;

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
	//w: 453 h:435
	Vec2 position = userInterface.ConvertCoordinatesToPosition(Vec2(point.x, point.y));
	userInterface.SetBorder(position);

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

void CSudokuMFCDlg::OnBnClickedButton5()
{
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd)
	{
		pMainWnd->PostMessage(WM_CLOSE);
	}
}

BOOL CSudokuMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam >= '0' && pMsg->wParam <= '9')
		{
			char key = (char)pMsg->wParam;
			userInterface.SetField(userInterface.GetLastMousePos(), key);
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

//RESET
void CSudokuMFCDlg::OnBnClickedButton2()
{
	sudoku.ClearSudoku();
	userInterface.CompleteUpdate(sudoku.GetFields());
}

//SAVE
void CSudokuMFCDlg::OnBnClickedButton1()
{
	sudoku.FillFieldBuffer(userInterface.GetTempFieldBuffer());
	sudoku.SaveToFile();
}

//LOAD
void CSudokuMFCDlg::OnBnClickedButton6()
{
	MenuMFC dlg;

	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd)
	{
		pMainWnd->PostMessage(WM_CLOSE);
	}

	//Menu zu neuem main window machen
	AfxGetApp()->m_pMainWnd = &dlg;

	INT_PTR nResponse = dlg.DoModal();

}

//UNDO
void CSudokuMFCDlg::OnBnClickedButton3()
{
	userInterface.TriggerUndo();
}

//SOLVE
void CSudokuMFCDlg::OnBnClickedButton4()
{
	
}
