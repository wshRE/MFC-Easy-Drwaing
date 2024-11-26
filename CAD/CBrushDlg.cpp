// CBrushDlg.cpp: 实现文件
//

#include "pch.h"
#include "CAD.h"
#include "afxdialogex.h"
#include "CBrushDlg.h"


// CBrushDlg 对话框

IMPLEMENT_DYNAMIC(CBrushDlg, CDialogEx)

CBrushDlg::CBrushDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_BRUSH, pParent)
{

}

CBrushDlg::~CBrushDlg()
{
}

void CBrushDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCCOLOR_BUTTON, m_clrbBrush);
	DDX_Control(pDX, IDC_COMBO_FIGURE, m_cmbFigure);
}

BOOL CBrushDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//#define HS_HORIZONTAL       0       /* ----- */
//#define HS_VERTICAL         1       /* ||||| */
//#define HS_FDIAGONAL        2       /* \\\\\ */
//#define HS_BDIAGONAL        3       /* ///// */
//#define HS_CROSS            4       /* +++++ */
//#define HS_DIAGCROSS        5       /* xxxxx */
//#define HS_API_MAX          12
	m_cmbFigure.AddString("-----");
	m_cmbFigure.AddString("|||||");
	m_cmbFigure.AddString("\\\\\\\\");
	m_cmbFigure.AddString("/////");
	m_cmbFigure.AddString("+++++");
	m_cmbFigure.AddString("xxxxx");
	m_cmbFigure.AddString("     ");
	//初值
	m_cmbFigure.SetCurSel(m_nPenFigure);
	m_clrbBrush.SetColor(m_clrBrush);
	m_clrbBrush.EnableOtherButton("其它");  //禁用其他
	return TRUE;
}


BEGIN_MESSAGE_MAP(CBrushDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CBrushDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CBrushDlg 消息处理程序


void CBrushDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);

	m_clrBrush = m_clrbBrush.GetColor();  //更新颜色
	m_nPenFigure = m_cmbFigure.GetCurSel();  //更新风格
	CDialogEx::OnOK();
}
