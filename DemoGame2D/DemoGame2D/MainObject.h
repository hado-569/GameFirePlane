#ifndef _MAIN_OBJECT_H_
#define _MAIN_OBJECT_H_

#include "BaseObject.h"
#include "Common_Fuc.h"
#include "AmoObject.h"
#include <vector>


#define WIDTH_PLAYER_IMAGE  75
#define HEIGHT_PLAYER_IMAGE  60

class PlayerObject : public BaseObject
{
public:
	PlayerObject();
	~PlayerObject();
	void HandleINPUTACTION(SDL_Event events);
	void HandleMOVE();
	void setAmoList(std::vector <AmoObject*> amo_list) { p_amo_list = amo_list; }
	std::vector<AmoObject*> getAmoList() const { return p_amo_list; }

	void MakeAmo(SDL_Surface* des);

	void RemoveAMO(const int& indx);

private:
	int x_val_;
	int y_val_;

	std::vector<AmoObject*> p_amo_list;
};


#endif // !_MAIN_OBJECT_H_

