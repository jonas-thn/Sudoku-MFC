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
	textColor = RGB(0, 0, 0); 
	bgBrush.CreateSolidBrush(RGB(255, 255, 255));
}

void CSudokuMFCDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_STATIC, staticText);
}

BEGIN_MESSAGE_MAP(CSudokuMFCDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON2, &CSudokuMFCDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CSudokuMFCDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON6, &CSudokuMFCDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON3, &CSudokuMFCDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CSudokuMFCDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CSudokuMFCDlg::OnBnClickedButton5)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

BOOL CSudokuMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	LONG style = GetStyle();
	style &= ~WS_THICKFRAME;  //resize frame negieren / deaktivieren       
	SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

	try
	{
		sudoku.Init(difficulty);
		sudoku.LoadFromFile();
		userInterface.Init(sudoku.GetFields(), sudoku.GetEditFields());
		solver.Init(sudoku.GetCurrentFileData().original);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}

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

	CenterWindow();

	return TRUE; 
}

HBRUSH CSudokuMFCDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_STATIC)
	{
		pDC->SetTextColor(textColor);
		pDC->SetBkMode(TRANSPARENT);
		return bgBrush;
	}

	return hbr;
}

void CSudokuMFCDlg::OnPaint()
{
	CPaintDC dc(this);

	if (!IsIconic())
	{
		try
		{
			userInterface.GetSpriteList().RedrawAll(&dc, 0, 0);
		}
		catch (const std::exception& e)
		{
			MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
			::PostQuitMessage(1);
		}
	}

	CDialogEx::OnPaint();
}

void CSudokuMFCDlg::SetText(const std::wstring& text, uint8_t r, uint8_t g, uint8_t b, TextState textSate)
{
	textState = TextState::Save;
	staticText.SetWindowTextW(text.data());
	textColor = RGB(r, g, b);
	staticText.Invalidate();
	textTimer = 0;
}

void CSudokuMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	try
	{
		Vec2 position = userInterface.ConvertCoordinatesToPosition(Vec2(point.x, point.y));
		userInterface.SetBorder(position);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CSudokuMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int i = 0;

	Update(i);
	Draw();

	i++;
	CDialogEx::OnTimer(nIDEvent);
}

void CSudokuMFCDlg::Update(int frame) 
{
	textTimer++;
	if (textState != TextState::Normal && textTimer > 20)
	{
		SetText(L"Select a field and type a number 1-9!", 0, 0, 0, TextState::Normal);
	}
}

void CSudokuMFCDlg::Draw()
{
	CClientDC dc(this);

	try
	{
		userInterface.GetSpriteList().Update(&dc, 0, 0);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}
}

BOOL CSudokuMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam >= '0' && pMsg->wParam <= '9')
		{
			char key = (char)pMsg->wParam;

			try
			{
				userInterface.SetField(userInterface.GetLastMousePos(), key);
			}
			catch (const std::exception& e)
			{
				MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
				::PostQuitMessage(1);
			}

			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

//RESET
void CSudokuMFCDlg::OnBnClickedButton2()
{
	SetText(L"Current Sudoku has been reset to its original values!", 0, 0, 200, TextState::Reset);

	try
	{
		sudoku.ClearSudoku();
		userInterface.CompleteUpdate(sudoku.GetFields());
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}
}

//SAVE
void CSudokuMFCDlg::OnBnClickedButton1()
{
	SetText(L"Current Sudoku is being saved!", 0, 150, 0, TextState::Save);

	try
	{
		sudoku.FillFieldBuffer(userInterface.GetTempFieldBuffer());
		sudoku.SaveToFile();
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}
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
	SetText(L"The sudoku is now solved. Congratulations!", 212, 157, 19, TextState::Solved);

	try
	{
		if (!solver.SolveSudoku())
		{
			MessageBoxA(nullptr, "Not solvable", "Error", MB_OK | MB_ICONERROR);
		}
		userInterface.CompleteUpdate(solver.GetBuffer());
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}
}

//EXIT
void CSudokuMFCDlg::OnBnClickedButton5()
{
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd)
	{
		pMainWnd->PostMessage(WM_CLOSE);
	}
}
