//
//  display.c
//  Snake
//
//  Created by Thomas Foster on 7/30/18.
//  Copyright © 2018 Thomas Foster. All rights reserved.
//

#include "display.h"
#include "sdl.h"
#include "game.h"
#include "tffunctions.h"


typedef struct
{
	texture_t title;
	texture_t author;
	texture_t anykey;
	texture_t youlose;
	texture_t playagain;
	texture_t level;
	texture_t apple;
	texture_t skill[4];
} labels_t;

labels_t labels;
SDL_Rect skillrects[4];

int	currentportal = 0;

// windata uses 3 - snake body, 4 - snake head
byte windata[30][40] = {
	//	 1             8               16              24              32              40
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},// 1
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},// 8
	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,2,2,2,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,0,2,0,0,0,2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,2,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,2,2,2,0,0,0,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,2,0,0,0,0,2,0,3,0,0,0,0,0,0,0,0,0,0,0},// 16
	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,2,2,0,0,0,2,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,2,0,0,2,0,2,0,2,0,2,0,0,2,0,3,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,0,2,0,2,0,2,0,2,0,2,0,0,2,0,2,0,4,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,2,0,0,0,2,2,0,2,0,2,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,2,0,2,0,2,0,0,0,0,2,0,2,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},// 24
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},//30
};


//
//  LoadScreens
///	Loads the text labels for the title, skill, and game over screens
///	These screens are static, this is only called once at the start
//
void LoadScreens (void)
{
	int i, maxwidth, height;
	int skillx, skilly;

	labels.title = CreateText("Snake", snakecolors[SN_GREEN]);
	labels.author = CreateText("by Thomas Foster", vgacolor[VGA_WHITE]);
	labels.anykey = CreateText("Press Any Key", vgacolor[VGA_WHITE]);
	labels.youlose = CreateText("You Lose!", vgacolor[VGA_RED]);
	labels.playagain = CreateText("Play again? (Y/N)", vgacolor[VGA_WHITE]);
	labels.skill[0] = CreateText("Skill", vgacolor[VGA_YELLOW]);
	labels.skill[1] = CreateText("(1) Easy-Peasy", vgacolor[VGA_YELLOW]);
	labels.skill[2] = CreateText("(2) \"Normal\"", vgacolor[VGA_YELLOW]);
	labels.skill[3] = CreateText("(3) Total Insanity", vgacolor[VGA_YELLOW]);
	
	// Calc rects for skill screen labels
	maxwidth = -1;
	height = labels.skill[0].size.height;
	for (i=0; i<4; i++) {
		if (labels.skill[i].size.width > maxwidth)
			maxwidth = labels.skill[i].size.width;
	}
	
	skillx = SCREENWIDTH/2-maxwidth/2;
	skilly = SCREENHEIGHT/2-(4*(height/2));
	for (i=0; i<4; i++) {
		skillrects[i] = SDLRect(skillx, skilly+height*i, labels.skill[i].size.width, labels.skill[i].size.height);
	}

}



//
//	LoadLevelScreen
///	Level screen doesn't have static text,
/// call this whenever it's displayed
//
void LoadLevelScreen (void)
{
	char leveltext[16] = "";
	char appletext[16] = "";
	sprintf(leveltext, "Level %d", game.level+1);
	sprintf(appletext, "%d Apples", game.numapples);
	labels.level = CreateText(leveltext, snakecolors[game.snake.currentbody]);
	labels.apple = CreateText(appletext, vgacolor[VGA_WHITE]);
}



//
//	FreeScreens
//
void FreeScreens (void)
{
	SDL_DestroyTexture(labels.title.texture);
	SDL_DestroyTexture(labels.author.texture);
	SDL_DestroyTexture(labels.anykey.texture);
	SDL_DestroyTexture(labels.youlose.texture);
	SDL_DestroyTexture(labels.playagain.texture);
	for (int i=0; i<4; i++)
		SDL_DestroyTexture(labels.skill[i].texture);
}




#pragma mark -

