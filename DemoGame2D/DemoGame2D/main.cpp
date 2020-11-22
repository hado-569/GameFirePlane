

#include "Common_Fuc.h"
#include "MainObject.h"
#include "ThreatsObject.h"
#include "ExplosionObject.h"
#include "HP_Player.h"
#include "TextObject.h"

#undef main



TTF_Font* g_font_text = NULL;

bool Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		return false;
	}
	g_screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (g_screen ==NULL)
	{
		return false;
	}

	if (TTF_Init()==-1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("VNI-Butlong.ttf",20);
	if (g_font_text==NULL)
	{
		return false;
	}

	return true;
}



int main(int arc,char* argv[])
{
	bool is_running_screen(true);
	int screen_x_val(0);
	bool is_quit = false;
	if (Init()==false)
	{
		return 0;

	}
	g_bkground = CommonFunctionSDL:: LoadImage("bkmap1.jpg");
	if (g_bkground==NULL)
	{
		return 0;
	}
	
	g_bkground2 = CommonFunctionSDL::LoadImage("lightBK.jpg");
	if (g_bkground == NULL)
	{
		return 0;
	}

	g_bkground3 = CommonFunctionSDL::LoadImage("bkground.jpg");
	if (g_bkground == NULL)
	{
		return 0;
	}




	//player
	PlayerObject player_object;
	player_object.SetRect(160,350);
	bool ret = player_object.LoadIMG("hero.png");
	if (!ret)
	{
		return 0;
	}

	//HP player
	HP_Player hp_player;
	hp_player.Init();

	//text - load
	Text_Object score_game;
	score_game.SetColor(Text_Object::WHITE_TEXT);

	//explosion - load frame
	ExplosionObject main_explo;
	ret = main_explo.LoadIMG("explode_2.png");
	main_explo.set_Clip();
	if (!ret)
	{
		return 0;
	}



	//threats - declare
	ThreatObject* p_threats = new ThreatObject[NUM_THREATS];
	for (int threats = 0; threats < NUM_THREATS; threats++)
	{

		ThreatObject* p_threat_object = (p_threats+threats);

		if (p_threat_object)
		{
			int rand_x_val = rand() % 15;
			p_threat_object->set_x_val(rand_x_val);

			int rand_y = rand() % 400 + 1;
			if (rand_y > SCREEN_HEIGHT + 50)
			{
				rand_y = SCREEN_HEIGHT * 0.5;
			}


			ret = p_threat_object->LoadIMG("enemy1.png");
			p_threat_object->SetRect(SCREEN_WIDTH + threats * 400, rand_y);
			if (ret == false)
			{
				return 0;
			}

			AmoObject* p_amo = new AmoObject;
			p_threat_object->InnitAmo(p_amo);
		}
		
	}
	
	//show - check Menu
	int ret_menu = CommonFunctionSDL::ShowMenu(g_screen,g_font_text);
	if (ret_menu==1)
	{
		is_quit = true;
	}


	unsigned int count_die = 0;
	unsigned int score_val = 0;

	//loop show object
	while (!is_quit)
	{
		while (SDL_PollEvent(&g_event))
		{
			if (g_event.type== SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			player_object.HandleINPUTACTION(g_event);
		}



		//show - background
		
		/* "loop one background " screen_x_val -= 2;
		CommonFunctionSDL::ApplySurface(g_bkground, g_screen, screen_x_val, 0);
		CommonFunctionSDL::ApplySurface(g_bkground, g_screen, screen_x_val+SCREEN_WIDTH+5, 0);

		if (screen_x_val <= - SCREEN_WIDTH)
		{
			screen_x_val = 0;
		}*/
		
		//show 1 session background
		if (is_running_screen==true)
		{
			screen_x_val -= 2;
			if (screen_x_val<= -(BKG_WIDTH-SCREEN_WIDTH))
			{
				is_running_screen = false;
			}
			else {
				CommonFunctionSDL::ApplySurface(g_bkground, g_screen, screen_x_val, 0);
			}
		}
		else
		{
			CommonFunctionSDL::ApplySurface(g_bkground, g_screen, screen_x_val, 0);
		}
	
		

		
		//show- player
		player_object.HandleMOVE();
		player_object.Show(g_screen);
		
		//player- HP
		hp_player.Render(g_screen);




		//loop [set- running amo bullet]
		player_object.MakeAmo(g_screen);


		//loop show - running threats
		for (int thre = 0; thre < NUM_THREATS; thre++)
		{
			ThreatObject* p_threat_object = (p_threats + thre);
			if (p_threat_object)
			{
				p_threat_object->HandleMOVE(SCREEN_WIDTH, SCREEN_HEIGHT);
				p_threat_object->Show(g_screen);			
				p_threat_object->MakeAmo(g_screen, SCREEN_WIDTH, SCREEN_HEIGHT);
			}


			if (SDL_Flip(g_screen) == -1)
			{
				return 0;
			}

			//check colision player - threats _ player - bullet_threats

			std::vector<AmoObject*> amo_list_thre = p_threat_object->get_amo_list();
			for (int  thre_bullet = 0; thre_bullet < amo_list_thre.size(); thre_bullet++)
			{
				AmoObject* ammo = amo_list_thre.at(thre_bullet);
				if (ammo!=NULL)
				{
					bool is_coli_player_bullet = CommonFunctionSDL::CheckColision(player_object.getRect(), ammo->getRect());
					bool is_coli = CommonFunctionSDL::CheckColision(player_object.getRect(), p_threat_object->getRect());

					if (is_coli_player_bullet||is_coli)
					{
						for (int ex = 0; ex < 3; ex++)
						{
						    int x_pos = (player_object.getRect().x + player_object.getRect().w * 0.2) - WIDTH_EXPLO * 0.2;
							int y_pos = (player_object.getRect().y + player_object.getRect().h * 0.5) - HEIGHT_EXPLO * 0.5;

							main_explo.set_Frame(ex);
							main_explo.SetRect(x_pos, y_pos);
							main_explo.ShowEXPLO(g_screen);

							SDL_Delay(250);

							if (SDL_Flip(g_screen) == -1)
							{
								return 0;
							}
						}

						



								count_die++;
						
								if (count_die <= 2)
								{

									SDL_Delay(1000);
									player_object.SetRect(160, 350);
									hp_player.Decrease();
									hp_player.Render(g_screen);
									p_threat_object->Reset(SCREEN_WIDTH + thre * 400);

									

									if (SDL_Flip(g_screen) == -1)
									{
										delete[] p_threats;
										CommonFunctionSDL::Cleanup();
										SDL_Quit();
										return 0;
									}
								}
								else
								{
									int ret_menu = CommonFunctionSDL::ShowMenu(g_screen, g_font_text);
									if (ret_menu == 1)
									{

										is_quit = true;

									}
									/*if (MessageBox(NULL, L"You Die !", L"Warning", MB_OK) == IDOK)
									{
										delete[] p_threats;
										CommonFunctionSDL::Cleanup();
										SDL_Quit();
										return 0;
									}*/
								}
								
					}

				}

			}

			//check bullet-by-player fire on threats 
			std::vector<AmoObject*> amo_list = player_object.getAmoList();

			for (int  amo = 0; amo< amo_list.size(); amo++)
			{
				AmoObject* p_amo = amo_list.at(amo);
				if (p_amo!= NULL)
				{

					bool ret_coli= CommonFunctionSDL::CheckColision(p_amo->getRect(), p_threat_object->getRect());
					if (ret_coli)
					{
						for (int ex = 0; ex < 3; ex++)
						{
							int x_pos = (p_threat_object->getRect().x + p_threat_object->getRect().w * 0.2) - WIDTH_EXPLO * 0.2;
							int y_pos = (p_threat_object->getRect().y + p_threat_object->getRect().h * 0.5) - HEIGHT_EXPLO * 0.5;

							main_explo.set_Frame(ex);
							main_explo.SetRect(x_pos, y_pos);
							main_explo.ShowEXPLO(g_screen);
							SDL_Delay(5);
							

							if (SDL_Flip(g_screen) == -1)
							{
								return 0;
							}
						}
						score_val++;

						p_threat_object->Reset(SCREEN_WIDTH + thre * 400);
						player_object.RemoveAMO(amo);
					}
				}
			}		
		}
		
		//show score 
		std::string val_str_score = std::to_string(score_val);
		std::string strScore("Score : ");
		strScore += val_str_score;

		score_game.SetText(strScore);
		score_game.CreateGameText(g_font_text, g_screen);


		if (SDL_Flip(g_screen)==-1)
		{
			return 0;
		}
	}

	


	delete[] p_threats;
	CommonFunctionSDL::Cleanup();
	SDL_Quit();
	return 0;
	
}

