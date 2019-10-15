#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH  32
#define BRICK_BBOX_HEIGHT 7

class CBrick : public CGameObject
{
	int width;
	int height;
public:

	CBrick(int w, int h) {
		ID = 1;
		width = w;
		height = h;
	};
	virtual void Render();
	virtual void GetBoundingBox(float &l, float &t, float &r, float &b);
};