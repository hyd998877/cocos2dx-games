//
//  LinkLogic.cpp
//  MyLinker
//
//  Created by zhouf369 on 14-8-18.
//
//

#include "LinkLogic.h"
#include "Icon.h"
#include "GameMapLayer.h"

bool LinkLogic::canFadeAway(Icon *first, Icon *second)
{
    if (checkLine(first, second)
        || checkOneCorner(first, second)
        || checkTwoCorner(first, second))
    {
        return true;
    }
    
    return false;
}

bool LinkLogic::checkLine(Icon *first, Icon *second)
{
    int dy = first->getRow() - second->getRow();
    int dx = first->getCol() - second->getCol();
    int next = 0;
    Icon *pNextIcon = NULL;
    if (dx == 0)
    {
        for (int i = 0; i < abs(dy); i++)
        {
            if (dy < 0)
            {
                next++;
            }
            else
            {
                next--;
            }
            
            pNextIcon = GameMapLayer::getIconAtRowAndCol(first->getRow()+next, first->getCol());
            
            if (pNextIcon == second)
            {
                return true;
            }
            else if (!pNextIcon->getDestroyed())
            {
                return false;
            }
        }
    }
    else if (dy == 0)
    {
        for (int i = 0; i < abs(dx); i++)
        {
            if (dx < 0)
            {
                next++;
            }
            else
            {
                next--;
            }
            
            pNextIcon = GameMapLayer::getIconAtRowAndCol(first->getRow(), first->getCol()+next);
            
            if (pNextIcon == second)
            {
                return true;
            }
            else if (!pNextIcon->getDestroyed())
            {
                return false;
            }
        }
    }
    
    return false;
}

bool LinkLogic::checkOneCorner(Icon *first, Icon *second)
{
    int iCornerRow1 = first->getRow();
    int iCornerCol1 = second->getCol();
    Icon *pCornerIcon1 = GameMapLayer::getIconAtRowAndCol(iCornerRow1, iCornerCol1);
    if (pCornerIcon1->getDestroyed() && checkLine(first, pCornerIcon1) && checkLine(pCornerIcon1, second))
    {
        return true;
    }
    
    int iCornerRow2 = second->getRow();
    int iCornerCol2 = first->getCol();
    Icon *pCornerIcon2 = GameMapLayer::getIconAtRowAndCol(iCornerRow2, iCornerCol2);
    if (pCornerIcon2->getDestroyed() && checkLine(first, pCornerIcon2) && checkLine(pCornerIcon2, second))
    {
        return true;
    }
    
    return false;
}

bool LinkLogic::checkTwoCorner(Icon *first, Icon *second)
{
    for (int i = first->getRow()+1; i < GameMapLayer::m_iMapRow; i++)
    {
        Icon *pIcon  = GameMapLayer::getIconAtRowAndCol(i, first->getCol());
        if (!pIcon->getDestroyed())
        {
            break;
        }
        else if (checkOneCorner(pIcon, second))
        {
            return true;
        }
    }
    for (int i = first->getRow()-1; i >= 0; i--)
    {
        Icon *pIcon = GameMapLayer::getIconAtRowAndCol(i, first->getCol());
        if (!pIcon->getDestroyed())
        {
            break;
        }
        else if (checkOneCorner(pIcon, second))
        {
            return true;
        }
    }
    
    for (int i = first->getCol()+1; i < GameMapLayer::m_iMapCol; i++)
    {
        Icon *pIcon = GameMapLayer::getIconAtRowAndCol(first->getRow(), i);
        if (!pIcon->getDestroyed())
        {
            break;
        }
        else if (checkOneCorner(pIcon, second))
        {
            return true;
        }
    }
    for (int i = first->getCol()-1; i >= 0; i++)
    {
        Icon *pIcon = GameMapLayer::getIconAtRowAndCol(first->getRow(), i);
        if (!pIcon->getDestroyed())
        {
            break;
        }
        else if (checkOneCorner(pIcon, second))
        {
            return true;
        }
    }
    
    return false;
}