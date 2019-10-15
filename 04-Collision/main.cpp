/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 04 - COLLISION

	This sample illustrates how to:

		1/ Implement SweptAABB algorithm between moving objects
		2/ Implement a simple (yet effective) collision frame work

	Key functions: 
		CGame::SweptAABB
		CGameObject::SweptAABBEx
		CGameObject::CalcPotentialCollisions
		CGameObject::FilterCollision

		CGameObject::GetBoundingBox
		
================================================================ */

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "define.h"
#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"

#include "Mario.h"
#include "Brick.h"
#include "Goomba.h"

#include "Simon.h"
#include "TileMap.h"

#include "GroundObject.h"

#include "Map.h"

#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"04 - Collision"

#define BACKGROUND_COLOR D3DCOLOR_XRGB(255, 255, 200)
#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 240

#define MAX_FRAME_RATE 120

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20
#define ID_TEX_SIMON 30
#define ID_TEX_Bricks 40
#define ID_TEX_Objects 50
#define ID_MAP_SENCE1 1001

CGame *game;

CMario *mario;
CGoomba *goomba;
Simon *simon;
Ropes *rope;

TileMap *tilemap;

GroundObject *groundobject;

Map *rs;
vector<LPGAMEOBJECT> *objects;
//CKeyHander *keyHander;

class CSampleKeyHander: public CKeyEventHandler
{
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};

CSampleKeyHander * keyHandler; 

void CSampleKeyHander::OnKeyDown(int KeyCode)
{
	rs->OnKeyDown(KeyCode);
}

void CSampleKeyHander::OnKeyUp(int KeyCode)
{
	rs->OnKeyUp(KeyCode);
}

