#ifndef _HEALTH_POINT_PLAYER_H_
#define _HEALTH_POINT_PLAYER_H_

#include "BaseObject.h"
#include <vector>


class HP_Player : public BaseObject
{
public:
	HP_Player();
	~HP_Player ();
	void SetNumber(const int& num) { number_ = num; };
	void Addpos(const int& x_pos);
	void Render(SDL_Surface* des);
	void Init();
	void Decrease();


private:
	int number_;
	std::vector<int> pos_list_;
};


#endif // !_HEALTH_POINT_PLAYER_H_

