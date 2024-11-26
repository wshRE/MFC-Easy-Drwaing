// CPaintView.cpp: 实现文件
//

#include "pch.h"
#include "CAD.h"
#include "CPaintView.h"
#include "Rotate.h"
#include "CPaintDlg.h"
#include "CBrushDlg.h"
#include "CADDoc.h"
constexpr auto M_PI = 3.1415926;
// CPaintView

IMPLEMENT_DYNCREATE(CPaintView, CFormView)

void CPaintView::RememberOld(std::shared_ptr<CShapeBase> pCurShape)
{
	//图形参数
	m_cOldStart = pCurShape->GetStart();//起点
	m_cOldEnd = pCurShape->GetEnd();  //终点
   //画笔参数
	m_nOldPenStyle = pCurShape->m_nPenStyle;
	m_nOldPenWidth = pCurShape->m_nPenWidth;
	m_clrOldPen = pCurShape->m_clrPen;
	//画刷配置
	m_nOldBrushFrigue = pCurShape->m_nBrushFrigue; //填充花纹
	m_clrOldBrush = pCurShape->m_clrBrush;//花纹颜色
}

BOOL CPaintView::iSIn(std::shared_ptr<CShapeBase> m_pCurShape)
{
	CPoint cBegin = m_pCurShape->GetStart();
	CPoint cEnd = m_pCurShape->GetEnd();
	if (cBegin.x >= m_pCurEidtShape->GetStart().x && cBegin.y >= m_pCurEidtShape->GetStart().y && cEnd.x <= m_pCurEidtShape->GetEnd().x && cEnd.y <= m_pCurEidtShape->GetEnd().y) {
		return TRUE;
	}
	return FALSE;
}

CPaintView::CPaintView()
	: CFormView(DLG_PAINT_VIEW)
{

}

CPaintView::~CPaintView()
{
}

void CPaintView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPaintView, CFormView)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CREATE()
	ON_COMMAND(MN_SHAPE_LINE, &CPaintView::OnShapeLine)
	ON_COMMAND(MN_SHAPE_RECT, &CPaintView::OnShapeRect)
	ON_COMMAND(MN_SHAPE_ELLI, &CPaintView::OnShapeElli)
	ON_COMMAND(ID_INEDIT, &CPaintView::OnInedit)
	ON_COMMAND(ID_WHRIL, &CPaintView::OnWhril)
	ON_COMMAND(ID_ENLARGE, &CPaintView::OnEnlarge)
	ON_COMMAND(ID_MOVE, &CPaintView::OnMove)
	ON_COMMAND(MN_INEDIT, &CPaintView::OnRBInedit)
	ON_COMMAND(MN_MOVE, &CPaintView::OnRBMove)
	ON_COMMAND(MN_ENLARGE, &CPaintView::OnRBEnlarge)
	ON_COMMAND(ID_ADVANCE, &CPaintView::OnAdvance)
	ON_COMMAND(ID_RETREAT, &CPaintView::OnRetreat)
	ON_COMMAND(ID_PAINT, &CPaintView::OnPaint)
	ON_COMMAND(ID_BRUSH, &CPaintView::OnBrush)
END_MESSAGE_MAP()


// CPaintView 诊断

#ifdef _DEBUG
void CPaintView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CPaintView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CPaintView 消息处理程序


