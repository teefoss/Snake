//
//  game.c
//  Snake
//
//  Created by Thomas Foster on 7/28/18.
//  Copyright © 2018 Thomas Foster. All rights reserved.
//
//	Game Logic

#include <stdlib.h>
#include <time.h>
#include "sdl.h"
#include "game.h"

//#define ONEAPPLE		// !! for testing, comment this out
#define STARTLEVEL 0	// !! for testing, set back to 0

#define NUMSEGS				3		// how many segs the snake starts with
#define APPLES_PER_LEVEL	1

game_t 			game;
gametextures_t	texs;
gamesounds_t	sounds;

sizetype tilesize;

// the "easy" way to make a level
// now includes more than block data!
byte blockdata[30][40] = {
//	 1             8               16              24              32              40
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 1
	{1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,1},
	{1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,0,1},
	{1,0,0,0,0,0,1,3,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1},
	{1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,1},
	{1,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1}, // 8
	{1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,1},
	{1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,1},
	{1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,1,1,0,0,4,0,0,1,1,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1}, // 16
	{1,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
	{1,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1},
	{1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,1}, // 24
	{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1},
	{1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}, // 30
};




//
//	ClearBlockMap
///	Clear all the apples off the blockmap
/// Call when GO and restarting.
//
void ResetBlockMap (void)
{
	int y,x;
	
	for (y=0; y<30; y++)
		for (x=0; x<40; x++)
			if (blockdata[y][x] == MAP_APPLE)
				blockdata[y][x] = MAP_EMPTY;
}

SDL_Color snakecolors[SN_NUMCOLORS] = {
	{ 0, 249, 0, 255 },		// green
	{ 170, 121, 66, 255 },	// brown
	{ 255, 147, 0 ,255 },	// orange
	{ 255, 251, 0, 255 },	// yellow
	{ 4, 51, 255, 255 },	// blue
	{ 0, 253, 155, 255 },	// cyan
	{ 148, 33, 146, 255 },	// purple
	{ 255, 64, 255, 255 },	// magenta
	{ 255, 255, 255, 255 },	// white
};



//
//	SnakeRect & DeadSnakeRect
///	Get the source rect from the sprite sheet
///	Use BODY or HEAD
//
SDL_Rect SnakeRect(bool body, snakecolors_e color)
{
	SDL_Rect r = { color*8, body*8, 8, 8 };
	return r;
}

SDL_Rect DeadSnakeRect(bool body)
{
	SDL_Rect r = { 0, body*8, 8, 8 };
	return r;
}




void LoadGameAssetts (void)
{
	tilesize = MakeSize(TILESIZE, TILESIZE);
	
	// LOAD TEXTURES
	texs.snake = LoadSDLTexture("snake.png");
	texs.snakedead = LoadSDLTexture("snakedead.png");
	texs.block = LoadSDLTexture("block.png");
	texs.apple = LoadSDLTexture("apple.png");
	texs.portal[0] = LoadSDLTexture("portal.png");
	texs.portal[1] = LoadSDLTexture("portal1.png");

	Mix_Volume(-1, 8);

	// LOAD SOUNDS
	sounds.pickup = Mix_LoadWAV("pickup.wav");
	if (!sounds.pickup)
		FatalError("InitGame: Could not load pickup.wav!");
	
	sounds.dead = Mix_LoadWAV("dead.wav");
	if (!sounds.dead)
		FatalError("InitGame: Could not load dead.wav!");
	
	sounds.win = Mix_LoadWAV("win.wav");
	if (!sounds.win)
		FatalError("InitGame: Could not load win.wav!");
	
	/*
	sounds.titlemus = Mix_LoadWAV("titlemus.wav");
	if (!sounds.titlemus)
		FatalError("InitGame: Could not load titlemus.wav!");
	Mix_VolumeChunk(sounds.titlemus, VOLUME);
	*/
	
	sounds.disappear = Mix_LoadWAV("disappear.wav");
	if (!sounds.disappear)
		FatalError("InitGame: Could not load disappear.wav!");

	sounds.energy = Mix_LoadWAV("energy.wav");
	if (!sounds.energy)
		FatalError("InitGame: Could not load energy.wav!");
	
	sounds.teleport = Mix_LoadWAV("teleport.wav");
	if (!sounds.teleport)
		FatalError("InitGame: Could not load teleport.wav!");
}

void FreeGameAssetts(void)
{
	// DESTROY TEXTURES
	SDL_DestroyTexture(texs.snake);
	SDL_DestroyTexture(texs.snakedead);
	SDL_DestroyTexture(texs.block);
	SDL_DestroyTexture(texs.apple);
	SDL_DestroyTexture(texs.portal[0]);
	SDL_DestroyTexture(texs.portal[1]);

	// FREE SOUNDS
	Mix_FreeChunk(sounds.pickup);
	Mix_FreeChunk(sounds.dead);
	Mix_FreeChunk(sounds.win);
	//Mix_FreeChunk(sounds.titlemus);
	Mix_FreeChunk(sounds.disappear);
	Mix_FreeChunk(sounds.energy);
	Mix_CloseAudio();
	
	printf("Textures and sounds freed.\n");
}


//
//	InitGame
///	Called to initialize or reset the game
//
void InitGame(bool newgame)
{
	int i,y,x;
	int numapples;
	int pindex, bindex;
	snake_t *sn;
	point_t newapple;
	byte *data;

	srand((unsigned int)time(NULL));
	
	
	// INIT GAME
	game.eventtime =  0;

	if (newgame) {
		game.level = STARTLEVEL;
		game.snake.currentbody = 0;
	} else {
		game.level++;
		if (game.level == 10) {
			game.state = ST_WIN;
			return;
		}
		printf("starting level %d...\n", game.level+1);
	}

	
	// LOAD DATA FROM BLOCK MAP
	
	// find the number of blocks on the map
	game.numblocks = 0;
	data = &blockdata[0][0];
	for (i=0; i<MAPWIDTH*MAPHEIGHT; i++, data++)
		if (*data == MAP_BLOCK)
			game.numblocks++;
	memset(game.blocks, 0, sizeof(point_t)*MAXBLOCKS);
	printf("...%d blocks\n",game.numblocks);
	
	
	// store portal and block locations
	for (y=0,bindex=0,pindex=0; y<MAPHEIGHT; y++) {
		for (x=0; x<MAPWIDTH; x++)
		{
			data = &blockdata[y][x];
			
			if (*data == MAP_EMPTY)
				continue;
			
			if (*data == MAP_PORTAL)
				game.portals[pindex++].location = MakePoint(x*TILESIZE, y*TILESIZE);
			else if (*data == MAP_BLOCK)
				game.blocks[bindex++] = MakePoint(x*TILESIZE, y*TILESIZE);
			else if (*data == MAP_START)
				game.snake.origin = MakePoint(x*TILESIZE, y*TILESIZE);
		}
	}

	
	// APPLES
	
	switch (game.skill) {
		case SK_EASY:	numapples = 3;	break;
		case SK_NORMAL: numapples = 10;	break;
		case SK_HARD:	numapples = 30;	break;
		default:
			printf("InitGame: Error. Game skill weirdness!");
			break;
	}
#ifdef ONEAPPLE
	game.numapples = 1;
	game.applesleft = 1;
	blockdata[SCREENHEIGHT/2/TILESIZE][SCREENWIDTH/2/TILESIZE] = MAP_APPLE;
	memset(game.apples, 0, sizeof(point_t)*MAXAPPLES);
	game.apples[0] = MakePoint(SCREENWIDTH/2, SCREENHEIGHT/2);
#else
	game.applesleft = game.numapples = (game.level+1)*numapples;
	memset(game.apples, 0, sizeof(point_t)*MAXAPPLES);
	printf("...%d apples\n",game.numapples);
	for (i=0 ; i<game.numapples ; i++) {
	top:
		newapple = MakePoint(rand()%40, rand()%30); // random place in map
		// check if map spot is free
		if (blockdata[newapple.y][newapple.x] != MAP_EMPTY ||
			TFPointsAreEqual(&newapple, &game.snake.origin))
			goto top;	// already a block, apple, or start pos there, try again

		if (blockdata[newapple.y][newapple.x] != MAP_EMPTY) {
			printf("InitGame: apple placement botched!\n");
			printf("Data at block map[%d][%d] is %d\n",newapple.x,newapple.y,blockdata[newapple.y][newapple.x]);
		}
		if (newapple.x > 39 || newapple.y > 29)
			printf("InitGame: apple placed outside level!\n");
		
		blockdata[newapple.y][newapple.x] = MAP_APPLE;
		game.apples[i] = MakePoint(newapple.x*TILESIZE, newapple.y*TILESIZE);
	}
#endif
	
	
	// SNAKE
	
	sn = &game.snake;
	sn->state = sleeping;
	sn->lastpt = game.snake.origin;
	sn->dx = sn->dy = 0;
	sn->numsegs = NUMSEGS;
	//memset(sn->segs, 0, 1200*sizeof(snakeseg_t));
	sn->headangle = 0;
	
	for (i=0;i<NUMSEGS;i++) {
		sn->segs[i].origin = sn->origin;
		sn->segs[i].lastpt = sn->origin;
	}

	game.portals[0].linkedpt = game.portals[1].location;
	game.portals[1].linkedpt = game.portals[0].location;

	printf("game inited\n");
}




