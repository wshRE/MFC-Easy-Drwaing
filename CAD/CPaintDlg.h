#pragma once
#include "afxdialogex.h"
#include "CMyColorButton.h"


// CPaintDlg 对话框

class CPaintDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPaintDlg)

public:
	CPaintDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPaintDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PAINT };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbStyle;  //风格
	int m_nWidth;          //宽度
	CMyColorButton m_clrbPen; //颜色

	int m_nPenStyle = PS_SOLID;  //	笔是实心的。
	COLORREF m_clrPen = RGB(0, 0, 0); //颜色为黑色

	afx_msg void OnBnClickedOk();  //确认
	virtual BOOL OnInitDialog();
};
