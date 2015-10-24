//
//  resources.h
//  MyParkour
//
//  Created by zhouf fang on 14-7-15.
//
//

#ifndef MyParkour_resources_h
#define MyParkour_resources_h

#define RATIO 32

#define GROUND_HEIGHT 57.0f
#define RUNNER_STARTX 80.0f

enum OBJTAGS
{
    RUNNER_TAG = 1000,
    COIN_TAG,
    ROCK_TAG,
    INFOS_LAYER_TAG
};

#define BACK_MUSIC "background.mp3"
#define JUMP_MUSIC "jump.mp3"
#define CROUCH_MUSIC "crouch.mp3"

#define pickUpCoins "pickup_coin.mp3"

#define spritesheet "parkour.plist"

#define spritePacker "parkour.png"
#define runner0 "runner0.png"
#define runnerCrouch "runnerCrouch0.png"

#define map0 "Map00.png"
#define map1 "Map01.png"

#define ground0 "Ground00.png"
#define ground1 "Ground01.png"

#define coin0 "coin0.png"

#define rockdown "rock.png"
#define rockhat "hathpace.png"

#endif
