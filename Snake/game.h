//
//  game.h
//  Snake
//
//  Created by Thomas Foster on 7/28/18.
//  Copyright © 2018 Thomas Foster. All rights reserved.
//
//	Game Logic

#ifndef game_h
#define game_h

#include <stdio.h>
#include "sdl.h"

typedef enum
{
	ST_TITLESCREEN,
	ST_SKILLSCREEN,
	ST_LEVELSCREEN,
	ST_GAME,
	ST_GAMEOVERSCREEN,
	ST_WIN
} gamestate_e;

typedef enum { SK_EASY, SK_NORMAL, SK_HARD } gameskill_e;

typedef enum {
	SN_GREEN,
	SN_BROWN,
	SN_ORANGE,
	SN_YELLOW,
	SN_BLUE,
	SN_CYAN,
	SN_PURPLE,
	SN_MAGENTA,
	SN_WHITE,
	SN_NUMCOLORS
} snakecolors_e;

extern SDL_Color snakecolors[SN_NUMCOLORS];


typedef struct
{
	SDL_Texture	*snake;
	SDL_Texture *snakedead;
	SDL_Texture	*block;
	SDL_Texture	*apple;
	SDL_Texture	*portal[2];
} gametextures_t;

typedef struct
{
	Mix_Chunk	*pickup;
	Mix_Chunk	*dead;
	Mix_Chunk	*win;
	Mix_Chunk	*titlemus;
	Mix_Chunk	*disappear;
	Mix_Chunk	*energy;
	Mix_Chunk	*teleport;
} gamesounds_t;

typedef struct
{
	point_t origin;
	point_t lastpt;
} snakeseg_t;

typedef struct
{
	point_t 	origin;
	point_t		lastpt;
	int 		dx,dy;
	enum 		{ sleeping, active, dead } state;

	double		headangle;
	int			currentbody; // index of current snakebody/head texture
	
	int 		numsegs;
	snakeseg_t	segs[1200];
} snake_t;

typedef struct
{
	point_t	location;
	point_t linkedpt;
} portal_t;




// ====================

#define MAXAPPLES 300
#define MAXBLOCKS 30*40
#define TILESIZE 16
extern sizetype tilesize; // handy for making SDL_Rect from point_t and sizetype

typedef struct
{
	int 		ticks;
	int			state;
	int			level;
	int			skill;

	snake_t		snake;
	int			applesleft;	// level complete when 0
	int 		eventtime;	// for timing of level complete or death anim
	
	portal_t	portals[2];
	
	int			numblocks;
	int			numapples;
	point_t		apples[MAXAPPLES];	// for rendering
	point_t		blocks[MAXBLOCKS];	// for rendering
} game_t;

#define MAPHEIGHT	30
#define MAPWIDTH 	40

typedef enum {
	MAP_EMPTY,
	MAP_BLOCK,
	MAP_APPLE,
	MAP_PORTAL,
	MAP_START
} mapobject_e;

extern byte blockdata[30][40];

extern game_t			game;
extern gametextures_t	texs;
extern gamesounds_t		sounds;

void LoadGameAssetts (void);
void ResetBlockMap (void);
void InitGame (bool newgame);
void FreeGameAssetts (void);

#define HEAD 0
#define BODY 1
SDL_Rect SnakeRect(bool body, snakecolors_e color);
SDL_Rect DeadSnakeRect(bool body);

#endif /* game_h */