void CPaintView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCADDoc* cDoc = (CCADDoc*)GetDocument();
	//1.画编辑框
	if (m_bIsEdit == TRUE) {
		m_pCurEidtShape = std::shared_ptr<CShapeBase>(pEditFactory->CreateShape());
		m_pCurEidtShape->SetStart(point);
		m_pCurEidtShape->SetPen(2, 7, RGB(142, 53, 74));
		m_pCurEidtShape->SetTp();
		//设置透明
		SetCapture();
		CView::OnLButtonDown(nFlags, point);
		return;
	}
	//2.调整姿态
	if (m_bIsChange && m_pCurEidtShape) {
		//记录起点----在移动部分对图形进行调整
		m_cStart = point;
		SetCapture();

		//图形捕获
		auto pos = cDoc->m_lstShapes.GetTailPosition();
		while (pos)
		{
			auto& pShape = cDoc->m_lstShapes.GetPrev(pos);
			//在图形内
			if (iSIn(pShape)) {
				m_pCurChooseShape = pShape; //指针指向图形
				RememberOld(m_pCurChooseShape);//记录图形旧状态
				break;
			}
		}
		CView::OnLButtonDown(nFlags, point);
		return;
	}
	//3.正常划线
	m_pCurShape = std::shared_ptr<CShapeBase>(pFactory->CreateShape());
	m_pCurShape->SetPen(m_nPenStyle, m_nPenWidth, m_clrPen);//画笔
	m_pCurShape->SetBrush(m_nPenFigure, m_clrBrush);//笔刷
	//设置第一个坐标
	m_pCurShape->SetStart(point);

	SetCapture();

	CFormView::OnLButtonDown(nFlags, point);
}
void CPaintView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CCADDoc* cDoc = (CCADDoc*)GetDocument();
	if (m_bIsEdit == TRUE && m_pCurEidtShape != nullptr) {
		m_pCurEidtShape->SetEnd(point);//存储直线终点
	}
	else if (m_bIsChange == TRUE) {
		//压栈
		std::shared_ptr<CBackTrack> ptrChange(new CBackTrack(m_pCurChooseShape, m_pCurChooseShape->GetStart(), m_pCurChooseShape->GetEnd(), m_cOldStart, m_cOldEnd,
			m_pCurChooseShape->m_nPenStyle, m_pCurChooseShape->m_nPenWidth, m_pCurChooseShape->m_clrPen, m_nOldPenStyle, m_nOldPenWidth, m_clrOldPen,
			m_pCurChooseShape->m_nBrushFrigue, m_pCurChooseShape->m_clrBrush, m_nOldBrushFrigue, m_clrOldBrush));
		m_stkToUndo.push(ptrChange);
	}
	else {
		if (m_pCurShape) {
			m_pCurShape->SetEnd(point);//存储直线终点
			//保存直线到链表
			cDoc->m_lstShapes.AddTail(m_pCurShape);
			//新链表入栈
			m_stkToUndo.push(shared_ptr<CBackTrack>(new CBackTrack(&(cDoc->m_lstShapes), m_pCurShape)));
			m_pCurShape = nullptr;
		}

	}

	//刷新客户区区
	InvalidateRect(NULL, FALSE);
	ReleaseCapture();

	CFormView::OnLButtonUp(nFlags, point);
}
void CPaintView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (nFlags & MK_LBUTTON)
	{
		CCADDoc* cDoc = (CCADDoc*)GetDocument();
		if (m_bIsEdit == TRUE) {
			m_pCurEidtShape->SetEnd(point);
			//刷新客户区区
			InvalidateRect(NULL, FALSE);
		}
		//三种操作
		else if (m_bIsChange == TRUE) {
			m_cEnd = point;
			//移动
			if (m_et == ET_MOVE) {
				CSize szOff = m_cEnd - m_cStart;
				m_pCurEidtShape->SetStart(m_pCurEidtShape->GetStart() + szOff);
				m_pCurEidtShape->SetEnd(m_pCurEidtShape->GetEnd() + szOff);

				//移动内部图像
				m_pCurChooseShape->SetStart(m_pCurChooseShape->GetStart() + szOff);
				m_pCurChooseShape->SetEnd(m_pCurChooseShape->GetEnd() + szOff);
				//更新起始点
				m_cStart = m_cEnd;
			}
			//变大变小
			else if (m_et == ET_ENLARGE) {
				//求改变的长度
				int nLength = m_cEnd.x - m_cStart.x;
				CPoint cstartbefore;
				cstartbefore.x = m_pCurEidtShape->GetStart().x - nLength;
				cstartbefore.y = m_pCurEidtShape->GetStart().y - nLength;
				CPoint cendbefore;
				cendbefore.x = m_pCurEidtShape->GetEnd().x + nLength;
				cendbefore.y = m_pCurEidtShape->GetEnd().y + nLength;

				m_pCurEidtShape->SetStart(cstartbefore);
				m_pCurEidtShape->SetEnd(cendbefore);

				//移动内部图像
				auto pos = cDoc->m_lstShapes.GetHeadPosition();
				while (pos)
				{
					auto& pShape = cDoc->m_lstShapes.GetNext(pos);
					//在图形内
					if (iSIn(pShape)) {
						//移动图形
						cstartbefore.x = pShape->GetStart().x - nLength;
						cstartbefore.y = pShape->GetStart().y - nLength;
						cendbefore.x = pShape->GetEnd().x + nLength;
						cendbefore.y = pShape->GetEnd().y + nLength;

						pShape->SetStart(cstartbefore);
						pShape->SetEnd(cendbefore);
					}
				}
				//更新起始点
				m_cStart = m_cEnd;
			}
			//旋转
			else {
				//旋转矩阵
				CPoint cstartbefore;
				cstartbefore.x = m_pCurEidtShape->GetStart().x;
				cstartbefore.y = m_pCurEidtShape->GetStart().y;
				CPoint cendbefore;
				cendbefore.x = m_pCurEidtShape->GetEnd().x;
				cendbefore.y = m_pCurEidtShape->GetEnd().y;

				rotate(cstartbefore, cendbefore, PI / 2);

				m_pCurEidtShape->SetStart(cstartbefore);
				m_pCurEidtShape->SetEnd(cendbefore);
				/*移动内部图形---未完成*/
				//更新起始点
				m_cStart = m_cEnd;
			}
			InvalidateRect(NULL, FALSE);
		}
		else {
			//移动中的每个点作为直线的终点，用于实现直线跟随鼠标的效果
			if (m_pCurShape) {
				m_pCurShape->SetEnd(point);
				//刷新客户区区
				InvalidateRect(NULL, FALSE);
			}

		}
	}

	CFormView::OnMouseMove(nFlags, point);
}



