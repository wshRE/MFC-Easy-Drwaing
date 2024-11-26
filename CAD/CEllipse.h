#pragma once
#include"CShapeBase.h"
class CEllipse :
    public CShapeBase
{
    DECLARE_SERIAL(CEllipse)
public:

    // ͨ�� IShape �̳�
    void DrawShape(CDC* pDC);
    virtual int GetType();
    //2.��д�麯�� 
    virtual void Serialize(CArchive& archive);
};


class CElliFac :public IFactory
{
public:
    CShapeBase* CreateShape() { return new CEllipse; }
};