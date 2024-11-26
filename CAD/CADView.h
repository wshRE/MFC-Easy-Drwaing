// CADView.h: CCADView 类的接口
//

#pragma once
#include <utility>
#include <memory>
#include <cmath>
#include "CShapeBase.h"
#include"CEllipse.h"
#include"CLine.h"
#include"CRectangle.h"
#include <stack>
#include "CBackTrack.h"
#include "CBackTrack.h"
class CCADView : public CView
{
protected: // 仅从序列化创建
	CCADView() noexcept;
	DECLARE_DYNCREATE(CCADView)








// 特性
public:
	CCADDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CCADView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	//void RememberOld(std::shared_ptr<CShapeBase> pCurShape);
	////3为中心点
	//double CCADView::get_angle(CPoint cStart, CPoint cEnd, CPoint cCenter); //求夹角
	//BOOL iSIn(std::shared_ptr<CShapeBase> m_pCurShape);
	//afx_msg void OnInedit();
	//afx_msg void OnShapeLine();
	//afx_msg void OnShapeRect();
	//afx_msg void OnShapeElli();
	//afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//afx_msg void OnWhril();
	//afx_msg void OnEnlarge();
	//afx_msg void OnMove();
	//afx_msg void OnRBInedit();
	//afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	//afx_msg void OnRBMove();
	//afx_msg void OnRBEnlarge();
	//afx_msg void OnPaint();
	//afx_msg void OnBrush();
	//afx_msg void OnAdvance();
	//afx_msg void OnRetreat();
};

#ifndef _DEBUG  // CADView.cpp 中的调试版本
inline CCADDoc* CCADView::GetDocument() const
   { return reinterpret_cast<CCADDoc*>(m_pDocument); }
#endif

