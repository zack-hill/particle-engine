#include "Utility.h"
#include <string>
#include <sstream>
#include <iostream>

SDL_Surface* Utility::loadImage(std::string filename) 
{
    //The image that's loaded
    SDL_Surface* loadedImage = NULL;
    
    //The optimized image that will be used
    SDL_Surface* optimizedImage = NULL;
    
    //Load the image using SDL_image
    loadedImage = IMG_Load( filename.c_str() );
    
    //If the image loaded
    if( loadedImage != NULL )
    {
        //Create an optimized image
        optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
        
        //Free the old image
        SDL_FreeSurface(loadedImage);
    }
    
    //Return the optimized image
    return optimizedImage;
}

void Utility::ApplySurface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip)
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}

std::string Utility::convertInt(int number)
{
   std::stringstream ss;
   ss << number;
   return ss.str();
}