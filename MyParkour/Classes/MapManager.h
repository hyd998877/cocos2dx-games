//
//  MapManager.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-25.
//
//

#ifndef __MyParkour__MapManager__
#define __MyParkour__MapManager__

#include "cocos2d.h"
#include "Box2D.h"

class MapManager : public cocos2d::CCNode
{
public:
    
    MapManager();
    ~MapManager();
    
    static MapManager* create(cocos2d::CCLayer *pLayer, b2World *pWorld);
    
    bool init(cocos2d::CCLayer *pLayer, b2World *pWorld);
    
    bool checkReloadMap(float fEyeX);
    float getMapWidth() { return m_fMapWidth; }
    int getCurMapIndex() { return m_iCurMap; }
    
private:
    
    int m_iMapCount;
    int m_iCurMap;
    float m_fMapWidth;
    
    cocos2d::CCLayer *m_pParentLayer;
    b2World *m_pWorld;
    
    cocos2d::CCSprite *m_pMap0;
    cocos2d::CCSprite *m_pMap1;
    
    cocos2d::CCSprite *m_pGround0;
    cocos2d::CCSprite *m_pGround1;
};

#endif /* defined(__MyParkour__MapManager__) */
