#include "pch.h"
#include "CMyColorButton.h"

void CMyColorButton::OnShowColorPopup()
{
    CColorDialog dlgColor;
    if (dlgColor.DoModal() == IDOK)
    {
        SetColor(dlgColor.GetColor());  //������ɫ��ť����ɫ
    }
}
