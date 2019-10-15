#pragma once
#include"Game.h"
#include"GameObject.h"
#include "define.h"
class Item: public CGameObject
{
	int width, height;
	int num;
	
public:
	bool start = false;
	Item(int w, int h, int no, int wx, int wy);
	~Item();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
	int GetNum() { return num; }
};