void CSampleKeyHander::KeyState(BYTE *states)
{
	rs->KeyState(states);
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object

	TO-DO: Improve this function by loading texture,sprite,animation,object from file
*/
//void LoadResources()
//{
//	CTextures * textures = CTextures::GetInstance();
//
//	textures->Add(ID_TEX_MARIO, L"textures\\mario.png",D3DCOLOR_XRGB(255, 255, 255));
//	textures->Add(ID_TEX_MISC, L"textures\\misc.png", D3DCOLOR_XRGB(176, 224, 248));
//	textures->Add(ID_TEX_ENEMY, L"textures\\enemies.png", D3DCOLOR_XRGB(3, 26, 110));
//	textures->Add(ID_TEX_SIMON, L"textures\\simon-belmont.png", D3DCOLOR_XRGB(255, 255, 255));
//	textures->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
//	textures->Add(ID_TEX_Bricks, L"textures\\Bricks.png", D3DCOLOR_XRGB(255, 255, 255));
//	textures->Add(ID_MAP_SENCE1, L"textures\\map1_outside_01_bank.png", D3DCOLOR_XRGB(255, 255, 255));
//	textures->Add(ID_TEX_Objects, L"textures\\objects.png", D3DCOLOR_XRGB(255, 0, 255));
//	CSprites * sprites = CSprites::GetInstance();
//	CAnimations * animations = CAnimations::GetInstance();
//	
//	LPDIRECT3DTEXTURE9 texMario = textures->Get(ID_TEX_MARIO);
//	LPDIRECT3DTEXTURE9 texSimon = textures->Get(ID_TEX_SIMON);
//	LPDIRECT3DTEXTURE9 texMap = textures->Get(ID_MAP_SENCE1);
//	LPDIRECT3DTEXTURE9 texObject = textures->Get(ID_TEX_Objects);
//	tilemap = new TileMap();
//	tilemap->LoadTileMap("textures\\map1_outside_01_map.tmx", texMap);
//	// big
//	//sprites->Add(10001, 246, 154, 260, 181, texMario);		// idle right
//
//	//sprites->Add(10002, 275, 154, 290, 181, texMario);		// walk
//	//sprites->Add(10003, 304, 154, 321, 181, texMario);
//
//	//sprites->Add(10011, 186, 154, 200, 181, texMario);		// idle left
//	//sprites->Add(10012, 155, 154, 170, 181, texMario);		// walk
//	//sprites->Add(10013, 125, 154, 140, 181, texMario);
//
//	//sprites->Add(10099, 215, 120, 231, 135, texMario);		// die 
//	//stand right
//	sprites->Add(10001, 152, 40, 192, 72, texSimon); //idle stand right	
//	sprites->Add(10002, 192, 40, 232, 72, texSimon);
//	sprites->Add(10003, 232, 40, 272, 72, texSimon);
//	//stand left
//	sprites->Add(10011, 112, 40, 152, 72, texSimon); //idle stand left
//	sprites->Add(10012, 72, 40, 112, 72, texSimon);
//	sprites->Add(10013, 32, 40, 72, 72, texSimon);
//	
//	//sit right
//	sprites->Add(10004, 273, 36, 311, 68, texSimon);
//	//sit left
//	sprites->Add(10005, -7, 36, 31, 68, texSimon);
//
//	//attack right
//	sprites->Add(10031, 156, 200, 196, 231,texSimon);
//	sprites->Add(10032, 192, 200, 232, 231, texSimon);
//	sprites->Add(10033, 229,199, 268, 231, texSimon);
//
//	//attack left
//	sprites->Add(10034, 109, 199, 146, 232, texSimon);
//	sprites->Add(10035, 73, 199, 100, 232, texSimon);
//	sprites->Add(10036, 36, 199, 73, 232, texSimon);
//
//	//attack sit right
//	sprites->Add(10041, 350 , 140, 387, 171, texSimon);
//	sprites->Add(10042, 384 , 140, 421, 171, texSimon);
//	sprites->Add(10043, 422 , 140, 459, 171, texSimon);
//
//	//attack sit left
//	sprites->Add(10046, 342, 185, 379, 216, texSimon);
//	sprites->Add(10045, 380, 185, 417, 216, texSimon);
//	sprites->Add(10044, 420, 185, 457, 216, texSimon);
//	// small
//	//sprites->Add(10021, 247, 0, 259, 15, texMario);			// idle small right
//	//sprites->Add(10022, 275, 0, 291, 15, texMario);			// walk 
//	//sprites->Add(10023, 306, 0, 320, 15, texMario);			// 
//
//	//sprites->Add(10031, 187, 0, 198, 15, texMario);			// idle small left
//
//	//sprites->Add(10032, 155, 0, 170, 15, texMario);			// walk
//	//sprites->Add(10033, 125, 0, 139, 15, texMario);			// 
//	
//	//Ropes 1 right
//	sprites->Add(10051, 339, 226, 400, 258, texSimon);
//	sprites->Add(10052, 406, 226, 466, 258, texSimon);
//	sprites->Add(10053, 452, 226, 513, 258, texSimon);
//
//	//Ropes 1 left
//	sprites->Add(10054, 651, 226, 713, 258, texSimon);
//	sprites->Add(10055, 586, 226, 646, 258, texSimon);
//	sprites->Add(10056, 540, 226, 601, 258, texSimon);
//
//	//Big Candles
//	sprites->Add(30001, 47, 23, 64, 56, texObject);
//	sprites->Add(30002, 74, 23, 91, 56, texObject);
//
//	LPDIRECT3DTEXTURE9 texMisc = textures->Get(ID_TEX_MISC);
//	sprites->Add(20001, 408, 225, 424, 241, texMisc);
//
//	LPDIRECT3DTEXTURE9 texEnemy = textures->Get(ID_TEX_ENEMY);
//	//sprites->Add(30001, 5, 14, 21, 29, texEnemy);
//	//sprites->Add(30002, 25, 14, 41, 29, texEnemy);
//
//	//sprites->Add(30003, 45, 21, 61, 29, texEnemy); // die sprite
//
//	LPANIMATION ani;
//
//	ani = new CAnimation(100);	// idle big right
//	ani->Add(10001);
//	animations->Add(400, ani);
//
//	ani = new CAnimation(100);	// idle big left
//	ani->Add(10011);
//	animations->Add(401, ani);
//
//	ani = new CAnimation(100);	// idle small right
//	ani->Add(10004);
//	animations->Add(402, ani);
//
//	ani = new CAnimation(100);	// idle small left
//	ani->Add(10005);
//	animations->Add(403, ani);
//
//	ani = new CAnimation(100);	// walk right big
//	ani->Add(10002);
//	ani->Add(10001);
//	ani->Add(10002);
//	ani->Add(10003);
//	animations->Add(500, ani);
//
//	ani = new CAnimation(100);	// // walk left big
//	ani->Add(10012);
//	ani->Add(10011);
//	ani->Add(10012);
//	ani->Add(10013);
//	animations->Add(501, ani);
//
//	ani = new CAnimation(150);	// attack right
//	ani->Add(10031);
//	ani->Add(10032);
//	ani->Add(10033);
//	animations->Add(502, ani);
//
//	ani = new CAnimation(150);	// attack \left
//	ani->Add(10034);
//	ani->Add(10035);
//	ani->Add(10036);
//	animations->Add(503, ani);
//
//	ani = new CAnimation(150);	// attack sit right
//	ani->Add(10041);
//	ani->Add(10042);
//	ani->Add(10043);
//	animations->Add(504, ani);
//
//	ani = new CAnimation(150);	// attack sit left
//	ani->Add(10044);
//	ani->Add(10045);
//	ani->Add(10046);
//	animations->Add(505, ani);
//
//	//ani = new CAnimation(100);	// walk left small
//	//ani->Add(10031);
//	//ani->Add(10032);
//	//ani->Add(10033);
//	//animations->Add(503, ani);
//	
//	ani = new CAnimation(100);		// Mario die
//	ani->Add(10099);
//	animations->Add(599, ani);
//
//	ani = new CAnimation(150); //Rope 1 right
//	ani->Add(10051);
//	ani->Add(10052);
//	ani->Add(10053);
//	animations->Add(511, ani);
//	
//	ani = new CAnimation(150); //Rope 1 left
//	ani->Add(10054);
//	ani->Add(10055);
//	ani->Add(10056);
//	animations->Add(512, ani);
//
//	ani = new CAnimation(100);		// brick
//	ani->Add(20001);
//	animations->Add(601, ani);
//
//	//ani = new CAnimation(300);		// Goomba walk
//	//ani->Add(30001);
//	//ani->Add(30002);
//	//animations->Add(701, ani);
//
//	//ani = new CAnimation(1000);		// Goomba dead
//	//ani->Add(30003);
//	//animations->Add(702, ani);
//
//	ani = new CAnimation(100);
//	ani->Add(30001);
//	ani->Add(30002);
//	animations->Add(701, ani);
//
//	simon = new Simon();
//	simon->AddAnimation(400);
//	simon->AddAnimation(401);
//	simon->AddAnimation(402);
//	simon->AddAnimation(403);
//	simon->AddAnimation(500);
//	simon->AddAnimation(501);
//	simon->AddAnimation(502);
//	simon->AddAnimation(503);
//	simon->AddAnimation(504);
//	simon->AddAnimation(505);
//	simon->SetPosition(50.0f, 0);
//	objects.push_back(simon);
//
//	rope = new Ropes();
//	rope->AddAnimation(511);
//	rope->AddAnimation(512);
//	objects.push_back(rope);
//
//	simon->GetRope(rope);
//	
//	groundobject = new GroundObject();
//	groundobject->AddAnimation(701);
//	groundobject->AddAnimation(701);
//	groundobject->SetNum(1);
//	groundobject->SetPosition(90, 160);
//	objects.push_back(groundobject);
//
//	/*for (int i = 0; i < 5; i++)
//	{
//		CBrick *brick = new CBrick();
//		brick->AddAnimation(601);
//		brick->SetPosition(100.0f + i*60.0f, 74.0f);
//		objects.push_back(brick);
//
//		brick = new CBrick();
//		brick->AddAnimation(601);
//		brick->SetPosition(100.0f + i*60.0f, 90.0f);
//		objects.push_back(brick);
//
//		brick = new CBrick();
//		brick->AddAnimation(601);
//		brick->SetPosition(84.0f + i*60.0f, 90.0f);
//		objects.push_back(brick);
//	}*/
//
//
//	for (int i = 0; i < 30; i++)
//	{
//		CBrick *brick = new CBrick();
//		brick->AddAnimation(601);
//		brick->SetPosition(0 + i*32.0f, 192);
//		objects.push_back(brick);
//	}
//
//	// and Goombas 
//	/*for (int i = 0; i < 4; i++)
//	{
//		goomba = new CGoomba();
//		goomba->AddAnimation(701);
//		goomba->AddAnimation(702);
//		goomba->SetPosition(200 + i*60, 135);
//		goomba->SetState(GOOMBA_STATE_WALKING);
//		objects.push_back(goomba);
//	}*/
//
//}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	// We know that Mario is the first object in the list hence we won't add him into the colliable object list
	// TO-DO: This is a "dirty" way, need a more organized way 

	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects->size(); i++)
	{
		coObjects.push_back(objects->at(i));
	}

	for (int i = 0; i < objects->size(); i++)
	{
		//objects->at(i)->Update(dt,&coObjects);
		objects->at(i)->Update(dt, objects);
	}

	for (int i = 0; i < objects->size(); i++)
	{
		if (objects->at(i)->GetState() == State_Dead && objects->at(i)->k>=30)
		{
			objects->erase(objects->begin() + i);
			i--;
		}
		if (objects->at(i)->GetState() == Item_hide)
		{
			objects->erase(objects->begin() + i);
			i--;
		}
	}


	// Update camera to follow mario
	float cx, cy;
	simon->GetPosition(cx, cy);
	cx -= (SCREEN_WIDTH / 2)-20;
	cy -= SCREEN_HEIGHT / 2;
	if (cx < 0)
	{
		cx = 0;
	}
	if (cx + SCREEN_WIDTH < 736)
	{
	
		CGame::GetInstance()->SetCamPos(cx, 0.0f /*cy*/);
	}
	else {
		CGame::GetInstance()->SetCamPos(736-SCREEN_WIDTH, 0.0f /*cy*/);
	}
	
}

