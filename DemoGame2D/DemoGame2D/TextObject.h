#ifndef _TEXT_OBJECT_H_
#define _TEXT_OBJECT_H_

#include "BaseObject.h"
#include <string>
#include <SDL_ttf.h>

class Text_Object : public BaseObject
{
public:
	Text_Object();
	~Text_Object();
	enum TEXTCOLOR {
		RED_TEXT,
		WHITE_TEXT,
		BLACK_TEXT
	};

	void SetText(const std::string& txt) {str_val_ = txt; };
	void SetColor(const int& type);
	void CreateGameText(TTF_Font* font_txt, SDL_Surface* des );

private:

	std::string str_val_;
	SDL_Color text_color_;

};




#endif // !_TEXT_OBJECT_H_
