#pragma once
#include"CShapeBase.h"
class CRectangle : public CShapeBase
{
    DECLARE_SERIAL(CRectangle)
public:
    void DrawShape(CDC* pDC);
    int GetType();
    //2.��д�麯�� 
    virtual void Serialize(CArchive& archive);
};


class CRectFac :public IFactory
{
public:
    CRectFac(int n) { m_nRadix = n; }
    CShapeBase* CreateShape()  //����ʵ��
    {
        //m_nRadix
        return new CRectangle;
    }

private:
    int m_nRadix = 0;
};

