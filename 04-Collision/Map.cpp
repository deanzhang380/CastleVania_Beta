#include "Map.h"



Map::Map(int level)
{
	level_map = level;

}


Map::~Map()
{
}

void Map::Update(DWORD dt)
{
	
}


void Map::LoadResource()
{
	game = CGame::GetInstance();
	rs.GetSimon(simon);
	rs.GetVectorObject(objects);
	rs.LoadResourceSimon("textures\\Resource\\LoadSimon.xml");
	rope = new Ropes();
	rs.GetRopes(rope);
	rs.LoadResourceRope("textures\\Resource\\LoadRope.xml");
	rs.LoadResourceItem("textures\\Resource\\LoadItem.xml");
	CTextures * textures = CTextures::GetInstance();

	
	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_MAP_SENCE1, L"textures\\map1_outside_01_bank.png", D3DCOLOR_XRGB(255, 255, 255));
	textures->Add(ID_TEX_Objects, L"textures\\objects.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_ITEM, L"textures\\items.png", D3DCOLOR_XRGB(128, 0, 0));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_MAP_SENCE1);
	LPDIRECT3DTEXTURE9 texObject = textures->Get(ID_TEX_Objects);
	//Big Candles
	sprites->Add(30001, 47, 23, 64, 56, texObject);
	sprites->Add(30002, 74, 23, 91, 56, texObject);

	//hit effect
	sprites->Add(30011, 41, 77, 51, 92, texObject);
	sprites->Add(30012, 55, 76, 65, 91, texObject);


	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
	sprites->Add(20001, 408, 225, 424, 241, texMisc);

	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);

	LPANIMATION ani;

	ani = new CAnimation(100);		// brick
	ani->Add(20001);
	animations->Add(601, ani);

	ani = new CAnimation(100);
	ani->Add(30001);
	ani->Add(30002);
	animations->Add(701, ani);

	ani = new CAnimation(100);
	ani->Add(30011);
	ani->Add(30012);
	animations->Add(702, ani);

	
	if (level_map == 1) {
		LoadMap("textures\\map1_outside_01_map.tmx", texMap);
		LoadObject("textures\\map1_outside_01_map.tmx");
	}
}

void Map::LoadMap(string file,LPDIRECT3DTEXTURE9 map)
{
	
		tilemap->LoadTileMap(file, map);
}

void Map::LoadObject(string file)
{
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());
	for (auto node : doc.child("map").children("objectgroup"))
	{
		if (stoi(node.attribute("id").value())== 4)
		{
			for (auto node1 :node.children("object"))
			{
				int width = stoi(node1.attribute("width").value());
				int height = stoi(node1.attribute("height").value());
				CBrick *brick = new CBrick(width,height);
				//brick->AddAnimation(601);
				brick->SetPosition(stoi(node1.attribute("x").value()), stoi(node1.attribute("y").value())+39);
				objects->push_back(brick);
			}
		}
		if (stoi(node.attribute("id").value()) == 3)
		{
			for (auto node1 : node.children("object"))
			{
				GroundObject *go = new GroundObject(stoi(node1.attribute("type").value()), stoi(node1.attribute("width").value()), stoi(node1.attribute("height").value()));
				go->AddAnimation(702);
				go->AddAnimation(701);
				//go->SetNum(1);
				go->SetPosition(stoi(node1.attribute("x").value()), stoi(node1.attribute("y").value()) + 39);
				int w, h, no, x, y;
				int i = 0;
				for (auto node2 : node1.child("properties").children("property"))
				{
					int temp = 0;
					switch (i)
					{
					case 0:
						no = stoi(node2.attribute("value").value()); break;
					case 1:
						h = stoi(node2.attribute("value").value()); break;
					case 2:
						w = stoi(node2.attribute("value").value()); break;
					case 3:
						x = stoi(node1.attribute("x").value()); break;
					case 4:
						y = stoi(node1.attribute("y").value())+40; break;
					}
					i=i+1;
				}
				//go->CreateItem(w, h, no, x, y);
				Item *item = new Item(w, h, no, -200, -200);
				item->AddAnimation(no);
				go->SetItem(item);
				objects->push_back(item);
				objects->push_back(go);
			}
		}
	}
	
}

void Map::KeyState(BYTE * states)
{
	if (simon->unmovable == 1)
	{
		return;
	}
	if (game->IsKeyDown(DIK_RIGHT)) {
		simon->SetState(Simon_STATE_WALKING_RIGHT);
	}
	else if (game->IsKeyDown(DIK_LEFT))
	{
			simon->SetState(Simon_STATE_WALKING_LEFT);
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		simon->SetState(Simon_STATE_SIT);
	}
	else
	{
		simon->Set_Sit(false);
		simon->SetState(Simon_ANI_NORMAL_IDLE_RIGHT);
	}
}

void Map::OnKeyDown(int KeyCode)
{
	DebugOut(L"[INFO] KeyDown: %d\n", KeyCode);
	switch (KeyCode)
	{
	case DIK_SPACE:
		simon->SetState(Simon_STATE_JUMP);
		break;
	case DIK_X:
		simon->SetState(Simon_STATE_ATTACK);
		if (simon->Get_Sit() == true)
		{
			simon->SetState(Simon_STATE_SIT_ATTACK);
		}
		break;
	case DIK_A:
		simon->SetState(Simon_STATE_SUB_WEBPON);
		break;
	}
}

void Map::OnKeyUp(int KeyCode)
{
	DebugOut(L"[INFO] KeyUp: %d\n", KeyCode);

}


