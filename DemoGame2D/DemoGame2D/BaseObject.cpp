
#include "BaseObject.h"

BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_object_ = NULL;

}

BaseObject::~BaseObject()
{
	if (p_object_!=NULL)
	{
		SDL_FreeSurface(p_object_);
	}
}

void BaseObject::Show(SDL_Surface* des)
{
	if (p_object_!=NULL)
	{
		rect_ = CommonFunctionSDL::ApplySurface(p_object_,des, rect_.x,rect_.y);
	}
}

bool BaseObject::LoadIMG(const char* file_name)
{
	p_object_ = CommonFunctionSDL::LoadImageW(file_name);

	if (p_object_==NULL)
	{
		return false;
	}
	return true;
}
