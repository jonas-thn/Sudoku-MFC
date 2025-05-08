#pragma once
#include "spritelib.h"
#include <string>
#include "UserInterface.h"
#include "Sudoku.h"
#include "Undo.h"
#include "Solver.h"

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

	Sudoku sudoku;
	UserInterface userInterface;
	Solver solver;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

private:
	void Update();
	void Draw();
	Difficulty difficulty = Difficulty::Easy;
public:
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
};
