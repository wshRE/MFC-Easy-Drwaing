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


// CPaintView 窗体视图

class CPaintView : public CFormView
{
	DECLARE_DYNCREATE(CPaintView)

public:
	//编辑
	BOOL m_bIsEdit = FALSE;   //是否开启编辑
	IFactory* pEditFactory = new CRectFac(4);  //矩形选择框
	std::shared_ptr<CShapeBase> m_pCurEidtShape = nullptr; //编辑矩阵框
//变化
	//参数
	enum EditType {
		ET_WHIRL, //旋转
		ET_MOVE, //移动
		ET_ENLARGE  //变大缩小
	};
	EditType m_et = ET_WHIRL; //当前旋转状态
	BOOL m_bIsChange = FALSE; //是否在变化状态
	CPoint m_cStart;  //记录变化之前的坐标
	CPoint m_cEnd;    //变化之后的坐标
	int nLastEnLarge = 0;
	int m_xzds = 0;  //当前旋转角度
	std::shared_ptr<CShapeBase> m_pCurChooseShape = nullptr; //当前选择的图形


//绘图模块
	enum ShapeType {
		ST_LINE, //直线
		ST_RECT, //矩形
		ST_ELLP  //椭圆
	};
	ShapeType m_st = ST_LINE; //图形的种类
	std::shared_ptr<CShapeBase> m_pCurShape = nullptr; //当前正在创建的图形
	//CList<std::shared_ptr<CShapeBase>> m_lstShapes; //保存各种图形的链表
	IFactory* pFactory = new CLineFac;



	//画笔
	int m_nPenStyle = PS_SOLID;
	int m_nPenWidth = 1;
	COLORREF m_clrPen = RGB(0, 0, 0);

	//画刷
	int m_nPenFigure = HS_API_MAX;  //空白不填充
	COLORREF m_clrBrush = RGB(0, 0, 0);


	//撤销重做
	std::stack<shared_ptr<CBackTrack>> m_stkToUndo; //撤销栈
	std::stack<shared_ptr<CBackTrack>> m_stkToRedo; //重做栈
	//旧状态
	//图形参数
	CPoint m_cOldStart;//起点
	CPoint m_cOldEnd;  //终点
	//画笔参数
	int m_nOldPenStyle;
	int m_nOldPenWidth;
	COLORREF m_clrOldPen;
	//画刷配置
	int m_nOldBrushFrigue; //填充花纹
	COLORREF m_clrOldBrush;//花纹颜色

	void RememberOld(std::shared_ptr<CShapeBase> pCurShape);
	BOOL iSIn(std::shared_ptr<CShapeBase> m_pCurShape);

protected:
	CPaintView();           // 动态创建所使用的受保护的构造函数
	virtual ~CPaintView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = DLG_PAINT_VIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnShapeLine();
	afx_msg void OnShapeRect();
	afx_msg void OnShapeElli();
	afx_msg void OnInedit();
	afx_msg void OnWhril();
	afx_msg void OnEnlarge();
	afx_msg void OnMove();
	afx_msg void OnRBInedit();
	afx_msg void OnRBMove();
	afx_msg void OnRBEnlarge();
	afx_msg void OnAdvance();
	afx_msg void OnRetreat();
	afx_msg void OnPaint();
	afx_msg void OnBrush();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	virtual void OnDraw(CDC* /*pDC*/);
};


