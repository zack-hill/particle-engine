#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <string>

class Utility
{
public:
	Utility(void);
	~Utility(void);

	struct Int2
		{
		public:
			Int2::Int2(void)
			{
				x = 0;
				y = 0;
			}
			Int2::Int2(int new_x, int new_y)
			{
				x = new_x;
				y = new_y;
			}	
			int x;
			int y;
	};
	struct Float2
		{
		public:
			Float2::Float2(void)
			{
				x = 0;
				y = 0;
			}
			Float2::Float2(float new_x, float new_y)
			{
				x = new_x;
				y = new_y;
			}	
			float x;
			float y;
	};

	static SDL_Surface* loadImage(std::string filename);
	static void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL );
	static std::string convertInt(int number);
};

