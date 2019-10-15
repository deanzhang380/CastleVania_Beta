#pragma once
#include"Simon.h"
#include "Game.h"
#include "Ropes.h"
#include "Brick.h"
#include "TileMap.h"
#include "GroundObject.h"
#include "Sprites.h"
#include"Textures.h"
#include"pugixml.hpp"
#include "pugiconfig.hpp"
#include "define.h"
#include "Resource.h"
#include "debug.h"
class Map
{
	//CGame *game;

	//CMario *mario;
	//CGoomba *goomba;
	int level_map;
	
	Ropes *rope;
	TileMap *tilemap;
	GroundObject *groundobject;
	vector<LPGAMEOBJECT> *objects;
	Resource rs;
	Simon *simon;
	CGame *game;
public:

	Map(int level);
	~Map();
	void Update(DWORD dt);
	void LoadResource();
	void SetVarible(Simon *s, vector<LPGAMEOBJECT> *ob, TileMap *tm) { simon = s; objects = ob; tilemap = tm; }
	void LoadMap(string file,LPDIRECT3DTEXTURE9 map);
	void LoadObject(string file);
	void KeyState(BYTE *states);
	void OnKeyDown(int KeyCode);
	void OnKeyUp(int KeyCode);
};



