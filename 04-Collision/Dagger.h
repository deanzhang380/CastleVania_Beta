#pragma once
#include "GameObject.h"
#include "define.h"
#include "Subweapon.h"
class Dagger: public Subweapon 
{
public:
	Dagger(int x, int y,int nx);
	void SetNX(int nx);
	~Dagger();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void SetState(int state);
};

