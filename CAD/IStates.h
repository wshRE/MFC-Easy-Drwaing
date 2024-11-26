#pragma once
#include "CShapeBase.h"
#include <memory>
using namespace std;
class IStates
{
    //1.���
    void CAdd(CList<shared_ptr<CShapeBase>>* plstShapes, shared_ptr<CShapeBase> ptrAddShape)
    {
        nFlag = 1;
        m_plstShapes = plstShapes;
        m_ptrMoveShape = ptrAddShape;
    }
    
    //2.�ƶ�/����
    void CMove(shared_ptr<CShapeBase> ptrMoveShape,
        CPoint ptOldBegin,
        CPoint ptOldEnd,
        CPoint ptNewBegin,
        CPoint ptNewEnd)
    {
        nFlag = 2;
        m_ptrMoveShape = ptrMoveShape;
        m_ptOldBegin = ptOldBegin;
        m_ptOldEnd = ptOldEnd;
        m_ptNewBegin = ptNewBegin;
        m_ptNewEnd = ptNewEnd;
    }



    void Undo()
    {
        if (nFlag == 2) {
            //��ԭΪ�ƶ�ǰ������
            m_ptrMoveShape->SetStart(m_ptOldBegin);
            m_ptrMoveShape->SetEnd(m_ptOldEnd);
        }
        else if (nFlag == 1) {
            //������ɾ��
            m_plstShapes->RemoveAt(m_plstShapes->Find(m_ptrMoveShape));
        }

    }

    void Redo()
    {
        if (nFlag == 2) {
                    //����Ϊ�ƶ��������
            m_ptrMoveShape->SetStart(m_ptNewBegin);
            m_ptrMoveShape->SetEnd(m_ptNewEnd);
        }
        else if (nFlag == 1) {
            //��ӵ�����
            m_plstShapes->AddTail(m_ptrMoveShape);
        }
    }
private:
    /*
    1.����
    2.�ƶ�/����
    */
    size_t nFlag; //������־
    shared_ptr<CShapeBase> m_ptrMoveShape; //����


//1.����
    CList<std::shared_ptr<CShapeBase>>* m_plstShapes;  //��ǰ��ͼ������ָ��
//2.�ƶ�
    //�ɵ�����
    CPoint m_ptOldBegin;
    CPoint m_ptOldEnd;

    //�ƶ��������
    CPoint m_ptNewBegin;
    CPoint m_ptNewEnd;
};