//
//	DisplayTitleScreen
//
void DisplayTitleScreen (void)
{
	SetDrawColor(vgacolor[VGA_BLACK]);
	SDL_RenderClear(renderer);

	SDL_Rect titlerect = SDLRect(SCREENWIDTH/2-labels.title.size.width/2,
									   SCREENHEIGHT/2-labels.title.size.height,
									   labels.title.size.width,
									   labels.title.size.height);
	SDL_Rect authorrect = SDLRect(SCREENWIDTH/2-labels.author.size.width/2,
									   SCREENHEIGHT/2+labels.author.size.height,
									   labels.author.size.width,
									   labels.author.size.height);
	SDL_Rect keyrect = SDLRect(SCREENWIDTH/2-labels.anykey.size.width/2,
										SCREENHEIGHT-labels.anykey.size.height-16,
										labels.anykey.size.width,
										labels.anykey.size.height);
	
	SDL_RenderCopy(renderer, labels.title.texture, NULL, &titlerect);
	SDL_RenderCopy(renderer, labels.author.texture, NULL, &authorrect);
	SDL_RenderCopy(renderer, labels.anykey.texture, NULL, &keyrect);

	SDL_RenderPresent(renderer);	
}


void DisplaySkillScreen (void)
{
	SetDrawColor(vgacolor[VGA_BLACK]);
	SDL_RenderClear(renderer);

	for (int i=0; i<4; i++)
	SDL_RenderCopy(renderer, labels.skill[i].texture, NULL, &skillrects[i]);
	
	SDL_RenderPresent(renderer);
}




//
//	DisplayLevelScreen
//
void DisplayLevelScreen (void)
{
	SetDrawColor(vgacolor[VGA_BLACK]);
	SDL_RenderClear(renderer);
	
	SDL_Rect levelrect = SDLRect(SCREENWIDTH/2-labels.level.size.width/2,
									   SCREENHEIGHT/2-labels.level.size.height,
									   labels.level.size.width,
									   labels.level.size.height);
	SDL_Rect applerect = SDLRect(SCREENWIDTH/2-labels.apple.size.width/2,
									   SCREENHEIGHT/2+labels.apple.size.height,
									   labels.apple.size.width,
									   labels.apple.size.height);
	SDL_Rect keyrect = SDLRect(SCREENWIDTH/2-labels.anykey.size.width/2,
									 SCREENHEIGHT-labels.anykey.size.height-16,
									 labels.anykey.size.width,
									 labels.anykey.size.height);

	SDL_RenderCopy(renderer, labels.level.texture, NULL, &levelrect);
	SDL_RenderCopy(renderer, labels.apple.texture, NULL, &applerect);
	SDL_RenderCopy(renderer, labels.anykey.texture, NULL, &keyrect);

	SDL_RenderPresent(renderer);
}



//
//	DisplayGameOverScreen
//
void DisplayGameOverScreen (void)
{
	SetDrawColor(vgacolor[VGA_BLACK]);
	SDL_RenderClear(renderer);
	
	SDL_Rect loserect = SDLRect(SCREENWIDTH/2-labels.youlose.size.width/2,
									  SCREENHEIGHT/2-labels.youlose.size.height,
									  labels.youlose.size.width,
									  labels.youlose.size.height);
	SDL_Rect playagainrect = SDLRect(SCREENWIDTH/2-labels.playagain.size.width/2,
									  SCREENHEIGHT/2+labels.playagain.size.height,
									  labels.playagain.size.width,
									  labels.playagain.size.height);

	SDL_RenderCopy(renderer, labels.youlose.texture, NULL, &loserect);
	SDL_RenderCopy(renderer, labels.playagain.texture, NULL, &playagainrect);

	SDL_RenderPresent(renderer);
}



