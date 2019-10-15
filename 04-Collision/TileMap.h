#pragma once
#include<iostream>
#include <string>
#include "Sprites.h"
#define Tile_WIDTH 32
#define Tile_HEIGHT 32
class TileMap
{
	int **map;
	int row;
	int column;

	float width;
	float height;

	CSprites *sprites;
public:
	TileMap();
	~TileMap();
	void GetSize(float &width, float &height) { width = this->width; height = this->height; }
	void LoadTileMap(string fileName, LPDIRECT3DTEXTURE9 tex);
	void Render(float x, float y);
	void ReplaceWord(std::string& source, const char* WordToFind, const char* WordToReplace);
	vector<string> split(string str, string token);
};

