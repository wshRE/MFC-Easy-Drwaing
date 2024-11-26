#pragma once
#include"CShapeBase.h"
class CEllipse :
    public CShapeBase
{
    DECLARE_SERIAL(CEllipse)
public:

    // 通过 IShape 继承
    void DrawShape(CDC* pDC);
    virtual int GetType();
    //2.重写虚函数 
    virtual void Serialize(CArchive& archive);
};


class CElliFac :public IFactory
{
public:
    CShapeBase* CreateShape() { return new CEllipse; }
};