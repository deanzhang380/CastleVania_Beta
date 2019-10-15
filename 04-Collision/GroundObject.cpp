#include "GroundObject.h"



void GroundObject::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	if (num == 1)
	{
		left = x;
		top = y;
		right = x + width;
		bottom = y + height;
	}
}

void GroundObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (time_dead < 0 && start ==true)
	{
		time_dead += 100;
		
	}
	if (time_dead == 0 && start == true)
	{
		num = Object_Ani_Dead;
		k++;
	}

	if (k >= 30)
	{
		item->SetState(Item_appear);
		item->SetPosition(this->x, this->y);
		coObjects->push_back(item);	
	}
	/*if (time_dead == 0 && start == true)
	{
		y-=100;
	}*/
}

void GroundObject::Render()
{
	int ani = num;
	/*if (state == GroungObject_State_Dead)
	{
		ani = GroundObject_Ani_Dead;
	}*/
	animations[ani]->Render(x, y,255);
	RenderBoundingBox(0, 0);
}




GroundObject::~GroundObject()
{
}

void GroundObject::CreateItem(int w, int h, int no, int wx, int wy)
{
	item = new Item(w, h,  no,  wx, wy);
}

void GroundObject::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == State_Dead)
	{
		if (start == false) {
			start = true;
			time_dead = -300;
		}
	}
}
