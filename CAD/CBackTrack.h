#pragma once
#include <memory>
#include "CShapeBase.h"
using namespace std;
//������
class CBackTrack
{
public:
    //ȫ¼��
    CBackTrack(shared_ptr<CShapeBase> ptrShapeRecord, 
        CPoint cNowStart,CPoint cNowEnd, CPoint cOldStart, CPoint cOldEnd,
        int nNewPenStyle, int nNewPenWidth, COLORREF clrNewPen, int nOldPenStyle, int nOldPenWidth, COLORREF clrOldPen,
        int nNewBrushFriguem, COLORREF clrNewBrush, int nOldBrushFriguem, COLORREF clrOldBrush) {
        m_ptrShapeRecord = ptrShapeRecord;
        m_cNowStart = cNowStart;
        m_cNowEnd = cNowEnd;
        m_cOldStart = cOldStart;
        m_cOldEnd = cOldEnd;

        m_nNowPenStyle = nNewPenStyle;
        m_nNowPenWidth = nNewPenWidth;
        m_clrNowPen = clrNewPen;

        m_nOldPenStyle = nOldPenStyle;
        m_nOldPenWidth = nOldPenWidth;
        m_clrOldPen = clrOldPen;

        m_nNowBrushFrigue = nNewBrushFriguem;
        m_clrNowBrush = clrNewBrush;

        m_nOldBrushFrigue = nOldBrushFriguem;
        m_clrOldBrush = clrOldBrush;
    }
    //�µ�
    CBackTrack( CList<std::shared_ptr<CShapeBase>>* plstShapes,shared_ptr<CShapeBase> ptrShapeRecord) {
        m_ptrShapeRecord = ptrShapeRecord;
        m_plstShapes = plstShapes;
        m_bIsFirst = TRUE;
    }
    
    
    //��ԭ
    void Undo() {
        if (m_bIsFirst == TRUE) {
            //��������ɾ�����ڵ�
            m_plstShapes->RemoveAt(m_plstShapes->Find(m_ptrShapeRecord));
            return;
        }
        m_ptrShapeRecord->SetStart(m_cOldStart);
        m_ptrShapeRecord->SetEnd(m_cOldEnd);

        m_ptrShapeRecord->SetPen(m_nOldPenStyle, m_nOldPenWidth, m_clrOldPen);
        m_ptrShapeRecord->SetBrush(m_nOldBrushFrigue, m_clrOldBrush);
    }
    //����
    void Redo() {
        if (m_bIsFirst == TRUE) {
            //����������ӱ��ڵ�
            m_plstShapes->AddTail(m_ptrShapeRecord);
            return;
        }
        m_ptrShapeRecord->SetStart(m_cNowStart);
        m_ptrShapeRecord->SetEnd(m_cNowEnd);
        m_ptrShapeRecord->SetPen(m_nNowPenStyle, m_nNowPenWidth, m_clrNowPen);
        m_ptrShapeRecord->SetBrush(m_nNowBrushFrigue, m_clrNowBrush);
    }


    void SetNowPoint(CPoint cNowStart,CPoint cNowEnd) {
        m_cNowStart = cNowStart;
        m_cNowEnd = cNowEnd;
    }
    void SetOldPoint(CPoint cOldStart, CPoint cOldEnd) {
        m_cOldStart = cOldStart;
        m_cOldEnd = cOldEnd;
    }
    void SetNewPen(int nNewPenStyle, int nNewPenWidth, COLORREF clrNewPen) {
        m_nNowPenStyle = nNewPenStyle;
        m_nNowPenWidth = nNewPenWidth;
        m_clrNowPen = clrNewPen;
    }
    void SetOldPen(int nOldPenStyle, int nOldPenWidth, COLORREF clrOldPen) {
        m_nOldPenStyle = nOldPenStyle;
        m_nOldPenWidth = nOldPenWidth;
        m_clrOldPen    = clrOldPen;
    }

    void SetNewBrush(int nNewBrushFriguem,COLORREF clrNewBrush) {
        m_nNowBrushFrigue = nNewBrushFriguem;
        m_clrNowBrush = clrNewBrush;
    }
    void SetOldBrush(int nOldBrushFriguem, COLORREF clrOldBrush) {
        m_nOldBrushFrigue = nOldBrushFriguem;
        m_clrOldBrush     = clrOldBrush;
    }
    void SetShape(shared_ptr<CShapeBase> ptrShapeRecord) {
        m_ptrShapeRecord = ptrShapeRecord;
    }
    void SetFirst() {
        m_bIsFirst = TRUE;
    }
public:
//�½�
    BOOL m_bIsFirst = FALSE;
    CList<std::shared_ptr<CShapeBase>>* m_plstShapes;

    shared_ptr<CShapeBase> m_ptrShapeRecord;
    //��״̬
//ͼ�β���
    CPoint m_cNowStart;//���
    CPoint m_cNowEnd;  //�յ�
//���ʲ���
    int m_nNowPenStyle;
    int m_nNowPenWidth;
    COLORREF m_clrNowPen;
//��ˢ����
    int m_nNowBrushFrigue; //��仨��
    COLORREF m_clrNowBrush;//������ɫ

    //��״̬
//ͼ�β���
    CPoint m_cOldStart;//���
    CPoint m_cOldEnd;  //�յ�
//���ʲ���
    int m_nOldPenStyle;
    int m_nOldPenWidth;
    COLORREF m_clrOldPen;
    //��ˢ����
    int m_nOldBrushFrigue; //��仨��
    COLORREF m_clrOldBrush;//������ɫ

};

