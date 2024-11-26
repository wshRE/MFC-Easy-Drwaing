#include "pch.h"
#include "CRectangle.h"

IMPLEMENT_SERIAL(CRectangle, CShapeBase, 1)
void CRectangle::DrawShape(CDC* pDC)
{
    CPen pen;
    pen.CreatePen(m_nPenStyle, m_nPenWidth, m_clrPen);
    CPen* pOldPen = pDC->SelectObject(&pen);

    //»­Ë¢
    CBrush brush;
    if (m_nBrushFrigue == 6  || m_nBrushFrigue == 12) {
        brush.CreateHatchBrush(12, RGB(0,0,0));
    }
    else {
        brush.CreateHatchBrush(m_nBrushFrigue, m_clrBrush);
    }

    CBrush* pOrigBrush = (CBrush*)pDC->SelectObject(&brush);
    
    if (m_bTransparent == TRUE) { //Í¸Ã÷
        pDC->SelectObject(GetStockObject(NULL_BRUSH));
    }
    //else {
    //    pDC->SelectObject(&brush);
    //}
    
    pDC->Rectangle(m_cStart.x, m_cStart.y, m_cEnd.x, m_cEnd.y); //´´½¨¾ØÕó

    pDC->SelectObject(pOldPen);
    pDC->SelectObject(pOrigBrush);
}

int CRectangle::GetType()
{
    return 1;
}

void CRectangle::Serialize(CArchive& archive)
{
    CShapeBase::Serialize(archive);
}

