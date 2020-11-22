#include "HP_Player.h"

HP_Player::HP_Player()
{

}

HP_Player::~HP_Player()
{
}

void HP_Player::Addpos(const int& x_pos)
{
	pos_list_.push_back(x_pos);
}

void HP_Player::Render(SDL_Surface* des)
{
	if (number_ == pos_list_.size())
	{
		for (int  i = 0; i < pos_list_.size(); i++)
		{
			rect_.x = pos_list_.at(i);
			Show(des);
		}

	}
}

void HP_Player::Init()
{
	LoadIMG("hp_player.png");
	number_ = 3;
	if (pos_list_.size()>0)
	{
		pos_list_.clear();
	}

	Addpos(20);
	Addpos(80);
	Addpos(140);
}

void HP_Player::Decrease()
{
	number_--;
	pos_list_.pop_back();

}
