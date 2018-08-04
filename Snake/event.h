//
//  event.h
//  Snake
//
//  Created by Thomas Foster on 8/3/18.
//  Copyright © 2018 Thomas Foster. All rights reserved.
//

#ifndef event_h
#define event_h

#include <stdio.h>
#include <SDL2/SDL.h>
#include "tffunctions.h"

extern bool keypressed;
bool ProcessEvents(SDL_Event *ev);

#endif /* event_h */
