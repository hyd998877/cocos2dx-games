//
//  Icon.h
//  MyLinker
//
//  Created by zhouf369 on 14-8-15.
//
//

#ifndef __MyLinker__Icon__
#define __MyLinker__Icon__

#include "cocos2d.h"

enum ICON_SEL
{
    SELECTED = 0,
    UN_SELECTED
};

class Icon : public cocos2d::CCSprite
{
public:
    
    Icon();
    ~Icon();
    
    virtual bool init();
    
    CREATE_FUNC(Icon);
    
public:
    
    void initSkinWithType(const int &type);
    
    void changeIconViewWithType(ICON_SEL type);
    
    void fadeOutAction(float dt);
    
    void updatePositionInParent();
    
    void dispose();
    
    void playAction();
    void unplayAction();
    
    const int& getIconType();
    
    int getRow() { return m_iRow; }
    void setRow(int iRow) { m_iRow = iRow; }
    int getCol() { return m_iCol; }
    void setCol(int iCol) { m_iCol = iCol; }
    bool getDestroyed() { return m_bDestroyed; }
    void setDestroyed(bool isDestroy) { m_bDestroyed = isDestroy; }
    
    
private:
    int m_iIconType;
    int m_iRow;
    int m_iCol;
    bool m_bDestroyed;
};

#endif /* defined(__MyLinker__Icon__) */
