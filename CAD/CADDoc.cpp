
// CADDoc.cpp: CCADDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "CAD.h"
#endif

#include "CADDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CADView.h"

// CCADDoc

IMPLEMENT_DYNCREATE(CCADDoc, CDocument)

BEGIN_MESSAGE_MAP(CCADDoc, CDocument)
END_MESSAGE_MAP()


// CCADDoc 构造/析构

CCADDoc::CCADDoc() noexcept
{
	// TODO: 在此添加一次性构造代码

}

//CList<std::shared_ptr<CShapeBase>>& CCADDoc::GetShapeList()
//{
//	// TODO: 在此处插入 return 语句
//}

CCADDoc::~CCADDoc()
{
}

BOOL CCADDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CCADDoc 序列化

void CCADDoc::Serialize(CArchive& ar)
{
	//CObject::Serialize(ar);
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
		//写入个数
		ar << (int)(m_lstShapes.GetCount());
		auto posS = m_lstShapes.GetTailPosition();
		while (posS)
		{
			CShapeBase* pShape = m_lstShapes.GetPrev(posS).get();
			ar << pShape; //写入
		}
	}
	else
	{
		// TODO: 在此添加加载代码
		int nCount;
		ar >> nCount;
		for (int i = 0; i < nCount;i++) {
			CShapeBase* m_pCurShape = nullptr;
			ar >> m_pCurShape;
			m_lstShapes.AddTail(shared_ptr<CShapeBase>(m_pCurShape));
		}
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CCADDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CCADDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CCADDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCADDoc 诊断

#ifdef _DEBUG
void CCADDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCADDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCADDoc 命令
