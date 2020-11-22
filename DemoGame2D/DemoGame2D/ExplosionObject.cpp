#include "ExplosionObject.h"

ExplosionObject::ExplosionObject()
{



}

ExplosionObject::~ExplosionObject()
{
}

void ExplosionObject::set_Clip()
{
	clip[0].x = 0;
	clip[0].y = 0;
	clip[0].w = WIDTH_EXPLO;
	clip[0].h = HEIGHT_EXPLO;

	clip[1].x = WIDTH_EXPLO;
	clip[1].y = 0;
	clip[1].w = WIDTH_EXPLO;
	clip[1].h = HEIGHT_EXPLO;

	clip[2].x = 2*WIDTH_EXPLO;
	clip[2].y = 0;
	clip[2].w = WIDTH_EXPLO;
	clip[2].h = HEIGHT_EXPLO;
}

void ExplosionObject::ShowEXPLO(SDL_Surface* des)
{
	if (frame_>3)
	{
		frame_ = 0;
	}

	CommonFunctionSDL::ApplySurface2(this->p_object_, des, &clip[frame_], rect_.x, rect_.y);

}
