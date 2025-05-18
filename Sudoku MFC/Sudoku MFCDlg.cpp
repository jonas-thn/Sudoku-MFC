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
	//Schwierigkeit, Icon und Textfarbe initialisieren
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

// CSudokuMFCDlg Initialisierung
BOOL CSudokuMFCDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	//Resize deaktivieren
	LONG style = GetStyle();
	style &= ~WS_THICKFRAME;  //thickframe negieren
	SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

	try
	{
		//Objekte initialisieren
		sudoku.Init(difficulty);
		sudoku.LoadFromFile();
		solver.Init(sudoku.GetCurrentFileData().original);
		userInterface.Init(sudoku.GetFields(), sudoku.GetEditFields());
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}

	//timer event alle 100ms
	SetTimer(1, 100, nullptr);

	//Menü schließen
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd)
	{
		pMainWnd->PostMessage(WM_CLOSE);
	}

	//Sudoku zu neuem main window machen
	AfxGetApp()->m_pMainWnd = this;

	//Fenster Größe und Position setzen
	SetWindowPos(nullptr, 0, 0, 469, 570, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
	MoveWindow(0, 0, 469, 570, TRUE);
	CenterWindow();

	return TRUE; 
}

//Text Farbe aktualisieren
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

//Fenster Inhalt neu zeichnen
void CSudokuMFCDlg::OnPaint()
{
	CPaintDC dc(this);

	if (!IsIconic())
	{
		try
		{
			//Sprites neu zeichnen
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

//Static Text setzen
void CSudokuMFCDlg::SetText(const std::wstring& text, uint8_t r, uint8_t g, uint8_t b, TextState textSate)
{
	//Zustand, Farbe und Inhalt ändern
	textState = TextState::Save;
	staticText.SetWindowTextW(text.data());
	textColor = RGB(r, g, b);
	staticText.Invalidate();
	textTimer = 0;
}

//Linksclick
void CSudokuMFCDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	try
	{
		//Koordinaten umwandeln und Umrandung setzen
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

//Timer Event
void CSudokuMFCDlg::OnTimer(UINT_PTR nIDEvent)
{
	static int i = 0; //Frame counter

	//Update und Render Loop
	Update(i);
	Draw();

	i++;

	CDialogEx::OnTimer(nIDEvent);
}

void CSudokuMFCDlg::Update(int frame) 
{
	//Text nach Änderung für 30 Frames (3 Sekunden) anzeigen
	textTimer++;
	if (textState != TextState::Normal && textTimer > 30)
	{
		SetText(L"Select a field and type a number 1-9!", 0, 0, 0, TextState::Normal);
	}
}

void CSudokuMFCDlg::Draw()
{
	CClientDC dc(this);

	try
	{
		//Geänderte Sprites neu zeichnen
		userInterface.GetSpriteList().Update(&dc, 0, 0);
	}
	catch (const std::exception& e)
	{
		MessageBoxA(nullptr, e.what(), "Error", MB_OK | MB_ICONERROR);
		::PostQuitMessage(1);
	}
}

//Tasteneingabe abfangen
BOOL CSudokuMFCDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam >= '0' && pMsg->wParam <= '9') //Eingabe Tastatur 1-9
		{
			char key = (char)pMsg->wParam;

			try
			{
				//Feld Eingabe setzen
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
		//Sudoku zurücksetzen und User Interface aktualisieren
		sudoku.ClearSudoku();
		userInterface.CompleteUpdate(sudoku.GetFields());
		userInterface.ClearUndo();
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
		//Sudoku speichern
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
	MenuMFC dlg; //Menu erstellen

	//Sudoku schließen
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
		//Sudoku lösen und User Interface aktualisieren
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
	//Dialog schließen
	CWnd* pMainWnd = AfxGetMainWnd();
	if (pMainWnd)
	{
		pMainWnd->PostMessage(WM_CLOSE);
	}
}
