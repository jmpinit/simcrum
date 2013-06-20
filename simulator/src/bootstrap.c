#include "stdbool.h"
#include "SDL/SDL.h"

void idle() {
	bool pause = false;
	bool dead = false;

	while(!dead) {
		if(!pause) {
			SDL_Event event;
			
			while(SDL_PollEvent(&event)) {
				switch (event.type) {
					case SDL_QUIT:
						exit(0);
					break;
					
					case SDL_KEYDOWN:
						switch (event.key.keysym.sym) {
							case SDLK_ESCAPE:
								exit(0);
							break;
							
							default:
							break;
						}
					break;
				}
			}

			SDL_Delay(16);
		}
	}
}
