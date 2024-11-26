#pragma once
class CShapeBase:public CObject
{
    DECLARE_SERIAL(CShapeBase)
    //图形接口
public:
    //图形绘制
    virtual void DrawShape(CDC* pDC);
    virtual int GetType();
    //2.重写虚函数 
    virtual void Serialize(CArchive& archive);
    void SetStart(CPoint m_cStart) {
        this->m_cStart = m_cStart;
    }
    void SetEnd(CPoint m_cEnd) {
        this->m_cEnd = m_cEnd;
    }
    CPoint GetStart() {
        return m_cStart;
    }
    CPoint GetEnd() {
        return m_cEnd;
    }
    void SetPen(int nPenStyle, int nPenWidth, COLORREF clrPen)
    {
        m_nPenStyle = nPenStyle;
        m_nPenWidth = nPenWidth;
        m_clrPen = clrPen;
    }
    void SetBrush(int nBrushFrigue,COLORREF clrBrush) {
        m_nBrushFrigue = nBrushFrigue;
        m_clrBrush = clrBrush;
    }
    void SetTp() {
        m_bTransparent = TRUE;
    }
//protected:
public:
//图形参数
    CPoint m_cStart;//起点
    CPoint m_cEnd;  //终点
//画笔参数
    int m_nPenStyle;
    int m_nPenWidth;
    COLORREF m_clrPen;
//画刷配置
    int m_nBrushFrigue; //填充花纹
    COLORREF m_clrBrush;//花纹颜色
    //特殊类画刷--透明
    BOOL m_bTransparent = FALSE;
};

//工厂类
class IFactory
{
public:
    //创建图形
    virtual CShapeBase* CreateShape() = 0;
};


