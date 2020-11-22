#include "ThreatsObject.h"

ThreatObject::ThreatObject()
{
	rect_.x = SCREEN_WIDTH;
	rect_.y = SCREEN_HEIGHT * 0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;

	x_val = 0;
	y_val = 0;


}


ThreatObject::~ThreatObject()
{

	if (amo_list_.size()>0)
	{
		for (int i = 0; i < amo_list_.size(); i++)
		{
			AmoObject* p_amo_ = amo_list_.at(i);
			if (p_amo_!=NULL)
			{
				delete p_amo_;
				p_amo_ = NULL;
			}
		}
		amo_list_.clear();
	}

}






void ThreatObject::HandleINPUTACTION(SDL_Event events)
{
}

void ThreatObject::HandleMOVE(const int& x_border, const int& y_border)
{
	rect_.x -= x_val;
	if (rect_.x<0)
	{
		rect_.x = SCREEN_WIDTH;
		int rand_y = rand() % 400;
		if (rand_y>SCREEN_HEIGHT-200)
		{
			rand_y = SCREEN_HEIGHT*0.5;
		}
		rect_.y = rand_y;

	}
}

void ThreatObject::InnitAmo(AmoObject* p_amo)
{
	if (p_amo)
	{
		bool ret = p_amo->LoadIMG("bulletEnemy.png");
		if (ret)
		{
			p_amo->set_is_move(true);
			p_amo->SetWidthHeight(WIDTH_BULLETENEMY,HEIGHT_BULLETENEMY);
			p_amo->SetRect(rect_.x-10,rect_.y+rect_.h*0.3);
			p_amo->set_type(AmoObject::BULLETENEMY);
			p_amo->set_x_val_(12);
			amo_list_.push_back(p_amo);
		}
	}

}

void ThreatObject::MakeAmo(SDL_Surface* des, const int& x_limit, const int& y_limit)
{
	for (int  i = 0; i < amo_list_.size(); i++)
	{
		AmoObject* p_amo = amo_list_.at(i);
		if (p_amo->get_is_move())
		{
			if (this->rect_.x<x_limit) {
				p_amo->Show(des);
				p_amo->HandleMOVERightToLeft(y_limit);
			}
		}
		else
		{
			p_amo->set_is_move(true);
			p_amo->SetRect(rect_.x-20,rect_.y+rect_.h*0.3);
		}
	}
	

	
}

void ThreatObject::Reset(const int& x_border)
{
	rect_.x = x_border;
	int rand_y = rand() % 400;
	if (rand_y > SCREEN_HEIGHT - 200)
	{
		rand_y = SCREEN_HEIGHT * 0.5;
	}
	rect_.y = rand_y;

	for (int  i = 0; i < amo_list_.size(); i++)
	{
		AmoObject* pAMO = amo_list_.at(i);
		if (pAMO)
		{
			ResetAMO(pAMO);
		}
	}
}

void ThreatObject::ResetAMO(AmoObject* p_amo)
{
	p_amo->SetRect(rect_.x - 10, rect_.y + rect_.h * 0.3);
}
