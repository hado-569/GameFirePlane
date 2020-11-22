
#include "Common_Fuc.h";
#include "TextObject.h"

SDL_Surface* CommonFunctionSDL::LoadImage(std::string file_path)
{
	SDL_Surface* load_image = NULL;
	SDL_Surface* optimize_image = NULL;
	load_image = IMG_Load(file_path.c_str());
	if (load_image != NULL)
	{
		optimize_image = SDL_DisplayFormat(load_image);
		SDL_FreeSurface(load_image);
		if (optimize_image != NULL)
		{
			UINT32 color_key = SDL_MapRGB(optimize_image->format, 0xff, 0xff, 0xff);
			SDL_SetColorKey(optimize_image, SDL_SRCCOLORKEY, color_key);
		}
	}
	return optimize_image;
}

SDL_Rect CommonFunctionSDL::ApplySurface(SDL_Surface* src, SDL_Surface* des, int x, int y)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	SDL_BlitSurface(src, NULL, des, &offset);
    return offset;
}

void CommonFunctionSDL::ApplySurface2(SDL_Surface* src, SDL_Surface* des, SDL_Rect* clip, int x, int y)
{
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;
    SDL_BlitSurface(src, clip, des, &offset);

}



void CommonFunctionSDL::Cleanup()
{
	SDL_FreeSurface(g_screen);
	SDL_FreeSurface(g_bkground);
}

bool CommonFunctionSDL::CheckColision(const SDL_Rect& object1, const SDL_Rect& object2)
{
    int left_a = object1.x+25;
    int right_a = (object1.x + object1.w)*-1.5;
    int top_a = object1.y+25;
    int bottom_a = (object1.y + object1.h)-25;

    int left_b = object2.x;
    int right_b = object2.x + object2.w;
    int top_b = object2.y;
    int bottom_b = object2.y + object2.h;

    // Case 1: size object 1 < size object 2
    if (left_a > left_b && left_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (left_a > left_b && left_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (top_a > top_b && top_a < bottom_b)
        {
            return true;
        }
    }

    if (right_a > left_b && right_a < right_b)
    {
        if (bottom_a > top_b && bottom_a < bottom_b)
        {
            return true;
        }
    }

    // Case 2: size object 1 < size object 2
    if (left_b > left_a && left_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (left_b > left_a && left_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (top_b > top_a && top_b < bottom_a)
        {
            return true;
        }
    }

    if (right_b > left_a && right_b < right_a)
    {
        if (bottom_b > top_a && bottom_b < bottom_a)
        {
            return true;
        }
    }

    // Case 3: size object 1 = size object 2
    if (top_a == top_b && right_a == right_b && bottom_a == bottom_b)
    {
        return true;
    }

    return false;
}

int CommonFunctionSDL::ShowMenu(SDL_Surface* des, TTF_Font* font)
{
    g_img_menu = LoadImage("menuMain.jpg");
    if (g_img_menu==NULL)
    {
        return 1;

    }
   
    const int kMenuItemNUM = 2;
    SDL_Rect pos_arr[kMenuItemNUM];

    pos_arr[0].x = 200;
    pos_arr[0].y = 400;

    pos_arr[1].x = 200;
    pos_arr[1].y = 500;

    Text_Object textMenu[kMenuItemNUM];

    textMenu[0].SetText("Play Game");
    textMenu[0].SetColor(Text_Object::WHITE_TEXT);
    textMenu[0].SetRect(pos_arr[0].x,pos_arr[0].y);

    textMenu[1].SetText("Exit");
    textMenu[1].SetColor(Text_Object::WHITE_TEXT);
    textMenu[1].SetRect(pos_arr[1].x, pos_arr[1].y);

    bool selected[kMenuItemNUM] = { 0,0 };
    SDL_Event m_event;
    int xM;
    int yM;
    while (true)
    {
        CommonFunctionSDL::ApplySurface(g_img_menu,des,0 ,0);
        for (int i = 0; i < kMenuItemNUM; i++)
        {
            textMenu[i].CreateGameText(font,des);
        }
        
        while (SDL_PollEvent(&m_event))
        {

            switch (m_event.type)
            {
            case SDL_QUIT:
                return 1;
                break;
            case SDL_MOUSEMOTION:
            {
                xM = m_event.motion.x;
                yM = m_event.motion.y;

                for (int i = 0; i < kMenuItemNUM; i++)
                {
                    if (CheckForcusWithRect(xM, yM, textMenu[i].getRect()))
                    {
                        if (selected[i]==false)
                        {
                            selected[i] = 1;
                            textMenu[i].SetColor(Text_Object::RED_TEXT);
                        }
                    }
                    else
                    {

                        if (selected[i] == true)
                        {
                            selected[i] = 0;
                            textMenu[i].SetColor(Text_Object::WHITE_TEXT);
                        }
                    }
                }

            }            
                break;

            case SDL_MOUSEBUTTONDOWN:
            {
                xM = m_event.button.x;
                yM = m_event.button.y;
                for (int i = 0; i < kMenuItemNUM; i++)
                {
                    if (CheckForcusWithRect(xM, yM, textMenu[i].getRect()))
                    {
                        return i;

                    }                
                }
            }               
                break;
            case SDL_KEYDOWN:
                if (m_event.key.keysym.sym == SDLK_ESCAPE)
                {
                    return 1;
                }
               
                break;
            default:
                break;
            }
        }

     SDL_Flip(des);
    }

   
    return 1;
}

bool CommonFunctionSDL::CheckForcusWithRect(const int& x, const int& y, const SDL_Rect& rect)
{
    if (x >= rect.x && x <rect.x + rect.w && y >= rect.y && y <rect.y + rect.h)
    {
        return true;

    }
    return false;

}
