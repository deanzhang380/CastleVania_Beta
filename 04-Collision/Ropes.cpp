#include "Ropes.h"
#include "GroundObject.h"
#include <dos.h>
Ropes::Ropes()
{
	
}


Ropes::Ropes(int wx, int wy)
{
	x = wx - 7;
	y = wy;
}


Ropes::~Ropes()
{

}

void Ropes::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case Rope_States_Right:
		is_attack = true;
		type = 0;
		nx = 1;
		time = -300;
		//a = -200;
		//a = (float)GetTickCount()/100000;
		break;
	case Rope_States_left:
		is_attack = true;
		nx = -1;
		time = -300;
		break;
	}

}

void Ropes::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	if(v==1){
		l = x + 40;
		t = y;
		if (level != 2) {
			r = l + Rope_BBOX_WIDTH;
		}
		else {
			r = l + Rope_BBOX_WIDTH_LEVEL_2;
		}
		b = y + Rope_BBOX_HEIGHT;
	}
	if (v == 0)
	{
		l = x;
		t = y;
		if (level != 2) {
			r = l + Rope_BBOX_WIDTH;
		}
		else {
			r = l + Rope_BBOX_WIDTH_LEVEL_2;
		}
		b = y + Rope_BBOX_HEIGHT;
	}
	
}

void Ropes::Render()
{

	if (is_visible == false) {
		if (is_attack == true && v==1)
		{
			dir = 0;
			animations[level+level+dir]->Render(x,y,255);
		}
		if (is_attack == true && v==0) {
			dir = 1;
			animations[level+level+dir]->Render(x, y, 255);
		}	
	}
	//animations[type]->Render(x, y, 255);
	if (v == 1)
	{
		RenderBoundingBox(38, 10);
	}
	if (v == 0)
	{
		RenderBoundingBox(0, 10);
	}

}

void Ropes::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	if (time < 0)
	{
		time += 100;
		k++;
	}
	if (time >= 0)
	{	
		is_CheckBB = false;
		is_attack = false;
		is_visible = true;
	}
	if (k >= 29)
	{
		k = 0;
	}
	if (is_attack == true)
	{
		is_visible = false;
		if (k == 20)
		{
			is_CheckBB = true;
		}
	}
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;
	coEvents.clear();

	vector<LPGAMEOBJECT>* vector1 = new vector<LPGAMEOBJECT>;
	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->ID == 2)
			vector1->push_back(coObjects->at(i));
	}

	CalcPotentialCollisions(vector1, coEvents);

	for (auto Object : *vector1)
	{
		float al, at, ar, ab, bl, bt, br, bb;
		GetBoundingBox(al, at, ar, ab);
		Object->GetBoundingBox(bl, bt, br, bb);
		if (CGame::GetInstance()->Is_Intersect({ long(al),long(at),long(ar),long(ab) }, { long(bl), long(bt), long(br), long(bb) }))
		{
			if (this->is_visible == false )
			{		
				if (is_CheckBB == true) {
					Object->SetState(200);
					k = 0;
				}
			}
		} 

		
	}
	/*if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<GroundObject*>(e->obj))
			{
				GroundObject *groundobject = dynamic_cast<GroundObject *>(e->obj);
				
					groundobject->SetState(GroungObject_State_Dead);
				
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}*/
	
}


void Ropes::LoadResource()
{

}

void Ropes::SetPosition(int wx, int wy, int v)
{
	if (v == 1)//right
	{
		x = wx - 8;
		y = wy - 2;
		this->v = v;
	}
	if (v == 0)//left
	{
		if (level == 0 || level==1) {
			x = wx - 18;
		}
		else {
			x = wx - 35;
		}
		y = wy - 2;
		this->v = v;
	}
}

void Ropes::SetLevel()
{
	level += 1;
}


