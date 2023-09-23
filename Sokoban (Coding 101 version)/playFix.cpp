#include "sokoban.h"
#include "audio_with_SDLMixer.h"

void playFix(SDL_Surface *screen, int level)
{
	printf("playFix, %d\n", level);
	// Show manual
	// maunal()
Initial:
	SDL_Surface *player1[4];
	SDL_Surface *block;
	SDL_Surface *box;
	SDL_Surface *boxOK;
	SDL_Surface *playerCurrent;
	SDL_Surface *goal;
	SDL_Rect p;
	SDL_Rect p_J;
	SDL_Event event;
	bool pass = true;
	int obj_rest = 0;
	int i, j;
	int map[N_HEIGHT][N_WIDTH];

	block = IMG_Load("src/sprites/wall_50.jpg");
	box = IMG_Load("src/sprites/box_50.jpg");
	boxOK = IMG_Load("src/sprites/box_ok.jpg");
	goal = IMG_Load("src/sprites/goal.png");

	// player1[UP] = IMG_Load("sprites/mario_haut.gif");
	// player1[DOWN] = IMG_Load("sprites/mario_bas.gif");
	// player1[LEFT] = IMG_Load("sprites/mario_gauche.gif");
	// player1[RIGHT] = IMG_Load("sprites/mario_droite.gif");

	// Anya (image size need to be modified)
	player1[UP] = IMG_Load("src/sprites/up.png");
	player1[DOWN] = IMG_Load("src/sprites/down.png");
	player1[LEFT] = IMG_Load("src/sprites/left.png");
	player1[RIGHT] = IMG_Load("src/sprites/right.png");
	// player1[UP] = IMG_Load("rsc/sprites/anya_up.png");
	// player1[DOWN] = IMG_Load("rsc/sprites/anya_down.png");
	// player1[LEFT] = IMG_Load("rsc/sprites/anya_left.png");
	// player1[RIGHT] = IMG_Load("rsc/sprites/anya_right.png");

	playerCurrent = player1[DOWN];

	if (!load_fix_lvl(map, level))
		exit(EXIT_FAILURE);

	for (i = 0; i < N_HEIGHT; i++)
	{
		for (j = 0; j < N_WIDTH; j++)
		{
			if (map[i][j] == ROLE)
			{
				p_J.y = i;
				p_J.x = j;
				map[i][j] = 0; // NONE改為0
				break;
			}
		}
	}
	SDL_EnableKeyRepeat(200, 50); // 鍵盤靈敏度
	while (pass)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			pass = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				pass = 0;
				break;
			case SDLK_UP:
				playerCurrent = player1[UP];
				move_player(map, &p_J, UP);
				break;
			case SDLK_DOWN:
				playerCurrent = player1[DOWN];
				move_player(map, &p_J, DOWN);
				break;
			case SDLK_RIGHT:
				playerCurrent = player1[RIGHT];
				move_player(map, &p_J, RIGHT);
				break;
			case SDLK_LEFT:
				playerCurrent = player1[LEFT];
				move_player(map, &p_J, LEFT);
				break;
			case SDLK_r: // Reset
				goto Initial;
				break;
			default:	
				break;
			}
			break;
		}

		SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
		obj_rest = 0;
		for (i = 0; i < N_HEIGHT; i++)
		{
			for (j = 0; j < N_WIDTH; j++)
			{
				p.y = i * BOX_SIZE;
				p.x = j * BOX_SIZE;
				switch (map[i][j])
				{
				case WALL:
					SDL_BlitSurface(block, nullptr, screen, &p);
					break;
				case BOX:
					SDL_BlitSurface(box, nullptr, screen, &p);
					break;
				case BOX_OK:
					SDL_BlitSurface(boxOK, nullptr, screen, &p);
					break;
				case GOAL:
					SDL_BlitSurface(goal, nullptr, screen, &p);
					obj_rest = 1;
					break;
				}
			}
		}
		if (!obj_rest)
		{
			pass = false;
			// show end game interface
			// endGame()
		}
		p.x = p_J.x * BOX_SIZE;
		p.y = p_J.y * BOX_SIZE;
		SDL_BlitSurface(playerCurrent, nullptr, screen, &p);
		SDL_Flip(screen);
		// SDL_blit(screen);
	}
	SDL_EnableKeyRepeat(0, 0);
	SDL_FreeSurface(block);
	SDL_FreeSurface(box);
	SDL_FreeSurface(boxOK);
	SDL_FreeSurface(goal);
	i = -1;
	while (++i < 4)
		SDL_FreeSurface(player1[i]);
	// 遊戲結束後看要改成 next level 或是結束遊戲
	while (true)
	{
		SDL_WaitEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			pass = 0;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				pass = 0;
				break;
			case SDLK_1:
			case SDLK_KP1:
				level = 1;
				playFix(screen, 1);
				break;
			// 按 2 切換到第二關
			case SDLK_2:
			case SDLK_KP2:
				level = 2;
				playFix(screen, 2);
				break;
			}
			break;
		}
		break;
	}

}
