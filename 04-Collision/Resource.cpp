#include "Resource.h"



Resource::Resource()
{
}


Resource::~Resource()
{
}

void Resource::LoadResourceSimon(string file)
{
	CTextures * textures = CTextures::GetInstance();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());
	textures->Add(stoi(doc.child("textures").attribute("ID").value()), L"textures\\simon-belmont.png", D3DCOLOR_XRGB(255, 255, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(stoi(doc.child("textures").attribute("ID").value()));

	for (auto ns : doc.child("textures").children("sprites"))
	{
		int a = stoi(ns.attribute("Sprites_ID").value());
		sprites->Add(stoi(ns.attribute("Sprites_ID").value()), stoi(ns.attribute("left").value()), stoi(ns.attribute("top").value()), stoi(ns.attribute("right").value()), stoi(ns.attribute("bottom").value()), texSimon);
	}
	LPANIMATION ani;
	for (auto animation : doc.child("Canimation").children("animations")) {
		ani = new CAnimation(stoi(animation.attribute("default_time").value()));
		for (auto a : animation.children("ani"))
		{
			ani->Add(stoi(a.attribute("ani_ID").value()));
		}
		animations->Add(stoi(animation.attribute("animations_Id").value()),ani);
		simon->AddAnimation(stoi(animation.attribute("animations_Id").value()));
	}	
	simon->SetPosition(20.0f, 100.0f);
	objects->push_back(simon);	
}

void Resource::LoadResourceRope(string file)
{
	CTextures * textures = CTextures::GetInstance();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());
	textures->Add(stoi(doc.child("textures").attribute("ID").value()), L"textures\\simon-belmont.png", D3DCOLOR_XRGB(255, 255, 255));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 texSimon = textures->Get(stoi(doc.child("textures").attribute("ID").value()));
	for (auto ns : doc.child("textures").children("sprites"))
	{
		int a = stoi(ns.attribute("Sprites_ID").value());
		sprites->Add(stoi(ns.attribute("Sprites_ID").value()), stoi(ns.attribute("left").value()), stoi(ns.attribute("top").value()), stoi(ns.attribute("right").value()), stoi(ns.attribute("bottom").value()), texSimon);
	}
	LPANIMATION ani;
	for (auto animation : doc.child("Canimation").children("animations")) {
		ani = new CAnimation(stoi(animation.attribute("default_time").value()));
		for (auto a : animation.children("ani"))
		{
			ani->Add(stoi(a.attribute("ani_ID").value()));
		}
		animations->Add(stoi(animation.attribute("animations_Id").value()), ani);
		ropes->AddAnimation(stoi(animation.attribute("animations_Id").value()));
	}
	objects->push_back(ropes);
	simon->GetRope(ropes);
}

void Resource::LoadResourceItem(string file)
{
	CTextures * textures = CTextures::GetInstance();
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(file.c_str());
	//int a = stoi(doc.child("textures").attribute("ID").value());
	textures->Add(stoi(doc.child("textures").attribute("ID").value()), L"textures\\items.png", D3DCOLOR_XRGB(128, 0, 0));
	CSprites * sprites = CSprites::GetInstance();
	CAnimations * animations = CAnimations::GetInstance();
	LPDIRECT3DTEXTURE9 tex= textures->Get(stoi(doc.child("textures").attribute("ID").value()));
	for (auto ns : doc.child("textures").children("sprites"))
	{
		int a = stoi(ns.attribute("Sprites_ID").value());
		sprites->Add(stoi(ns.attribute("Sprites_ID").value()), stoi(ns.attribute("left").value()), stoi(ns.attribute("top").value()), stoi(ns.attribute("right").value()), stoi(ns.attribute("bottom").value()), tex);
	}
	LPANIMATION ani;
	for (auto animation : doc.child("Canimation").children("animations")) {
		ani = new CAnimation(stoi(animation.attribute("default_time").value()));
		for (auto a : animation.children("ani"))
		{
			int b = stoi(a.attribute("ani_ID").value());
			ani->Add(stoi(a.attribute("ani_ID").value()));
		}
		int a = stoi(animation.attribute("animations_Id").value());
		animations->Add(stoi(animation.attribute("animations_Id").value()), ani);
		
		//item->AddAnimation(stoi(animation.attribute("animations_Id").value()));
	}
}
