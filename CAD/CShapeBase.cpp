#include "pch.h"
#include "CShapeBase.h"

IMPLEMENT_SERIAL(CShapeBase, CObject, 1)
void CShapeBase::DrawShape(CDC* pDC)
{
}

int CShapeBase::GetType()
{
    return -1;
}


//重写虚函数
void CShapeBase::Serialize(CArchive& archive)
{
    if (archive.IsStoring())
    {
        archive << m_cStart << m_cEnd << m_nPenStyle << m_nPenWidth << m_clrPen << m_nBrushFrigue << m_clrBrush;  //读取
    }
    else
    {
        archive >> m_cStart >> m_cEnd >> m_nPenStyle >> m_nPenWidth >> m_clrPen >> m_nBrushFrigue >> m_clrBrush; //写入
    }
}
