//
//  event.c
//  Snake
//
//  Created by Thomas Foster on 8/2/18.
//  Copyright © 2018 Thomas Foster. All rights reserved.
//

#include "game.h"
#include "display.h"
#include "event.h"

bool keypressed = false;



void ProcessGameInput(SDL_Event *ev)
{
	snake_t *sn;
	
	if (keypressed) // only one key press allowed per cycle
		return;
	
	sn = &game.snake;
	switch (ev->key.keysym.sym) {
			
		case SDLK_UP:
			if (!sn->dy) {
				sn->dx = 0;
				sn->dy = -1;
				keypressed = true;
			}
			break;
			
		case SDLK_DOWN:
			if (!sn->dy) {
				sn->dx = 0;
				sn->dy = 1;
				keypressed = true;
			}
			break;
			
		case SDLK_LEFT:
			if (!sn->dx) {
				sn->dy = 0;
				sn->dx = -1;
				keypressed = true;
			}
			break;
			
		case SDLK_RIGHT:
			if (!sn->dx) {
				sn->dy = 0;
				sn->dx = 1;
				keypressed = true;
			}
			break;
		default:
			break;
	}
}


//
//  ProcessKeyDown
///	Handle everything by game state
//
bool ProcessKeyDown(SDL_Event *ev)
{
	if (ev->key.keysym.sym == SDLK_ESCAPE)
		return false;

	switch (game.state) {
						
		case ST_TITLESCREEN:
		case ST_LEVELSCREEN:
			game.state++;
			break;
			
			
		case ST_SKILLSCREEN:
			
			switch (ev->key.keysym.sym) {
				case SDLK_1: game.skill = SK_EASY; break;
				case SDLK_2: game.skill = SK_NORMAL; break;
				case SDLK_3: game.skill = SK_HARD; break ;
				default: break;
			}
			
			InitGame(true);
			LoadLevelScreen();
			game.state = ST_LEVELSCREEN;
			break;
			
			
		case ST_GAME:
			ProcessGameInput(ev);
			break;
			
			
		case ST_GAMEOVERSCREEN:
			switch (ev->key.keysym.sym) {
				case SDLK_y:
					ResetBlockMap();
					InitGame(true);
					LoadLevelScreen();
					game.state = ST_LEVELSCREEN;
					break;
				case SDLK_n:
					return false; // exit program
				default:
					break;
			}
			break;
			
		case ST_WIN:
			return false;
			
			
		default:
			break;
	}
	return true;
}


bool ProcessEvents(SDL_Event *ev)
{
	while (SDL_PollEvent(ev))
	{
		if (ev->type == SDL_QUIT)
			return false;
		
		if (ev->type == SDL_KEYDOWN)
			return ProcessKeyDown(ev);
	}
	return true;
}
