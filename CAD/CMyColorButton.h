#pragma once
#include <afxcolorbutton.h>
class CMyColorButton :
    public CMFCColorButton
{
public:
    virtual void OnShowColorPopup();
};