//起始
int CPaintView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	/*CCADDoc* cDoc = (CCADDoc*)GetDocument();*/
	// TODO:  在此添加您专用的创建代码
	/*ini初始化*/
	
	return 0;
}

//图形选择按钮
void CPaintView::OnShapeLine()
{
	// TODO: 在此添加命令处理程序代码
	m_st = ST_LINE;
	pFactory = new CLineFac;
	m_bIsEdit = FALSE;
	m_bIsChange = FALSE;
}
void CPaintView::OnShapeRect()
{
	// TODO: 在此添加命令处理程序代码
	m_st = ST_RECT;
	pFactory = new CRectFac(4);
	m_bIsEdit = FALSE;
	m_bIsChange = FALSE;
}
void CPaintView::OnShapeElli()
{
	// TODO: 在此添加命令处理程序代码
	m_st = ST_ELLP;
	pFactory = new CElliFac;
	m_bIsEdit = FALSE;
	m_bIsChange = FALSE;
}

//修改编辑状态
void CPaintView::OnInedit()
{
	CCADDoc* cDoc = (CCADDoc*)GetDocument();
	if (cDoc->m_lstShapes.IsEmpty()) {
		AfxMessageBox("ERROR：当前页面没有图形，不允许进入编辑状态");
		return;
	}
	m_bIsEdit = TRUE;
	m_bIsChange = FALSE;
	AfxMessageBox("TIP：进入编辑选项后，可以在界面中画出选择的矩形框，之后选择移动等可以对矩形内的图形进行操作");
}

//变化
void CPaintView::OnWhril()
{
	if (m_pCurEidtShape == nullptr) {
		AfxMessageBox("ERROR:当前界面没有编辑框，请先画出选择的区域");
		return;
	}
	m_bIsEdit = FALSE;  //关闭编辑状态
	m_bIsChange = TRUE; //开启变化状态
	m_et = ET_WHIRL; //当前移动状态
	m_xzds = 0;  //当前旋转角度
}
void CPaintView::OnEnlarge()
{
	if (m_pCurEidtShape == nullptr) {
		AfxMessageBox("ERROR:当前界面没有编辑框，请先画出选择的区域");
		return;
	}
	m_bIsEdit = FALSE;  //关闭编辑状态
	m_bIsChange = TRUE; //开启变化状态
	m_et = ET_ENLARGE; //当前移动状态
	nLastEnLarge = 0; //放缩改为0
}
void CPaintView::OnMove()
{
	if (m_pCurEidtShape == nullptr) {
		AfxMessageBox("ERROR:当前界面没有编辑框，请先画出选择的区域");
		return;
	}
	m_bIsEdit = FALSE;  //关闭编辑状态
	m_bIsChange = TRUE; //开启变化状态
	m_et = ET_MOVE; //当前移动状态
}



//右键-修改编辑状态
void CPaintView::OnRBInedit()
{
	CCADDoc* cDoc = (CCADDoc*)GetDocument();
	if (cDoc->m_lstShapes.IsEmpty()) {
		AfxMessageBox("ERROR：当前页面没有图形，不允许进入编辑状态");
		return;
	}
	m_bIsEdit = TRUE;
	m_bIsChange = FALSE;
	AfxMessageBox("TIP：进入编辑选项后，可以在界面中画出选择的矩形框，之后选择移动等可以对矩形内的图形进行操作");
}
//右键---移动
void CPaintView::OnRBMove()
{
	if (m_pCurEidtShape == nullptr) {
		AfxMessageBox("ERROR:当前界面没有编辑框，请先画出选择的区域");
		return;
	}
	m_bIsEdit = FALSE;  //关闭编辑状态
	m_bIsChange = TRUE; //开启变化状态
	m_et = ET_MOVE; //当前移动状态
}
//右键------放缩
void CPaintView::OnRBEnlarge()
{
	if (m_pCurEidtShape == nullptr) {
		AfxMessageBox("ERROR:当前界面没有编辑框，请先画出选择的区域");
		return;
	}
	m_bIsEdit = FALSE;  //关闭编辑状态
	m_bIsChange = TRUE; //开启变化状态
	m_et = ET_ENLARGE; //当前移动状态
	nLastEnLarge = 0; //放缩改为0
}


