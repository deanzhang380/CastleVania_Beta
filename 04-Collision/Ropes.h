#pragma once
#include "GameObject.h"
#include "Game.h"
#define Rope_BBOX_WIDTH 24
#define Rope_BBOX_HEIGHT 11
#define Rope_States_Right 0
#define Rope_States_left 1


class Ropes : public CGameObject
{
	int level = 0;
	int dir = 0;
	int a=0;
	int v=1;
	int type = 0;
	int time_visible = 0;
	int time = 0;
	int k = 0;
public:
	bool is_CheckBB = false;
	bool is_right = true;
	bool is_attack = false;
	bool is_sit = false;
	bool is_visible = true;
	Ropes();
	Ropes(int x, int y);
	~Ropes();
	void SetState(int state);
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	void LoadResource();
	void SetPosition(int x, int y,int v);
	void SetAttack(bool tf) { this->is_attack = tf; }
	void SetLevel();
};
