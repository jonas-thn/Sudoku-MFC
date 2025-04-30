#pragma once
#include "spritelib.h"
#include <string>

class CSudokuMFCDlg : public CDialogEx
{
public:
	CSudokuMFCDlg(CWnd* pParent = nullptr);	

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

	CSprite background, dog;
	CDIB framebuffer;
	CSpriteList spriteList;

public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
