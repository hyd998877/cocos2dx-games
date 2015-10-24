//
//  GameSceneLayer.h
//  MyLinker
//
//  Created by zhouf369 on 14-8-19.
//
//

#ifndef __MyLinker__GameSceneLayer__
#define __MyLinker__GameSceneLayer__

#include "cocos2d.h"

class Icon;
class GameMapLayer;

class GameSceneLayer : public cocos2d::CCLayer
{
public:
    
    static cocos2d::CCScene* createScene();
    
    virtual bool init();
    virtual void registerWithTouchDispatcher(void);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    
    CREATE_FUNC(GameSceneLayer);
    
private:
    
    void initSelIconToNull();
    bool checkSelIcon(Icon *pIcon1, Icon *pIcon2);
    
private:
    
    GameMapLayer *m_pGameMapLayer;
    
    Icon *m_pFirstIcon;
    Icon *m_pSecondIcon;
};

#endif /* defined(__MyLinker__GameSceneLayer__) */
