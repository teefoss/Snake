//
//  main.c
//  Snake
//
//  Created by Thomas Foster on 7/27/18.
//  Copyright © 2018 Thomas Foster. All rights reserved.
//

#include <stdio.h>
#include "sdl.h"
#include "gamemain.h"

int main(int argc, const char * argv[])
{
	StartSDL();
	
	GameMain();
	
	StopSDL();
	return 0;
}
