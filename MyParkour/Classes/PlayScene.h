//
//  PlayScene.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-16.
//
//

#ifndef __MyParkour__PlayScene__
#define __MyParkour__PlayScene__

#include "cocos2d.h"
#include "Box2D.h"
#include "GLES-Render.h"

enum GameState
{
    GameState_Normal,
    GameState_Paused,
    GameState_Over,
};

class Runner;
class SimpleRecognizer;
class MapManager;

class PlayScene : public cocos2d::CCLayer
{
public:
    
    PlayScene();
    virtual ~PlayScene();
    
    static cocos2d::CCScene* scene();
    
    virtual bool init();
    virtual void update(float dt);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
	virtual void ccTouchCancelled(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    
    CREATE_FUNC(PlayScene);
    
private:
    
    void setDebug(bool isDebug);
    void initPhysics();
    
    virtual void draw();
    
private:
    
    b2World *m_pWorld;
    GLESDebugDraw *m_pDebugDraw;
    
    MapManager *m_pMapMgr;
    Runner *m_pRunner;
    float m_fLastEyeX;
    
    SimpleRecognizer *m_pRecognizer;
    
    GameState m_eGameState;
};

#endif /* defined(__MyParkour__PlayScene__) */
