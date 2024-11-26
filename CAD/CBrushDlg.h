#pragma once
#include "afxdialogex.h"
#include "CMyColorButton.h"


// CBrushDlg 对话框

class CBrushDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBrushDlg)

public:
	CBrushDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CBrushDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BRUSH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CMyColorButton m_clrbBrush; //颜色
	CComboBox m_cmbFigure;      //花纹
	virtual BOOL OnInitDialog();

	//初值
	int m_nPenFigure = HS_API_MAX;  //空白不填充
	COLORREF m_clrBrush = RGB(0, 0, 0);
	afx_msg void OnBnClickedOk();
};
