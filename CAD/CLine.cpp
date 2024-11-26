#include "pch.h"
#include "CLine.h"
IMPLEMENT_SERIAL(CLine, CShapeBase, 1)
void CLine::DrawShape(CDC* pDC)
{
    //»­±Ê
    CPen pen;
    pen.CreatePen(m_nPenStyle, m_nPenWidth, m_clrPen);
    CPen* pOldPen = pDC->SelectObject(&pen);

    //»­Ë¢
    CBrush brush;
    if (m_nBrushFrigue == 6) {
        brush.CreateHatchBrush(12, m_clrBrush);
    }
    else {
        brush.CreateHatchBrush(m_nBrushFrigue, m_clrBrush);
    }
    pDC->SelectObject(&brush);

    pDC->MoveTo(m_cStart);
    pDC->LineTo(m_cEnd);
    pDC->SelectObject(pOldPen);
}

int CLine::GetType()
{
    return 0;
}

void CLine::Serialize(CArchive& archive)
{
    CShapeBase::Serialize(archive);
}
