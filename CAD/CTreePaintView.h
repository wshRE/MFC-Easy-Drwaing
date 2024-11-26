#pragma once

#include <afxcview.h>
// CTreePaintView 视图

class CTreePaintView : public CTreeView
{
	DECLARE_DYNCREATE(CTreePaintView)

protected:
	CTreePaintView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTreePaintView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
//数据
public:
	HTREEITEM hItemLine;
	HTREEITEM hItemRect;
	HTREEITEM hItemElii;

public:
	void DelChild(HTREEITEM hmyItem);               //清空子节点
	afx_msg void OnTvnItemexpanding(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
};


