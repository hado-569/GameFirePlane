#ifndef _AMO_OBJECT_H_
#define _AMO_OBJECT_H_

#include "BaseObject.h"


#define WIDTH_HADO  50
#define HEIGHT_HADO 50

#define WIDTH_FIRELAZE 32
#define HEIGHT_FIRELAZE 35

#define WIDTH_BULLETENEMY 75
#define HEIGHT_BULLETENEMY 35

class AmoObject :public BaseObject
{

public:
	enum AmoType {
		NONE,
		HADOUKEN,
		FIRELAZE,
		BULLETENEMY
	};

	AmoObject();
	~AmoObject();

	void HandleINPUTACTION(SDL_Event events);
	void HandleMOVE(const int x_border,const int y_border);
	void HandleMOVERightToLeft(const int& y_limit);


	int get_type() const { return amo_type; }
	void set_type(const int& type) { amo_type = type; };

	bool get_is_move() const { return is_move; }
	void set_is_move(bool ismove) {  is_move = ismove; }

	void SetWidthHeight(const int& width, const int& height) { rect_.x = width; rect_.y = height; }

	void set_x_val_(const int& val) { x_val_ = val; }
	void set_y_val_(const int& val) { y_val_ = val; }

	int get_x_val()const { return x_val_; }
	int get_y_val()const { return y_val_; }
private:

	int x_val_;
	int y_val_;
	bool is_move;
	int amo_type;

};


#endif // !_AMO_OBJECT_H_

