//
//  GameMessageLayer.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-21.
//
//

#ifndef __SimpleRaiden__GameMessageLayer__
#define __SimpleRaiden__GameMessageLayer__

#include "cocos2d.h"

class CGameMessageLayer : public cocos2d::CCLayer
{
public:
    
    virtual bool init();
    virtual void update(float dt);
    
    CREATE_FUNC(CGameMessageLayer);
    
private:
    
    void showScore();
    void showHp();
    void showLife();
    void showMissile();
    void shootMissile(CCObject* pSender);
    
private:
    
    cocos2d::CCSprite *m_pHp;
    cocos2d::CCLabelAtlas *m_pScore;
    cocos2d::CCLabelAtlas *m_pLife;
    cocos2d::CCLabelAtlas *m_pMissileNum;
    cocos2d::CCMenuItemImage *m_pMissileItem;
    
    int m_iHeight;
    int m_iWidth;
    float m_fMinX;
    float m_fMinY;
};

#endif /* defined(__SimpleRaiden__GameMessageLayer__) */
