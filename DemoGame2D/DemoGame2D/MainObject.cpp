#include "MainObject.h"
#include "AmoObject.h"

PlayerObject::PlayerObject()
{
	rect_.x = 0;
	rect_.y = 0;
	rect_.w = 0;
	rect_.h = 0;
	x_val_ = 0;
	y_val_ = 0;
}

PlayerObject::~PlayerObject()
{
	;
}

void PlayerObject::HandleINPUTACTION(SDL_Event events)
{
	if (events.type==SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
		
			y_val_-= HEIGHT_PLAYER_IMAGE/12;
			
			break;
		case SDLK_s:
			y_val_ += HEIGHT_PLAYER_IMAGE / 12;
			break;
		case SDLK_a:
			x_val_ -= WIDTH_PLAYER_IMAGE/12;
			break;
		case SDLK_d:

			x_val_ += WIDTH_PLAYER_IMAGE/12;

			break;
		/*case SDLK_SPACE:
			AmoObject* p_amo = new AmoObject();
			p_amo->SetWidthHeight(WIDTH_HADO, HEIGHT_HADO);
			p_amo->LoadIMG("hadouken.png");
			p_amo->set_type(AmoObject::HADOUKEN);

			p_amo->SetRect(this->rect_.x + this->rect_.w+10, this->rect_.y +this->rect_.h-5);
			p_amo->set_is_move(true);

			p_amo_list.push_back(p_amo);
			break;*/
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym)
		{
		case SDLK_w:
			
			y_val_+=HEIGHT_PLAYER_IMAGE/12;
			
		
			break;
		case SDLK_s:
			y_val_-=HEIGHT_PLAYER_IMAGE/12;
			break;
		case SDLK_a:
			x_val_ += WIDTH_PLAYER_IMAGE / 12;
			break;
		case SDLK_d:

			x_val_ -= WIDTH_PLAYER_IMAGE / 12;

			break;
		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN) {
		
		AmoObject* p_amo = new AmoObject();
		if (events.button.button==SDL_BUTTON_LEFT)
		{
			
			p_amo->SetWidthHeight(WIDTH_FIRELAZE,HEIGHT_FIRELAZE);
			p_amo->LoadIMG("fire.png");
			p_amo->set_type(AmoObject::FIRELAZE);
		}
		

		p_amo->SetRect(this->rect_.x + this->rect_.w ,(this->rect_.y + this->rect_.h)-40 );
		p_amo->set_is_move(true);
		p_amo->set_x_val_(4);
		p_amo_list.push_back(p_amo);

	}
	else if (events.type == SDL_MOUSEBUTTONUP) {

	}
	else
	{
		;
	}
	

}




void PlayerObject::HandleMOVE()
{
	rect_.x += x_val_;

	if (rect_.x<0 || rect_.x + WIDTH_PLAYER_IMAGE > SCREEN_WIDTH)
	{
		rect_.x -= x_val_;
	}

	rect_.y += y_val_;
	
	if (rect_.y <0 || rect_.y + HEIGHT_PLAYER_IMAGE > SCREEN_HEIGHT-285)
	{

		rect_.y -= y_val_;		
		//std::cout << rect_.y<<"\t"<<y_val_<<std::endl;
	}
	
	
}

void PlayerObject::MakeAmo(SDL_Surface* des)
{
	for (int i = 0; i < p_amo_list.size(); i++)
	{
		
		AmoObject* p_amo = p_amo_list.at(i);
		if (p_amo != NULL)
		{
			if (p_amo->get_is_move())
			{
				p_amo->Show(des);
				p_amo->HandleMOVE(SCREEN_WIDTH, SCREEN_HEIGHT);
			}
			else
			{
				if (p_amo != NULL)
				{
					p_amo_list.erase(p_amo_list.begin() + i);
					
					delete p_amo;
					p_amo = NULL;
				}
			}
		}
	}
}

void PlayerObject::RemoveAMO(const int& indx)
{
	for (int i = 0; i < p_amo_list.size(); i++)
	{
		if (indx<p_amo_list.size())
		{
			AmoObject* p_amo = p_amo_list.at(indx);
			p_amo_list.erase(p_amo_list.begin() + indx);
			if (p_amo != NULL)
			{
				delete p_amo;
				p_amo = NULL;
			}
		}
		
	}

}
