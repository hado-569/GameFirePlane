#ifndef _BASE_OBJECT_H_
#define _BASE_OBJECT_H_

#include "Common_Fuc.h"


class BaseObject
{
public:
	BaseObject();
	~BaseObject();

	void Show(SDL_Surface* des);
	bool LoadIMG(const char * file_name);
	void SetRect(const int& x, const int& y) { rect_.x = x, rect_.y = y; };
	SDL_Rect getRect() const { return rect_; }
	SDL_Surface* getObject() { return p_object_; }

protected:
	SDL_Rect rect_;
	SDL_Surface* p_object_;
};




#endif // !_BASE_OBJECT_H_

