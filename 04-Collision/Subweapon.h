#pragma once
#include"Game.h"
#include "GameObject.h"
class Subweapon:public CGameObject
{

public:
	Subweapon();
	~Subweapon();
	virtual void Render()=0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)=0;
	virtual void SetState(int state)=0;
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b)=0;
};