/*
	Render a frame 
*/
void Render()
{
	LPDIRECT3DDEVICE9 d3ddv = game->GetDirect3DDevice();
	LPDIRECT3DSURFACE9 bb = game->GetBackBuffer();
	LPD3DXSPRITE spriteHandler = game->GetSpriteHandler();

	if (d3ddv->BeginScene())
	{
		 
		d3ddv->ColorFill(bb, NULL, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DXSPRITE_ALPHABLEND);
		tilemap->Render(0,40);
		for (int i = 0; i < objects->size(); i++)
			objects->at(i)->Render();

		spriteHandler->End();
		d3ddv->EndScene();
	}
	d3ddv->Present(NULL, NULL, NULL, NULL);
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, 
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd) 
	{
		OutputDebugString(L"[ERROR] CreateWindow failed");
		DWORD ErrCode = GetLastError();
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			game->ProcessKeyboard();
			
			Update(dt);
			Render();
		}
		else
			Sleep(tickPerFrame - dt);	
	}

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	game = CGame::GetInstance();
	game->Init(hWnd);

	keyHandler = new CSampleKeyHander();
	game->InitKeyboard(keyHandler);

	rs = new Map(1);
	simon = new Simon();
	objects = new vector<LPGAMEOBJECT>();
	tilemap = new TileMap();
	rs->SetVarible(simon, objects,tilemap);
	rs->LoadResource();
	//LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}