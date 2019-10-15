#pragma once
#include "GameObject.h"
#include "define.h"
#include "Item.h"

class GroundObject: public CGameObject
{
	
	Item *item;
	int width, height;
	int num;
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
	virtual void Render();
public:
	
	bool remove = false;
	bool start = false;
	int time_dead ;
	void SetNum(int x) { this->num = x; }
	GroundObject(int x, int w, int h) { num = x; width = w; height = h; ID = 2; }
	~GroundObject();
	void CreateItem(int w, int h, int no, int wx, int wy);
	void SetItem(Item *i) { item = i; }
	virtual void SetState(int state);
};

