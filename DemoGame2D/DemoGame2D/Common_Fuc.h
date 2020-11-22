#ifndef _COMMON_FUNC_H_
#define _COMMON_FUNC_H_

#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <SDL_ttf.h>


const int BKG_WIDTH(4000);
const int BKG_HEIGHT(702);

const int SCREEN_WIDTH(1000);
const int SCREEN_HEIGHT(702);
const int SCREEN_BPP(32);

const int NUM_THREATS =2;

static  SDL_Surface* g_screen = NULL;
static	SDL_Surface* g_bkground = NULL;
static SDL_Surface* g_bkground2 = NULL;
static SDL_Surface* g_bkground3 = NULL;
static SDL_Surface* g_img_menu = NULL;

/*SDL_Surface* g_playerImage = NULL;*/
static  SDL_Event g_event;

namespace CommonFunctionSDL {

	

	SDL_Surface* LoadImage(std::string file_path);
	SDL_Rect ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y);
	void ApplySurface2(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x ,int y);
	void Cleanup();
	bool CheckColision(const SDL_Rect& object1, const SDL_Rect& object2);

	int ShowMenu(SDL_Surface* des, TTF_Font* font);
	bool CheckForcusWithRect(const int& x, const int& y, const SDL_Rect& rect);

}

#endif // !_COMMON_FUNC_H_

