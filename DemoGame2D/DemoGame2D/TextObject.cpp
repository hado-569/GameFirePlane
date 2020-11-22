#include "TextObject.h"

Text_Object::Text_Object()
{
	rect_.x = 500;
	rect_.y = 10;
	text_color_.r =255;
	text_color_.g = 255;
	text_color_.b = 255;

}

Text_Object::~Text_Object()
{
}

void Text_Object::SetColor(const int& type)
{
	if (type== RED_TEXT)
	{
		SDL_Color color = { 225,0,0};
		text_color_ = color;

	}
	else if (type==WHITE_TEXT)
	{
		SDL_Color color = { 225,225,225 };
		text_color_ = color;
	}
	else
	{
		SDL_Color color = { 0,0,0 };
		text_color_ = color;
	}
}

void Text_Object::CreateGameText(TTF_Font* font_txt, SDL_Surface* des)
{
	p_object_ = TTF_RenderText_Solid(font_txt,str_val_.c_str(),text_color_);
	Show(des);
}
