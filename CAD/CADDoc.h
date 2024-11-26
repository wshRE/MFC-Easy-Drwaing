
// CADDoc.h: CCADDoc 类的接口
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

using namespace std;
class CCADDoc : public CDocument
{
protected: // 仅从序列化创建
	CCADDoc() noexcept;
	DECLARE_DYNCREATE(CCADDoc)

public:
	CList<std::shared_ptr<CShapeBase>> m_lstShapes; //保存各种图形的链表
// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);  //序列化与反序列化
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CCADDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS



};
