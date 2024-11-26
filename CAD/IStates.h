#pragma once
#include "CShapeBase.h"
#include <memory>
using namespace std;
class IStates
{
    //1.添加
    void CAdd(CList<shared_ptr<CShapeBase>>* plstShapes, shared_ptr<CShapeBase> ptrAddShape)
    {
        nFlag = 1;
        m_plstShapes = plstShapes;
        m_ptrMoveShape = ptrAddShape;
    }
    
    //2.移动/放缩
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
            //还原为移动前的坐标
            m_ptrMoveShape->SetStart(m_ptOldBegin);
            m_ptrMoveShape->SetEnd(m_ptOldEnd);
        }
        else if (nFlag == 1) {
            //从链表删除
            m_plstShapes->RemoveAt(m_plstShapes->Find(m_ptrMoveShape));
        }

    }

    void Redo()
    {
        if (nFlag == 2) {
                    //设置为移动后的坐标
            m_ptrMoveShape->SetStart(m_ptNewBegin);
            m_ptrMoveShape->SetEnd(m_ptNewEnd);
        }
        else if (nFlag == 1) {
            //添加到链表
            m_plstShapes->AddTail(m_ptrMoveShape);
        }
    }
private:
    /*
    1.新增
    2.移动/放缩
    */
    size_t nFlag; //操作标志
    shared_ptr<CShapeBase> m_ptrMoveShape; //对象


//1.新增
    CList<std::shared_ptr<CShapeBase>>* m_plstShapes;  //当前的图形链表指针
//2.移动
    //旧的坐标
    CPoint m_ptOldBegin;
    CPoint m_ptOldEnd;

    //移动后的坐标
    CPoint m_ptNewBegin;
    CPoint m_ptNewEnd;
};

