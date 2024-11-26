#pragma once
class CShapeBase:public CObject
{
    DECLARE_SERIAL(CShapeBase)
    //ͼ�νӿ�
public:
    //ͼ�λ���
    virtual void DrawShape(CDC* pDC);
    virtual int GetType();
    //2.��д�麯�� 
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
//ͼ�β���
    CPoint m_cStart;//���
    CPoint m_cEnd;  //�յ�
//���ʲ���
    int m_nPenStyle;
    int m_nPenWidth;
    COLORREF m_clrPen;
//��ˢ����
    int m_nBrushFrigue; //��仨��
    COLORREF m_clrBrush;//������ɫ
    //�����໭ˢ--͸��
    BOOL m_bTransparent = FALSE;
};

//������
class IFactory
{
public:
    //����ͼ��
    virtual CShapeBase* CreateShape() = 0;
};


