//
//  GameMapLayer.cpp
//  MyLinker
//
//  Created by zhouf369 on 14-8-15.
//
//

#include "GameMapLayer.h"
#include "Icon.h"

using namespace cocos2d;

const int GameMapLayer::m_iIconWidth = 45;
const int GameMapLayer::m_iIconHeight = 51;
int GameMapLayer::m_iMapRow = 0;
int GameMapLayer::m_iMapCol = 0;

CCArray* GameMapLayer::m_pMapsArray = CCArray::create();

GameMapLayer::GameMapLayer()
{
    
}

GameMapLayer::~GameMapLayer()
{
    dispose();
}

bool GameMapLayer::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    m_pMapsArray->retain();
    
    return true;
}

void GameMapLayer::initMapWithRowAndCol(const int &row, const int &col)
{
    m_iMapRow = row;
    m_iMapCol = col;
    
    m_iMapWidth = m_iMapCol * m_iIconWidth;
    m_iMapHeight = m_iMapRow * m_iIconHeight;
    
    srand(time(NULL));
    
    for (int i = 0; i < m_iMapRow; i++)
    {
        CCArray *pTempArray = CCArray::create();
//        pTempArray->retain();
        m_pMapsArray->addObject(pTempArray);
        
        for (int j = 0; j < m_iMapCol; j++)
        {
            if (i == 0 || i == m_iMapRow-1 || j == 0 || j == m_iMapCol-1)
            {
                // Add empty icons.
                Icon *pNullIcon = Icon::create();
                pNullIcon->initSkinWithType(1);
                pNullIcon->setRow(i);
                pNullIcon->setCol(j);
                pNullIcon->updatePositionInParent();
                pNullIcon->setVisible(false);
                pNullIcon->setDestroyed(true);
                
                pTempArray->addObject(pNullIcon);
                this->addChild(pNullIcon);
            }
            else
            {
                // Add two icons each time.
                int iIconType = CCRANDOM_0_1() * 35 + 1;
                Icon *pIcon = Icon::create();
                pIcon->initSkinWithType(iIconType);
                pIcon->setRow(i);
                pIcon->setCol(j);
                pIcon->updatePositionInParent();
                this->addChild(pIcon);
                pTempArray->addObject(pIcon);
                
                j++;
                Icon *pIconClone = Icon::create();
                pIconClone->initSkinWithType(iIconType);
                pIconClone->setRow(i);
                pIconClone->setCol(j);
                pIconClone->updatePositionInParent();
                this->addChild(pIconClone);
                pTempArray->addObject(pIconClone);
            }
        }
    }
    
    randomMapArray(20);
}

void GameMapLayer::randomMapArray(const int &repeat)
{
    int iMaxRow = m_pMapsArray->count();
    int iMaxCol = ((CCArray *) m_pMapsArray->objectAtIndex(0))->count();
    
    for (int i = 0; i < repeat; i++)
    {
        int iRow1 = CCRANDOM_0_1() * (iMaxRow - 2) + 1;
        int iCol1 = CCRANDOM_0_1() * (iMaxCol - 2) + 1;
        
        int iRow2 = CCRANDOM_0_1() * (iMaxRow - 2) + 1;
        int iCol2 = CCRANDOM_0_1() * (iMaxCol - 2) + 1;
        
        CCLog("random 1 row: %d, col: %d", iRow1, iCol1);
        CCLog("random 2 row: %d, col: %d", iRow2, iCol2);
        
        Icon *pIcon1 = this->getIconAtRowAndCol(iRow1, iCol1);
        Icon *pIcon2 = this->getIconAtRowAndCol(iRow2, iCol2);
        
        int iIconType1 = pIcon1->getIconType();
        int iIconType2 = pIcon2->getIconType();
        
        pIcon1->initSkinWithType(iIconType2);
        pIcon2->initSkinWithType(iIconType1);
        
//        pIcon1->setRow(iRow2);
//        pIcon1->setCol(iCol2);
//        
//        pIcon2->setRow(iRow1);
//        pIcon2->setCol(iCol1);
//        
//        pIcon1->updatePositionInParent();
//        pIcon2->updatePositionInParent();
    }
}

cocos2d::CCSize GameMapLayer::getMapSize()
{
    return CCSizeMake(m_iMapWidth, m_iMapHeight);
}

void GameMapLayer::setIconToMaxTop(Icon *icon)
{
    this->removeChild(icon);
    this->addChild(icon, this->getChildrenCount());
    
//    icon->setZOrder(this->getChildrenCount());
}

cocos2d::CCArray*& GameMapLayer::getMapDataArray()
{
    return m_pMapsArray;
}

Icon* GameMapLayer::getIconAtRowAndCol(const int &row, const int &col)
{
    CCArray *pRowArray = (CCArray *) m_pMapsArray->objectAtIndex(row);
    Icon *pIcon = (Icon *) pRowArray->objectAtIndex(col);
    
    return pIcon;
}

void GameMapLayer::dispose()
{
    m_pMapsArray->release();
}
