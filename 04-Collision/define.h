#pragma once

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_SIMON 30
#define ID_TEX_Bricks 40
#define ID_TEX_Objects 50
#define ID_MAP_SENCE1 1001
#define ID_TEX_ITEM 60


#define Simon_WALKING_SPEED		0.08f 
#define Simon_JUMP_SPEED_Y		0.6f
#define Simon_JUMP_DEFLECT_SPEED 0.2f
#define Simon_GRAVITY			0.0018f
#define Simon_DIE_DEFLECT_SPEED	 0.5f

#define Simon_STATE_IDLE			0
#define Simon_STATE_WALKING_RIGHT	100
#define Simon_STATE_WALKING_LEFT	200
#define Simon_STATE_JUMP			300
#define Simon_STATE_DIE				400
#define Simon_STATE_SIT	500
#define Simon_STATE_ATTACK	600
#define Simon_STATE_SIT_ATTACK 700
#define Simon_STATE_SUB_WEBPON 800

#define Simon_ANI_NORMAL_IDLE_RIGHT		0
#define Simon_ANI_NORMAL_IDLE_LEFT			1
#define Simon_ANI_SIT_IDLE_RIGHT		2
#define Simon_ANI_SIT_IDLE_LEFT		3

#define Simon_ANI_NORMAL_WALKING_RIGHT			4
#define Simon_ANI_NORMAL_WALKING_LEFT			5
#define Simon_ANI_ATTACK_RIGHT		6
#define Simon_ANI_ATTACK_LEFT		7
#define Simon_ANI_SIT_ATTACK_RIGHT  8
#define Simon_ANI_SIT_ATTACK_LEFT	9
#define Simon_ANI_DIE				10

//#define	Simon_LEVEL_SMALL	1
//#define	Simon_LEVEL_BIG		2

#define Simon_BIG_BBOX_WIDTH  16
#define Simon_BIG_BBOX_HEIGHT 30

#define Simon_SIT_BBOX_WIDTH 16
#define Simon_SIT_BBOX_HEIGHT 40
//#define Simon_SMALL_BBOX_WIDTH  13
//#define Simon_SMALL_BBOX_HEIGHT 15

#define Simon_UNTOUCHABLE_TIME 5000
#define Simon_UNMOVABLE_TIME 300

#define Rope_BBOX_WIDTH 24
#define Rope_BBOX_HEIGHT 11
#define Rope_BBOX_WIDTH_LEVEL_2 40
#define Rope_States_Right 0
#define Rope_States_left 1

#define State_Alive 100
#define State_Dead 200

#define Object_Ani_Dead 0
#define Object_Ani_Alive 1

#define Item_hide 11
#define Item_appear 12
#define Item_visible 13

#define Dagger_width 18
#define Dagger_height 9

#define Item_ID_Rope 802
#define Item_ID_Big_Heart 801
#define Item_ID_Dagger 803

#define SubWeapon_Dagger 0