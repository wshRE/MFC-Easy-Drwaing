// CTreePaintView.cpp: 实现文件
//

#include "pch.h"
#include "CAD.h"
#include "CTreePaintView.h"
#include "CADDoc.h"


// CTreePaintView

IMPLEMENT_DYNCREATE(CTreePaintView, CTreeView)

CTreePaintView::CTreePaintView()
{

}

CTreePaintView::~CTreePaintView()
{
}

BEGIN_MESSAGE_MAP(CTreePaintView, CTreeView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDING, &CTreePaintView::OnTvnItemexpanding)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CTreePaintView::OnNMDblclk)
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CTreePaintView 诊断

#ifdef _DEBUG
void CTreePaintView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void CTreePaintView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTreePaintView 消息处理程序

void CTreePaintView::DelChild(HTREEITEM hmyItem)
{
	if (GetTreeCtrl().ItemHasChildren(hmyItem))
	{
		CTreeCtrl& treeTest = GetTreeCtrl();
		HTREEITEM hNextItem;
		HTREEITEM hChildItem = treeTest.GetChildItem(hmyItem);

		while (hChildItem != NULL)
		{
			hNextItem = treeTest.GetNextItem(hChildItem, TVGN_NEXT);
			treeTest.DeleteItem(hChildItem);
			hChildItem = hNextItem;
		}
	}
}

//展开
void CTreePaintView::OnTvnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

}


void CTreePaintView::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
}


int CTreePaintView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;
	CTreeCtrl& treeTest = GetTreeCtrl();
	hItemLine = treeTest.InsertItem("直线");
	hItemRect = treeTest.InsertItem("矩形");
	hItemElii = treeTest.InsertItem("椭圆");
	//设置风格，树带线
	treeTest.ModifyStyle(0,
		TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS);
	return 0;
}




void CTreePaintView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
	CCADDoc* pDoc = (CCADDoc*)GetDocument();

	auto pos = pDoc->m_lstShapes.GetHeadPosition();
	DelChild(hItemLine);
	DelChild(hItemRect);
	DelChild(hItemElii);

	while (pos)
	{
		//获取直线
		auto& pShape = pDoc->m_lstShapes.GetNext(pos);
		//判断类型
		char sz[MAXBYTE]{};
		ZeroMemory(sz, 0);
		sprintf_s(sz, "(%d,%d)-(%d,%d)", pShape->GetStart().x, pShape->GetStart().y, pShape->GetEnd().x, pShape->GetEnd().y);
		if (pShape->GetType() == 0) {
			//加入
			GetTreeCtrl().InsertItem(sz, hItemLine);
		}
		else if (pShape->GetType() ==  1) {
			GetTreeCtrl().InsertItem(sz, hItemRect);
		}
		else if (pShape->GetType() == 2) {
			GetTreeCtrl().InsertItem(sz, hItemElii);
		}
	}
}
