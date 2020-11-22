#include "AmoObject.h"

AmoObject::AmoObject()
{
	x_val_ = 0;
	y_val_ = 0;
	rect_.x = 0;
	rect_.y = 0;

	is_move = false;
	amo_type = NONE;

}

AmoObject::~AmoObject()
{
}

void AmoObject::HandleINPUTACTION(SDL_Event events)
{
}

void AmoObject::HandleMOVE(const int x_border, const int y_border)
{
	rect_.x += x_val_;

	if (rect_.x>x_border)
	{
		is_move = false;
	}
}

void AmoObject::HandleMOVERightToLeft(const int& y_limit)
{
	rect_.x -= x_val_;
	if (rect_.x<0)
	{
		is_move = false;
	}
}
