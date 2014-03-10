#pragma once

#include "Utility.h"

class ParticleEngine
{
public:
	void Initialize();
	void EventHandler(SDL_Event event);
	int Update();
	void Draw(SDL_Surface* screen);
	ParticleEngine(void) { };
	~ParticleEngine(void) { };
};

