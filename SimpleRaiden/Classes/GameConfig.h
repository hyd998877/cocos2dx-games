//
//  GameConfig.h
//  SimpleRaiden
//
//  Created by zhouf369 on 14-10-11.
//
//

#ifndef __SimpleRaiden__GameConfig__
#define __SimpleRaiden__GameConfig__

#include "cocos2d.h"

#define RESOLUTION_WIDTH 320
#define RESOLUTION_HEIGHT 480

#define GOLD_ANIMATION_NAME "Gold_Animation"
#define EXPLOSION_ANIMATION_NAME "Explosion"

enum
{
	GAME_MENU = 1,
	GAME_LEVEL,
	GAME_START,
	GAME_OVER,
};

enum
{
	LEVEL_ONE = 1,
	LEVEL_TWO,
	LEVEL_THREE,
};

enum
{
    ENEMY_MOVE_ONE = 1,
    ENEMY_MOVE_TWO,
    ENEMY_MOVE_THREE,
};

enum
{
    BOSS_MOVE_ONE = 1,
    BOSS_MOVE_TWO,
    BOSS_MOVE_THREE,
};

extern int g_iGameLevel;

void startFlipInterface(int iType);

void loadExplosionAnim();
void loadItemsAnim();

cocos2d::CCPointArray* getEnemyMoveArray(int iType);
cocos2d::CCPointArray* getBossMoveArray(int iType, int iHeight, int iWidth);

#endif /* defined(__SimpleRaiden__GameConfig__) */
