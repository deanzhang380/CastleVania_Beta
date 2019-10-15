#include <fstream>
#include "TileMap.h"
#include "Game.h" 
#include "Library/pugiconfig.hpp"
#include "Library/pugixml.hpp"
#include <string>
#include<iostream>
#include <algorithm>
using namespace std;
using namespace pugi;

TileMap::TileMap()
{
}


TileMap::~TileMap()
{
}

void TileMap::LoadTileMap(string fileName, LPDIRECT3DTEXTURE9 tex)
{
	ifstream in(fileName);
	if (!in)
	{
		//DebugOut(L"Can't not open file\n");
		return;
	}
	string matrix;
	vector<string> c;
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(fileName.c_str());
	
	if (result)
	{
		string a = doc.child("map").attribute("width").value();
		column = stoi(a);
		string b = doc.child("map").attribute("height").value();
		row = stoi(b);

		matrix = doc.child("map").child("layer").child("data").text().get();
		//getline(matrix,",")


		c = split(matrix, "\n");
		//vector <int> d = stoi(split(c[1], ","));
		//string chars = "\n";
		//matrix.erase(std::remove(matrix.begin(), matrix.end(), "\n"), matrix.end());
		//replace(matrix.begin(), matrix.end(), "\n", "\0");
	}
	sprites = CSprites::GetInstance();

	
	/*in >> column;
	in >> row;*/
	//string a = doc.

	width = (float)Tile_WIDTH * column;
	height = (float)Tile_HEIGHT * row;

	//khoi tao ma tran map
	int i = 0;
	int j = 0;

	map = new int *[row];
	for (i = 0; i < row; i++)
		map[i] = new int[column];
	i = 0;
	
	int k = 1;
	for (int a = 0; a < row; a++)
	{
		vector<string> substr = split(c[k], ",");
		int l = 0;
		for (int b = 0; b < column; b++)
		{
			map[a][b] =stoi(substr[l]);
			l++;
		}

		k++;
	}

	int m = map[0][22];
	int id = 1;
	int tileset_width=stoi(doc.child("map").child("tileset").child("image").attribute("width").value());
	int tileset_height= stoi(doc.child("map").child("tileset").child("image").attribute("height").value());

	/*in >> tileset_width;
	in >> tileset_height;*/
	//in.close();

	int left, top;

	for (top = 0; top < tileset_height; top += Tile_HEIGHT)
		for (left = 0; left < tileset_width; left += Tile_WIDTH)
		{
			sprites->Add(id, left, top, left + Tile_WIDTH, top + Tile_HEIGHT, tex);
			id++;
		}
}

void TileMap::Render(float x, float y)
{
	int i, j;
	float x0, y0;
	x0 = x;
	y0 = y;
	float cam_x, cam_y;
	CGame *game = CGame::GetInstance();
	game->GetCamPos(cam_x, cam_y);
	
	for (i = 0; i < row; i++)
		for (j = 0; j < column; j++)
		{
			sprites->Get(map[i][j])->Draw(x, y);
			if (j < column - 1) x += Tile_WIDTH/*+ offset_x*/;
			else
			{
				x = x0;
				if (i < row) y += Tile_HEIGHT/*+ offset_y*/;
			}
		}
}

void TileMap::ReplaceWord(std::string & source, const char * WordToFind, const char * WordToReplace)
{
	size_t LengthOfWordToReplace = strlen(WordToFind);
	size_t replaceLen = strlen(WordToReplace);
	size_t positionToSearchAt = 0;

	//search for the next word 
	while ((positionToSearchAt = source.find(WordToFind, positionToSearchAt)) != std::string::npos)
	{
		//replace the found word with the new word
		source.replace(positionToSearchAt, LengthOfWordToReplace, WordToReplace);

		// move to next position
		positionToSearchAt += replaceLen;
	}
}

vector<string> TileMap::split(string str, string token)
{
	vector<string>result;
	while (str.size()) {
		int index = str.find(token);
		if (index != string::npos) {
			result.push_back(str.substr(0, index));
			str = str.substr(index + token.size());
			if (str.size() == 0)result.push_back(str);
		}
		else {
			result.push_back(str);
			str = "";
		}
	}
	return result;
}



