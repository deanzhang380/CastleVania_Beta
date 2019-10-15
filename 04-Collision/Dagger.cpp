#include "Dagger.h"



Dagger::Dagger(int x, int y,int nx)
{
	this->x = x;
	this->y = y+5;
	ID = 4;
	//state = Item_appear;
	this->AddAnimation(803);
	this->AddAnimation(804);
	this->nx = nx;
}

void Dagger::SetNX(int nx)
{
	this->nx = nx;
}


Dagger::~Dagger()
{
}

void Dagger::GetBoundingBox(float & l, float & t, float & r, float & b)
{
	l = x ;
	t = y;
	r = l + Dagger_width;
	b = y + Dagger_height;
}

void Dagger::Render()
{
	if (state = Item_appear) {
		if (nx > 0) {
			animations[0]->Render(x, y, 255);
			RenderBoundingBox(0, 0);
		}
		if (nx < 0)
		{
			animations[1]->Render(x, y, 255);
			RenderBoundingBox(0, 0);
		}
	}
}

void Dagger::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	x += dx;
}

void Dagger::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case Item_appear:
		vx =nx* 0.04f;
		break;
	default:
		break;
	}
}