//前进后退
void CPaintView::OnAdvance()
{
	// TODO: 在此添加命令处理程序代码
	if (m_stkToUndo.empty())
	{
		return;
	}
	//撤销， 从撤销栈取出栈顶动作，执行撤销，存入重做栈
	auto ptrAction = m_stkToUndo.top();
	m_stkToUndo.pop();

	ptrAction->Undo();

	m_stkToRedo.push(ptrAction);
	m_pCurShape = nullptr;
	InvalidateRect(NULL, FALSE);

	//如果在其他状态的话需要退出
	if (m_bIsEdit == TRUE) {
		AfxMessageBox("tip:退出编辑状态");
		m_bIsEdit = FALSE;
		m_bIsChange = FALSE;
		return;
	}
	if (m_bIsChange == TRUE) {
		AfxMessageBox("tip:退出操作状态");
		m_bIsEdit = FALSE;
		m_bIsChange = FALSE;
		return;
	}
}
void CPaintView::OnRetreat()
{
	// TODO: 在此添加命令处理程序代码
	if (m_stkToRedo.empty())
	{
		return;
	}
	//重做 从重做栈取出栈顶动作，执行重做，存入撤销栈
	auto ptrAction = m_stkToRedo.top();
	m_stkToRedo.pop();
	ptrAction->Redo();
	m_stkToUndo.push(ptrAction);
	InvalidateRect(NULL, FALSE);

	//如果在其他状态的话需要退出
	if (m_bIsEdit == TRUE) {
		AfxMessageBox("tip:退出编辑状态");
		m_bIsEdit = FALSE;
		m_bIsChange = FALSE;
		return;
	}
	if (m_bIsChange == TRUE) {
		AfxMessageBox("tip:退出操作状态");
		m_bIsEdit = FALSE;
		m_bIsChange = FALSE;
		return;
	}
}



//画笔画刷
void CPaintView::OnPaint()
{
	CPaintDlg dlg;
	dlg.m_nPenStyle = m_nPenStyle;//dlg.m_cmbStyle.GetCurSel();  获取风格
	dlg.m_nWidth = m_nPenWidth;   //获取宽度
	dlg.m_clrPen = m_clrPen;      //获取颜色
	if (dlg.DoModal() == IDOK)
	{
		//使用
		m_nPenStyle = dlg.m_nPenStyle;//dlg.m_cmbStyle.GetCurSel();----DoModal后窗口已经关了，因此没有了窗口句柄，使用会报错
		m_nPenWidth = dlg.m_nWidth;
		m_clrPen = dlg.m_clrPen;
	}
}
void CPaintView::OnBrush()
{
	CBrushDlg dlg;
	dlg.m_nPenFigure = m_nPenFigure;
	dlg.m_clrBrush = m_clrBrush;
	if (dlg.DoModal() == IDOK) {
		m_nPenFigure = dlg.m_nPenFigure;
		m_clrBrush = dlg.m_clrBrush;
	}
}



//更新
void CPaintView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	CCADDoc* cDoc = (CCADDoc*)GetDocument();

}


void CPaintView::OnDraw(CDC* pDC)
{
	CCADDoc* pDoc = (CCADDoc*)GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CRect rcClient;
	GetClientRect(&rcClient);
	//1) 创建内存DC
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	//2）创建内存位图
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(pDC, rcClient.Width(), rcClient.Height());
	//3）位图选入内存DC
	CBitmap* pOldBmp = dcMem.SelectObject(&bmpMem);
	//4）绘制
	dcMem.FillSolidRect(&rcClient, RGB(255, 255, 255));
	////遍历链表，将保存得所有直线绘制到界面
	auto pos = pDoc->m_lstShapes.GetHeadPosition();
	while (pos)
	{
		//获取直线
		auto& pShape = pDoc->m_lstShapes.GetNext(pos);
		//绘制
		pShape->DrawShape(&dcMem);
	}
	if (m_bIsEdit == FALSE && m_pCurShape) {
		m_pCurShape->DrawShape(&dcMem);
	}
	//编辑框
	if ((m_bIsEdit || m_bIsChange)&& m_pCurEidtShape) {
		//CPen pen;
		//pen.CreatePen(2, 7, RGB(142,53,74));
		//CPen* pOldPen = dcMem.SelectObject(&pen);
		m_pCurEidtShape->DrawShape(&dcMem);
		//dcMem.SelectObject(pOldBmp);
	}
	//4）从内存DC拷贝到客户区
	  ////拷贝到客户区
	pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(),//拷贝到客户区
		&dcMem, 0, 0, //从屏幕左上角拷贝
		SRCCOPY); //颜色不做任何修改
	dcMem.SelectObject(pOldBmp);

	//通知所有视图，数据被修改，更新界面
	pDoc->UpdateAllViews(this);
}
