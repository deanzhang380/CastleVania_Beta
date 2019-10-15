#include "Simon.h"



Simon::Simon()
{
	

}


Simon::~Simon()
{
}

void Simon::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);
//	objects = coObjects;
	//is_jumping = true;
	// Simple fall down
	/*bool is_walking = false;
	if (is_attack == true)
	{
		vx = 0;
	}*/
	vy += Simon_GRAVITY * dt;
	//if (time_attack < 0) {
	//	time_attack += 120;
	//	//is_attack = true;
	//}//Thoi gian song khi danh
	//if (time_attack >= 0) {
	//	time_attack = 0;
	//	is_attack = false;
	//}
	if (time_jump < 0) {
		time_jump += 10;
	}
	if (time_jump >= 0) {
		time_jump = 0;
		is_jumping = false;
	}

	if (nx > 0)
	{
		if (is_sit == false)
		{
			ropes->SetPosition(x, y, 1);
		}
		if (is_sit == true)
		{
			ropes->SetPosition(x, y + 5, 1);
		}
	}
	if (nx < 0) {
		if (is_sit == false)
		{
			ropes->SetPosition(x, y, 0);
		}
		if (is_sit == true)
		{
			ropes->SetPosition(x, y + 5, 0);
		}
	}
	if (flag == 1)
	{
		coObjects->push_back(sw);
		flag = 0;
	}

	UpdateSubWeapon(dt, coObjects);
	/*if (sw != nullptr) {
		coObjects->push_back(sw);
	}*/
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	vector<LPGAMEOBJECT>* vector1 = new vector<LPGAMEOBJECT>;

	for (int i = 0; i < coObjects->size(); i++)
	{
		if (coObjects->at(i)->ID == 1)
			vector1->push_back(coObjects->at(i));
		if (coObjects->at(i)->ID == 3)
			vector1->push_back(coObjects->at(i));
	}
	// turn off collision when die 
	if (state != Simon_STATE_DIE)
		CalcPotentialCollisions(vector1, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > Simon_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	if (GetTickCount() - unmovable_start > Simon_UNMOVABLE_TIME)
	{
		unmovable_start = 0;
		unmovable = 0;
	}
	if (GetTickCount() - attack_start > 350) {
		
		attack_start = 0;
		is_attack = false;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		// Collision logic with Goombas
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<Item *>(e->obj)) {
				Item *item = dynamic_cast<Item *>(e->obj);
				if (e->nx != 0 || e->ny != 0) {
					if (item->state != Item_visible) {
						item->SetState(Item_hide);
						int a = item->GetNum();
						if (item->GetNum() == Item_ID_Rope) {
							ropes->SetLevel();
							StartUnmovable();
						}
						if (item->GetNum() == Item_ID_Dagger) {
							id_subwp = 0;
						}
					}
				}
			}

		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

	void Simon::Render()
	{
		int ani;
		if (state == Simon_STATE_DIE)
			ani = Simon_ANI_DIE;
		else if(is_sit==false || is_jumping == false)
		{
			if (nx > 0&&vx==0) ani = Simon_ANI_NORMAL_IDLE_RIGHT;
			if (nx > 0 && vx > 0) ani = Simon_ANI_NORMAL_WALKING_RIGHT;
			if (nx < 0 && vx == 0) ani =Simon_ANI_NORMAL_IDLE_LEFT;
			if (nx < 0 && vx < 0) ani = Simon_ANI_NORMAL_WALKING_LEFT;
			RenderBoundingBox(12,0);
		}
		 if (is_sit==true){
			if (nx >= 0)
			{
				ani = Simon_ANI_SIT_IDLE_RIGHT;
			}
			else
				ani = Simon_ANI_SIT_IDLE_LEFT;
			RenderBoundingBox(12, 0);
		}
		 if (vy <0) {
			if (nx >= 0)
			{
				ani = Simon_ANI_SIT_IDLE_RIGHT;
			}
			else
				ani = Simon_ANI_SIT_IDLE_LEFT;
			RenderBoundingBox(12, 0);
		}
		 if (is_attack == true && is_sit==false) {
			 if (nx > 0)
			 {
				 ani = Simon_ANI_ATTACK_RIGHT;
				 //ropes->SetPosition(x, y);
				 if (sub_attack == 0) {
					 ropes->SetAttack(true);
					 ropes->SetState(0);
				 }
				 if (sub_attack == 1) {
					 
					 flag = 1;
					 /*sw.at(0)->SetState(Item_appear);*/
					 sw->SetState(Item_appear);
					 sw->SetPosition(this->x, this->y);
					 
					// objects->push_back(sw);
				 }
			 }
			 else {
				 ani = Simon_ANI_ATTACK_LEFT;
				 if (sub_attack == 0) {
					 ropes->SetAttack(true);
					 ropes->SetState(0);
				 }
				 if (sub_attack == 1) {

					 flag = 1;
					 /*sw.at(0)->SetState(Item_appear);*/
					 sw->SetState(Item_appear);
					 sw->SetPosition(this->x, this->y);

					 // objects->push_back(sw);
				 }

			 }
			 RenderBoundingBox(12, 0);
		 }
		 if(is_attack == true && is_sit == true)
		 {
			 if (nx > 0)
			 {
				 ani = Simon_ANI_SIT_ATTACK_RIGHT;
				 if (sub_attack == 0) {
					 ropes->SetAttack(true);
					 ropes->SetState(0);
				 }
				 if (sub_attack == 1) {
					
					/* sw->SetState(Item_appear);*/
				 }
			 }
			 else {
				 ani = Simon_ANI_SIT_ATTACK_LEFT;
				 ropes->SetAttack(true);
				 ropes->SetState(1);
			 }
			 RenderBoundingBox(12, 0);
		 }
		int alpha = 255;
		if (untouchable) alpha = 128;
		animations[ani]->Render(x, y, alpha);	
}


void Simon::SetState(int state)
{
	CGameObject::SetState(state);

	if (unmovable == 1)
	{
		return;
	}
	switch (state)
	{
	case Simon_STATE_WALKING_RIGHT:
		if (unmovable==0) {
			vx = Simon_WALKING_SPEED;
		}
		nx = 1;
		break;
	case Simon_STATE_WALKING_LEFT:
		if (Can_Move() == true) {
			vx = -Simon_WALKING_SPEED;
		}
		nx = -1;
		break;
	case Simon_STATE_JUMP:
		if (is_jumping == false) {
			time_jump = -400; //thoi gian bay den tiep dat
			vy = -Simon_JUMP_SPEED_Y * 0.8f;//Gia toc cua nhay (vy cang nho nhay cang cao)
			is_jumping = true; //co hieu dau hieu dang nhay
		}
		break;
	case Simon_STATE_IDLE:
		vx = 0;
		break;
	case Simon_STATE_DIE:
		vy = -Simon_DIE_DEFLECT_SPEED;
		break;
	case Simon_STATE_SIT:
		vx = 0;
		is_sit = true;
		break;
	case Simon_STATE_ATTACK:
		
		if (is_attack == false ) {
			/*time_attack = -(100 * 30); *///set thoi gian song cua dong tac danh
			//is_attack = true; //co hieu trang thai tan cong
			StartAttack();
			vx = 0;
			vy = 0;
			StartUnmovable();
			sub_attack = 0;
		}
		break;
	case Simon_STATE_SIT_ATTACK:
		if (is_attack == false) {
			time_attack = -(100 * 30); //set thoi gian song cua dong tac danh
			is_attack = true; //co hieu trang thai tan cong
			vx = 0;
			vy = 0;
			StartUnmovable();
			sub_attack = 0;
		}
		break;
	case Simon_STATE_SUB_WEBPON:
		if (is_attack == false) {
			StartAttack();
			vx = 0;
			vy = 0;
			StartUnmovable();
			sub_attack = 1;
			ReturnSubWP();
		}
		break;
	}
}

void Simon::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	//rx = x + 12;
	
	left = x+12;
	top = y;
	/*if (is_sit == false)
	{
		right = x + 12 + Simon_BIG_BBOX_WIDTH;
		bottom = y + Simon_BIG_BBOX_HEIGHT;
	}

	if (is_sit == true)
	{
		right = x + 12 + Simon_SIT_BBOX_WIDTH;
		bottom = y + Simon_SIT_BBOX_HEIGHT;
	}*/
	
	right = x + 12 + Simon_BIG_BBOX_WIDTH;
	bottom = y + Simon_BIG_BBOX_HEIGHT;
	/*if (level == Simon_LEVEL_BIG)
	{
		right = x + Simon_BIG_BBOX_WIDTH;
		bottom = y + Simon_BIG_BBOX_HEIGHT;
	}
	else
	{
		right = x + Simon_SMALL_BBOX_WIDTH;
		bottom = y + Simon_SMALL_BBOX_HEIGHT;
	}*/
}

bool Simon::Can_Move()
{
	if (is_sit == true ||is_attack==true)
	{
		return false;
	}
	return true;
}

void Simon::ReturnSubWP()
{
	switch (id_subwp)
	{
	case 0:
		/*sw.push_back(new Dagger(this->x, this->y));*/
		sw = new Dagger(this->x, this->y,this->nx);
		
		break;
	default:
		break;
	}
	
}

void Simon::UpdateSubWeapon(DWORD dt, vector<LPGAMEOBJECT>* objects)
{
	/*for (auto iter : sw) {
		iter->Update(dt, objects);
		objects->push_back(iter);
	}*/
}
