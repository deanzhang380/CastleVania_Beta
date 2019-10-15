#include "Item.h"



void Item::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = left + width;
	bottom = top + height;
}

void Item::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (start == true)
	{
		vy += 0.0018f*dt;
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(coObjects, coEvents);
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}


}

void Item::Render()
{
	
	/*if (state == GroungObject_State_Dead)
	{
	ani = GroundObject_Ani_Dead;
	}*/
	if (start == true) {
		animations[0]->Render(x, y, 255);
		RenderBoundingBox(0, 0);
	}
	
}

Item::Item(int w, int h, int no, int wx, int wy)
{
	ID = 3;
	width = w;
	height = h;
	num = no;
	x = wx;
	y = wy;
	state = Item_visible;
}


Item::~Item()
{
}

void Item::SetState(int state)
{
	CGameObject::SetState(state);
	if (state ==Item_appear)
	{
		if (start == false) {
			start = true;
			//time_dead = -300;
		}
	}
	if (state == Item_hide)
	{
		//num = 0;
	}
}
