#ifndef  _EXPLOSION_OBJECT_H_
#define  _EXPLOSION_OBJECT_H_

#include "BaseObject.h"
#include "Common_Fuc.h"

const int WIDTH_EXPLO = 233;
const int HEIGHT_EXPLO = 165;





class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();
	void set_Clip();
	void set_Frame(const int& fr) { frame_ = fr; };

	void ShowEXPLO(SDL_Surface* des);


private:
	int frame_;
	SDL_Rect clip[3];
};







#endif // ! _EXPLOSION_OBJECT_H_

