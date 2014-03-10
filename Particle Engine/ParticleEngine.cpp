#include "ParticleEngine.h"

#include <vector>
#include <windows.h>

using namespace std;

struct rect
{
	float x;
	float y;
	int h;
	int w;
};

struct Particle
{
	SDL_Surface* texture;
	rect box;
	float xVel;
	float yVel;
	double weight;

};

const int particleCount		= 100000;
const float velDecay		= .999f;
const float velCap			= 3.5f;
const float maxInitialVel	= 1.f;
const float mouseForce		= 100.f;
const float gravity			= .05f;

rect windowBounds;

Particle *particles[particleCount];

SDL_Surface *particleSurface;

bool quit = false;
bool friction = true;
bool mousePower;

Utility::Int2 mousePos;

float Distance(float dX0, float dY0, float dX1, float dY1)
{
    return sqrt((dX1 - dX0)*(dX1 - dX0) + (dY1 - dY0)*(dY1 - dY0));
}

void ParticleEngine::Initialize()
{
	quit = false;
	SDL_WM_SetCaption( "Particle Engine", NULL );
	
	particleSurface = Utility::loadImage("Content/ParticleEngine/particle.png");

	srand(GetTickCount());

	windowBounds.w = 1920;
	windowBounds.h = 1080;
	windowBounds.x = 0;
	windowBounds.y = 0;

	for(int i = 0; i < particleCount; i++)
	{		
		particles[i] = new Particle();
		particles[i]->texture = particleSurface;
		
		particles[i]->box.x = rand() % windowBounds.w + windowBounds.x;
		particles[i]->box.y = rand() % windowBounds.h + windowBounds.y;
		particles[i]->box.w = 5;
		particles[i]->box.h = 5;
		particles[i]->weight = ((float) rand() / (RAND_MAX)) + 1;

		particles[i]->xVel = 0;
		particles[i]->yVel = 0;
	}

	SDL_WarpMouse( (windowBounds.w + windowBounds.x) / 2, (windowBounds.h + windowBounds.y) / 2 );
}

void ParticleEngine::EventHandler(SDL_Event event)
{
	if( event.type == SDL_MOUSEBUTTONDOWN )
    {
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			mousePower = true;
		}
	}

	if( event.type == SDL_MOUSEBUTTONUP )
    {
		if( event.button.button == SDL_BUTTON_LEFT )
		{
			mousePower = false;
		}
	}

	if( event.type == SDL_MOUSEMOTION ) 
    {
		int x, y; 
		SDL_GetMouseState( &x, &y );
		mousePos = Utility::Int2(x, y);
	}

	if(event.type == SDL_KEYDOWN)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_ESCAPE: quit = true; SDL_ShowCursor(SDL_ENABLE); break; 
			case SDLK_f: friction = !friction; break;
			case SDLK_r: 
				{
					for(int i = 0; i < particleCount; i++)
					{
						particles[i]->box.x = rand() % windowBounds.w + windowBounds.x;
						particles[i]->box.y = rand() % windowBounds.h + windowBounds.y;
						particles[i]->xVel = 0;
						particles[i]->yVel = 0;
					}
					break;
				}
			case SDLK_t:
				{
					for(int i = 0; i < particleCount; i++)
					{
						particles[i]->box.x = windowBounds.w/2 + windowBounds.x;
						particles[i]->box.y = windowBounds.h/2 + windowBounds.y;
						particles[i]->xVel = 0;
						particles[i]->yVel = 0;
					}
					break;
				}
		}
	}	
}

int ParticleEngine::Update()
{
	for(int i = 0; i < particleCount; i++)
	{
		if(mousePower)
		{
			float dx = mousePos.x - particles[i]->box.x;
			float dy = mousePos.y - particles[i]->box.y;
			float dist = Distance(mousePos.x, mousePos.y, particles[i]->box.x, particles[i]->box.y);

			if(dist > 2)
			{
				particles[i]->xVel += (float)(dx * mouseForce)/(dist * dist);
				particles[i]->yVel += (float)(dy * mouseForce)/(dist * dist);
			}
		}

		//Fricion
		if(friction)
			particles[i]->xVel *= velDecay;
			particles[i]->yVel *= velDecay;

			particles[i]->yVel += gravity;

			if (particles[i]->box.y < windowBounds.y) 
			{
				particles[i]->yVel *= -0.9;
				particles[i]->box.y = windowBounds.y;
			}
	
			if (particles[i]->box.y > windowBounds.h + windowBounds.y)
			{
				particles[i]->yVel *= -0.45;
				particles[i]->box.y = windowBounds.h + windowBounds.y;
			}
	
			if (particles[i]->box.x < windowBounds.x)
			{
				particles[i]->xVel *= -0.9;
				particles[i]->box.x = windowBounds.x;
			}
	
			if (particles[i]->box.x > windowBounds.w + windowBounds.x)
			{
				particles[i]->xVel *= -0.9;
				particles[i]->box.x = windowBounds.w + windowBounds.x;
			}
			
		//Pos += Vel
		particles[i]->box.x += particles[i]->xVel / particles[i]->weight;
		particles[i]->box.y += particles[i]->yVel / particles[i]->weight;
		}

	if( quit )
		return 1;
	else
		return 0;
}

void ParticleEngine::Draw(SDL_Surface* screen)
{
	SDL_FillRect(screen, NULL, 0 );
	for(int i = 0; i < particleCount; i++)
	{
		Utility::ApplySurface((int)particles[i]->box.x, (int)particles[i]->box.y, particles[i]->texture, screen);
	}
	SDL_Flip(screen);
}
