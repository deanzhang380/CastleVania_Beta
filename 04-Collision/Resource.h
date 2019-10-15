#pragma once
#include <string>
#include "Simon.h"
#include "pugixml.hpp"
#include "pugiconfig.hpp"
#include "Textures.h"
#include "Sprites.h"
#include "Ropes.h"
#include "Item.h"
class Resource
{
	Item *item;
	Simon *simon;
	Ropes *ropes;
	vector<LPGAMEOBJECT> *objects;
public:
	Resource();
	~Resource();
	void LoadResourceSimon(string file);
	void LoadResourceRope(string file);
	void LoadResourceItem(string file);
	void GetSimon(Simon * s) {
		simon = s;
	}
	void GetVectorObject(vector<LPGAMEOBJECT> *ob) { objects = ob; }
	void GetRopes(Ropes *r) { ropes = r; }
	void GetItem(Item *i) { item = i; }

};

