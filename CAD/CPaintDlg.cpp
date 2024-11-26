// CPaintDlg.cpp: 实现文件
//

#include "pch.h"
#include "CAD.h"
#include "afxdialogex.h"
#include "CPaintDlg.h"


// CPaintDlg 对话框

IMPLEMENT_DYNAMIC(CPaintDlg, CDialogEx)

CPaintDlg::CPaintDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PAINT, pParent)
	, m_nWidth(0)
{

}

CPaintDlg::~CPaintDlg()
{
}

void CPaintDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STYLE, m_cmbStyle);
	DDX_Text(pDX, IDC_WIDTH_EDIT, m_nWidth);
	DDX_Control(pDX, IDC_COLOR_BUTTON, m_clrbPen);
}


BEGIN_MESSAGE_MAP(CPaintDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CPaintDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPaintDlg 消息处理程序



void CPaintDlg::OnBnClickedOk()
{
	//获取数据
	UpdateData(TRUE);

	m_clrPen = m_clrbPen.GetColor();  //更新颜色
	m_nPenStyle = m_cmbStyle.GetCurSel();  //更新风格
	CDialogEx::OnOK();
}

BOOL CPaintDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
  //#define PS_SOLID            0
  //#define PS_DASH             1       /* -------  */
  //#define PS_DOT              2       /* .......  */
  //#define PS_DASHDOT          3       /* _._._._  */
  //#define PS_DASHDOTDOT       4       /* _.._.._  */
	m_cmbStyle.AddString("————");
	m_cmbStyle.AddString("-------");
	m_cmbStyle.AddString(".......");
	m_cmbStyle.AddString("_._._._");
	m_cmbStyle.AddString("_.._.._");
	m_cmbStyle.AddString("       ");

	//设置初值
	m_cmbStyle.SetCurSel(m_nPenStyle);
	m_clrbPen.SetColor(m_clrPen);

	m_clrbPen.EnableOtherButton("其它");  //禁用其他

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


