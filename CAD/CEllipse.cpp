#include "pch.h"
#include "CEllipse.h"
IMPLEMENT_SERIAL(CEllipse, CShapeBase, 1)
void CEllipse::DrawShape(CDC* pDC)
{
    CPen pen;
    pen.CreatePen(m_nPenStyle, m_nPenWidth, m_clrPen);
    CPen* pOldPen = pDC->SelectObject(&pen);

    //»­Ë¢
    CBrush brush;
    if (m_nBrushFrigue == 6 || m_nBrushFrigue == 12) {
        brush.CreateHatchBrush(12, RGB(0, 0, 0));
    }
    else {
        brush.CreateHatchBrush(m_nBrushFrigue, m_clrBrush);
    }
    CBrush* pOrigBrush = (CBrush*)pDC->SelectObject(&brush);

    pDC->Ellipse(m_cStart.x, m_cStart.y, m_cEnd.x, m_cEnd.y);
    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOrigBrush);
}

int CEllipse::GetType()
{
    return 2;
}

void CEllipse::Serialize(CArchive& archive)
{
    CShapeBase::Serialize(archive);
}

