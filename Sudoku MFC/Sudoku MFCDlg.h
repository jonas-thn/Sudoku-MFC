#pragma once
#include "spritelib.h"
#include <string>
#include "UserInterface.h"
#include "Sudoku.h"
#include "Undo.h"
#include "Solver.h"
#include "Random.h"

enum class TextState
{
	Normal,
	Save,
	Reset,
	Solved
};

class CSudokuMFCDlg : public CDialogEx
{
public:
	
	CSudokuMFCDlg(CWnd* pParent = nullptr, Difficulty difficulty = Difficulty::Easy);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SUDOKU_MFC_DIALOG };
#endif

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	virtual void DoDataExchange(CDataExchange* pDX);
	BOOL CSudokuMFCDlg::PreTranslateMessage(MSG* pMsg) override;
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	Sudoku sudoku;
	UserInterface userInterface;
	Solver solver;

	CStatic staticText;
	TextState textState = TextState::Normal;
	COLORREF textColor;
	CBrush bgBrush;
	int textTimer = 0;

	void SetText(const std::wstring& text, uint8_t r, uint8_t g, uint8_t b, TextState textState);

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	//Update und Render Loop
	void Update(int frame);
	void Draw();
	Difficulty difficulty = Difficulty::Easy;
public:
	//Botton Events
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
};
