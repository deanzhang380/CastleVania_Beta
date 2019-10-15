#pragma once
#include "GameObject.h"
#include "Ropes.h"
#include "Item.h"
#include "Subweapon.h"
#include "Dagger.h"

#define Frame 60


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
class Simon :public CGameObject
{
	int time_attack = 0;
	int time_jump = 0;

	bool is_sit = false;
	bool is_jumping = false;
	bool is_attack = false;
	
	int rx;
	int untouchable;
	
	DWORD untouchable_start;
	
public:

	Simon();
	~Simon();
	Ropes * ropes;
	int unmovable ;
	int sub_attack;
	int id_subwp;
	/*vector<Subweapon*> sw;*/
	int flag = 0;
	Subweapon *sw;
	DWORD attack_start;
	DWORD unmovable_start;
	vector<LPGAMEOBJECT> *objects;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *colliable_objects = NULL);
	virtual void Render();
	void SetState(int state);
	/*void SetLevel(int l) { level = l; }*/
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void StartUnmovable() { unmovable = 1; unmovable_start = GetTickCount(); }
	void StartAttack() { is_attack = true; attack_start = GetTickCount(); }
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);

	void Set_Sit(bool x)
	{
		is_sit = x;
	}

	void Set_Jump(bool x)
	{
		is_jumping = x;
	}

	bool Can_Move();

	bool Get_Sit()
	{
		return is_sit;
	}
	void GetRope(Ropes *r) { ropes = r; }

	void ReturnSubWP();
	void UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects);
};

