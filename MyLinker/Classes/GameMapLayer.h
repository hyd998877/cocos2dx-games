//
//  GameMapLayer.h
//  MyLinker
//
//  Created by zhouf369 on 14-8-15.
//
//

#ifndef __MyLinker__GameMapLayer__
#define __MyLinker__GameMapLayer__

#include "cocos2d.h"

class Icon;

class GameMapLayer : public cocos2d::CCLayer
{
public:
    
    GameMapLayer();
    ~GameMapLayer();
    
    virtual bool init();
    
    CREATE_FUNC(GameMapLayer);
    
public:
    
    void initMapWithRowAndCol(const int &row, const int &col);
    cocos2d::CCSize getMapSize();
    void setIconToMaxTop(Icon *icon);
    
    static cocos2d::CCArray*& getMapDataArray();
    static Icon* getIconAtRowAndCol(const int &row, const int &col);
    
public:
    
    static const int m_iIconWidth;
    static const int m_iIconHeight;
    static int m_iMapRow;
    static int m_iMapCol;
    
private:
    
    void randomMapArray(const int &repeat);
    void dispose();
    
private:
    
    int m_iMapWidth;
    int m_iMapHeight;
    
    static cocos2d::CCArray *m_pMapsArray;
};

#endif /* defined(__MyLinker__GameMapLayer__) */
