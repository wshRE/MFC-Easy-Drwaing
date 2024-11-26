#pragma once
#include"CShapeBase.h"
#include <afx.h>
class CLine :
    public CShapeBase
{
    DECLARE_SERIAL(CLine)
public:
    // ͨ�� IShape �̳�
     void DrawShape(CDC* pDC);
     int GetType();
     virtual void Serialize(CArchive& archive);
};




class CLineFac :public IFactory
{
public:
    CShapeBase* CreateShape() { return new CLine; }
};
