//
//  GameConfig.cpp
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-11.
//
//

#include "GameConfig.h"
#include "GameMenuLayer.h"
#include "GameOverLayer.h"
#include "GameLevelLayer.h"
#include "GameManagerLayer.h"

using namespace cocos2d;

int g_iGameLevel = LEVEL_ONE;

void startFlipInterface(int iType)
{
    CCScene *pScene = NULL;
    
    if(iType == GAME_MENU)
	{
		pScene = CCTransitionFadeDown::create(1.0f, CGameMenuLayer::scene());
	}
	else if(iType == GAME_LEVEL)
	{
		pScene = CCTransitionSplitRows::create(1.0f, CGameLevelLayer::scene());
	}
	else if(iType == GAME_START)
	{
		pScene = CCTransitionCrossFade::create(1.0f, CGameManagerLayer::scene());
	}
	else if(iType == GAME_OVER)
	{
		pScene = CCTransitionFlipX::create(1.0f, CGameOverLayer::scene());
	}
	else
		return;
    
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void loadExplosionAnim()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/explosion.plist");
	CCArray *animFrames = CCArray::create();
	char str[64] = {0};
	for (int i = 1; i < 35; i++) {
		sprintf(str, "explosion_%02d.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.04f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, EXPLOSION_ANIMATION_NAME);
}

void loadItemsAnim()
{
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Image/Item.plist");
	CCArray *animFrames = CCArray::create();
	char str[64] = {0};
	for (int i = 1; i < 8; i++) {
		sprintf(str, "Gold_%02d.png", i);
		CCSpriteFrame *frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation *animation = CCAnimation::createWithSpriteFrames(animFrames, 0.2f);
	CCAnimationCache::sharedAnimationCache()->addAnimation(animation, GOLD_ANIMATION_NAME);
}

CCPointArray * getEnemyMoveArray1()
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPointArray *pArray = CCPointArray::create(10);
    pArray->addControlPoint(ccp(0, 0));
    int iFlag = -1;
    for (int i = 1; i < 7; i++)
    {
        iFlag = -iFlag;
        pArray->addControlPoint(ccp(size.width/3.0f*iFlag, -size.height*i/5.0f));
    }
    
    return pArray;
}

#define DIRECTION_TO_RIGHT 1
#define DIRECTION_TO_LEFT -1

CCPointArray * getEnemyMoveArray2(int iDirection)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPointArray *pArray = CCPointArray::create(4);
    
    pArray->addControlPoint(ccp(0, 0));
    pArray->addControlPoint(ccp(iDirection*size.width*3/5.0f, -size.height/5.0f));
    pArray->addControlPoint(ccp(iDirection*size.width*4/5.0f, -size.height/5.0f));
    pArray->addControlPoint(ccp(-iDirection*size.width*1/5.0f, -size.height*6/5.0f));
    
    return pArray;
}

CCPointArray* getEnemyMoveArray(int iType)
{
    CCPointArray *pArray = NULL;
    switch (iType)
    {
        case ENEMY_MOVE_ONE:
            pArray = getEnemyMoveArray1();
            break;
            
        case ENEMY_MOVE_TWO:
            pArray = getEnemyMoveArray2(DIRECTION_TO_RIGHT);
            break;
            
        case ENEMY_MOVE_THREE:
            pArray = getEnemyMoveArray2(DIRECTION_TO_LEFT);
            break;
            
        default:
            break;
    }
    
    return pArray;
}

CCPointArray* getBossArray1(int iHeight, int iWidth)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPointArray *pArray = CCPointArray::create(15);
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    for(int i = 0; i < 3; i++)
    {
        pArray->addControlPoint(ccp(iWidth/2, size.height*3/4));
        pArray->addControlPoint(ccp(size.width - iWidth/2, size.height*3/4));
    }
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    pArray->addControlPoint(ccp(size.width/2, iHeight/2));
    pArray->addControlPoint(ccp(iWidth/2, (size.height*3/4 - iHeight/2)*1/3 + iHeight/2));
    pArray->addControlPoint(ccp(size.width - iWidth/2, (size.height*3/4 - iHeight/2)*2/3 + iHeight/2));
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    
    return pArray;
}

CCPointArray* getBossArray2(int iHeight, int iWidth)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPointArray *pArray = CCPointArray::create(15);
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    for(int i = 0; i < 2; i++)
    {
        pArray->addControlPoint(ccp(iWidth/2, size.height*2/3));
        pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
        pArray->addControlPoint(ccp(size.width - iWidth/2, size.height*2/3));
    }
    pArray->addControlPoint(ccp(iWidth/2, (size.height*3/4 - iHeight/2)*2/3 + iHeight/2));
    pArray->addControlPoint(ccp(size.width - iWidth/2, (size.height*3/4 - iHeight/2)*1/3 + iHeight/2));
    pArray->addControlPoint(ccp(size.width/2, iHeight/2));
    pArray->addControlPoint(ccp(iWidth/2, (size.height*3/4 - iHeight/2)*1/3 + iHeight/2));
    pArray->addControlPoint(ccp(size.width - iWidth/2, (size.height*3/4 - iHeight/2)*2/3 + iHeight/2));
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    
    return pArray;
}

CCPointArray* getBossArray3(int iHeight, int iWidth)
{
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    CCPointArray *pArray = CCPointArray::create(15);
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    pArray->addControlPoint(ccp(iWidth/2, (size.height*3/4 - iHeight/2)*1/2 + iHeight/2));
    pArray->addControlPoint(ccp(size.width/2, iHeight/2));
    pArray->addControlPoint(ccp(size.width - iWidth/2, (size.height*3/4 - iHeight/2)*1/2 + iHeight/2));
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    pArray->addControlPoint(ccp(size.width - iWidth/2, size.height*3/4));
    pArray->addControlPoint(ccp(size.width - iWidth/2, iHeight/2));
    pArray->addControlPoint(ccp(iWidth/2, iHeight/2));
    pArray->addControlPoint(ccp(iWidth/2, size.height*3/4));
    pArray->addControlPoint(ccp(size.width/2, size.height*3/4));
    
    return pArray;
}

CCPointArray* getBossMoveArray(int iType, int iHeight, int iWidth)
{
    CCPointArray *pArray = NULL;
    switch (iType)
    {
        case BOSS_MOVE_ONE:
            pArray = getBossArray1(iHeight, iWidth);
            break;
            
        case BOSS_MOVE_TWO:
            pArray = getBossArray2(iHeight, iWidth);
            break;
            
        case BOSS_MOVE_THREE:
            pArray = getBossArray3(iHeight, iWidth);
            break;
            
        default:
            break;
    }
    
    return pArray;
}