//
//	DisplayGame
//
void DisplayGame (void)
{
	SDL_Rect	src, dest, prect;
	snakeseg_t	*seg;
	point_t		*headorg, *apple, *block;
	int 		i,j;
	
	if (game.ticks % 75 == 0)
		currentportal ^= 1;
	
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	

	// BLOCKS
	
	block = &game.blocks[0];
	for (i=0; i<game.numblocks; i++, block++) {
		dest = SDLRectFromPoint(*block, tilesize);
		SDL_RenderCopy(renderer, texs.block, NULL, &dest);
	}


	// APPLES
	
	apple = &game.apples[0];
	for (i=0; i<game.numapples; i++, apple++) {
		if (blockdata[apple->y/TILESIZE][apple->x/TILESIZE] == MAP_APPLE) {
			dest = SDLRectFromPoint(*apple, tilesize);
			SDL_RenderCopy(renderer, texs.apple, NULL, &dest);
		}
	}
	
	
	
	// PORTALS

	portal_t *p = &game.portals[0];
	for (i=0; i<2; i++, p++) {
		SDL_Rect portalrect = { p->location.x, p->location.y, TILESIZE, TILESIZE };
		SDL_RenderCopy(renderer, texs.portal[currentportal], NULL, &portalrect);
	}


	// SNAKE HEAD
	
	headorg = &game.snake.origin;
	// halfway through level complete event, render random color
	if (game.eventtime && game.ticks > game.eventtime+1500) {
		game.snake.currentbody = rand() % 9;
	}
	
	src = SnakeRect(HEAD, game.snake.currentbody);
	dest = SDLRectFromPoint(*headorg, tilesize);
	
	if (game.snake.state == dead) {
		if (game.ticks < game.eventtime+1500) {
			src = DeadSnakeRect(HEAD);
			SDL_RenderCopyEx(renderer, texs.snakedead, &src, &dest, game.snake.headangle, NULL, 0);
		}
	} else {
		if (TFPointsAreEqual(headorg, &game.portals[0].location) ||
			TFPointsAreEqual(headorg, &game.portals[1].location))
		{
			p = &game.portals[0];
			for (i=0; i<2; i++, p++) { // render heads at both portals
				prect = SDLRectFromPoint(p->location, tilesize);
				SDL_RenderCopyEx(renderer, texs.snake, &src, &prect, game.snake.headangle, NULL, 0);
			}
		}
		SDL_RenderCopyEx(renderer, texs.snake, &src, &dest, game.snake.headangle, NULL, 0);
	}

	
	// SNAKE BODY

	seg = &game.snake.segs[0];
	src = SnakeRect(BODY, game.snake.currentbody);
	for (i = 0; i < game.snake.numsegs; i++, seg++) {
		dest = SDLRectFromPoint(seg->origin, tilesize);
		if (game.snake.state == dead) {
			src = DeadSnakeRect(BODY);
			if (game.ticks < game.eventtime+1500)
				SDL_RenderCopy(renderer, texs.snakedead, &src, &dest);
		} else {
			SDL_RenderCopy(renderer, texs.snake, &src, &dest);
			for (j=0; j<2; j++) {
				if (TFPointsAreEqual(&seg->origin, &game.portals[j].location)) {
					prect = SDLRectFromPoint(game.portals[j].linkedpt, tilesize);
					SDL_RenderCopy(renderer, texs.snake, &src, &prect);
					break;
				}
			}
		}
	}
	
	SDL_RenderPresent(renderer);

	if (!game.eventtime)
		return;

	// HANDLE EVENTS
	
	// ? 	Seems this should be in ProcessGame... but it needs render
	//		snake's last move before going to next screen.

	if (game.snake.state == dead) 	// game over
	{
		if (game.ticks == game.eventtime+3000) {
			game.state = ST_GAMEOVERSCREEN;
		}
	}

	else // level complete
	{
		int delay = (game.level == 9) ? 5000 : 3000;
		if (game.ticks == game.eventtime+delay) {
			InitGame(false);
			if (game.level != 10) { // lvl still increased even tho 9 is last
				Mix_HaltChannel(-1);
				game.state = ST_LEVELSCREEN;
				LoadLevelScreen();
			}
		}
	}
}



void DisplayWinScreen(void)
{
	int y,x,c;
	byte *data;
	SDL_Rect src, dest;
	
	SetDrawColor(vgacolor[VGA_BLACK]);
	SDL_RenderClear(renderer);

	c = rand() % SN_NUMCOLORS;
	for (y=0; y<30; y++) {
		for (x=0; x<40; x++)
		{
			data = &windata[y][x];
			
			if (*data == MAP_EMPTY)
				continue;
			
			dest = SDLRect(x*TILESIZE, y*TILESIZE, TILESIZE, TILESIZE);
			if (*data == MAP_APPLE) {
				SDL_RenderCopy(renderer, texs.apple, NULL, &dest);
			} else if (*data == 3) {
				src = SnakeRect(BODY, c);
				SDL_RenderCopy(renderer, texs.snake, &src, &dest); //body
			} else if (*data == 4) {
				src = SnakeRect(HEAD, c);
				SDL_RenderCopyEx(renderer, texs.snake, &src, &dest, 180, NULL, 0); //head
			}

		}
	}
	SDL_RenderPresent(renderer);
}



//
//	Display
/// Render the appropriate stuff for current game state
//
void Display(void)
{
	switch (game.state)
	{
		case ST_TITLESCREEN: 	DisplayTitleScreen(); break;
		case ST_GAME: 			DisplayGame(); break;
		case ST_GAMEOVERSCREEN: DisplayGameOverScreen(); break;
		case ST_LEVELSCREEN: 	DisplayLevelScreen(); break;
		case ST_SKILLSCREEN:	DisplaySkillScreen(); break;
		case ST_WIN:			DisplayWinScreen(); break;
		default: break;
	}
}
