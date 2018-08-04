//
//  gameloop.c
//  Snake
//
//  Created by Thomas Foster on 7/28/18.
//  Copyright © 2018 Thomas Foster. All rights reserved.
//
//	Game Logic and Main Loop

#include "sdl.h"
#include "gamemain.h"
#include "game.h"
#include "display.h"
#include "event.h"

#define DRAWFRAME	333



//
//	ProcessGame
//
void ProcessGame (void)
{
	int i;
	int mapx, mapy;
	snake_t *sn;
	//	snakeseg_t	*segs;

	
	// PLAY SOUND IF LEVEL COMPLETE OR DEAD
	if (game.eventtime && game.ticks == game.eventtime + 1500) {
		if (game.snake.state == dead) {
			Mix_PlayChannel(-1, sounds.disappear, 0);
		} else {
			Mix_PlayChannel(-1, sounds.energy, 0);
		}
	}
	
	// only processed if in game and every .3 second
	// no processing during death or level complete event
	if (game.state != ST_GAME || game.ticks % DRAWFRAME != 0 || game.eventtime) {
		return; // only process every 0.5 seconds etc
	}
	
	// ===============================

	keypressed = false;
	
	// MOVE SNAKE
	sn = &game.snake;
	if (sn->state == sleeping && (sn->dx || sn->dy))
		sn->state = active; // wake up!
	
	sn->lastpt = sn->origin;  // set the last position so the next seg knows it
	sn->origin.y += sn->dy*TILESIZE;  // move the snake by 1 tile
	sn->origin.x += sn->dx*TILESIZE;
	
	mapx = sn->origin.x / TILESIZE;	// for checking the blockmap
	mapy = sn->origin.y / TILESIZE; // "
	
	for (i=0; i<2; i++) {	// teleport!
		if (TFPointsAreEqual(&sn->origin, &game.portals[i].location)) {
			sn->origin = game.portals[i].linkedpt;
			Mix_PlayChannel(-1, sounds.teleport, 0);
			break;
		}
	}
	
	
	// SET HEAD ANGLE
	if (game.snake.dy == -1)
		sn->headangle = 0;
	else if (game.snake.dy == 1)
		sn->headangle = 180;
	else if (game.snake.dx == -1)
		sn->headangle = -90;
	else if (game.snake.dx == 1)
		sn->headangle = 90;
	
	
	// CHECK FOR A BLOCK
	if (blockdata[mapy][mapx] == MAP_BLOCK)
	{
		sn->state = dead;
		game.eventtime = game.ticks;
		Mix_PlayChannel(-1, sounds.dead, 0);
	}
	
	
	// CHECK FOR AN APPLE
	if (blockdata[mapy][mapx] == MAP_APPLE)
	{
		game.applesleft--;	// nom
		blockdata[mapy][mapx] = MAP_EMPTY;
		
		sn->numsegs++;	// grow
		// set new seg to prior seg pos
		sn->segs[sn->numsegs-1].lastpt = sn->segs[sn->numsegs-2].origin;
		sn->segs[sn->numsegs-1].origin = sn->segs[sn->numsegs-2].origin;
		
		if (game.applesleft == 0) {
			Mix_PlayChannel(-1, sounds.win, 0);
			game.eventtime = game.ticks; // start lvl compl event
		} else {
			Mix_PlayChannel(-1, sounds.pickup, 0);
		}
	}
	
	// CHECK IF HIT TAIL
	if (game.snake.state == active) // snake starts wrapped up
	{
		for (i=0; i<sn->numsegs; i++)
			if (TFPointsAreEqual(&sn->origin, &sn->segs[i].origin)) {
				sn->state = dead;
				game.eventtime = game.ticks;
				Mix_PlayChannel(-1, sounds.dead, 0);
			}
	}
	sn->segs[0].lastpt = sn->segs[0].origin;
	sn->segs[0].origin = sn->lastpt;
	
	// set each seg to the position of the prior one
	for (i=1; i<sn->numsegs; i++) {
		sn->segs[i].lastpt = sn->segs[i].origin;
		sn->segs[i].origin = sn->segs[i-1].lastpt;
	}
}



//
//	GameMain
///	Inits/frees game and assetts, starts game loop.
//
void GameMain (void)
{
	SDL_Event 	ev;
	
	LoadScreens();
	
	printf("Initializing game...\n");
	
	game.state = ST_TITLESCREEN; // TODO check order of init
	game.ticks = 0;
	
	LoadGameAssetts();
	
	// GAME LOOP
	while (1)
	{
		game.ticks++;
		
		if (!ProcessEvents(&ev))
			break;
		
		ProcessGame();
		Display();
	}
	
	printf("Quiting...\n");
	FreeGameAssetts();
	FreeScreens();
}
