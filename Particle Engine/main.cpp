#include "ParticleEngine.h"

//Screen attributes
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;

int frame = 0;
bool cap = true;

SDL_Surface* screen = NULL;

SDL_Event event;

ParticleEngine *particleEngine;

void Initialize()
{
    SDL_Init(SDL_INIT_EVERYTHING);

	SDL_putenv("SDL_VIDEO_CENTERED=center");
	SDL_WM_SetIcon(Utility::loadImage("Content/icon.png"), NULL);

    screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE );
	
    SDL_WM_SetCaption( "C++ Particle Engine Using SDL", NULL );

	particleEngine->Initialize();
}

void clean_up()
{
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    bool quit = false;
	Initialize();
	
    while(quit == false)
    {
		particleEngine->Update();
		particleEngine->Draw(screen);

        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                quit = true;
            }
			else
				particleEngine->EventHandler(event);
        }
		
        frame++;
    }

    clean_up();

    return 0;
}
