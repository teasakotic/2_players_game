#include "Tela.h"
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
Tela::Tela()
{

}

void Tela::clean_surface(SDL_Surface* prozor, float x, float y, float h, float w)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.h = h;
    area.w = w;

    SDL_FillRect(prozor, &area, SDL_MapRGB( prozor->format, 0,0,0));
}
void Tela::apply_surfaceC( float x, float y,float h, float w, SDL_Surface* source, SDL_Surface* destination,SDL_Rect Corte)
{

    SDL_Rect polozaj;

    polozaj.x = x;
    polozaj.y = y;
    polozaj.h = h;
    polozaj.w = w;

    SDL_BlitSurface( source, &Corte, destination, &polozaj );
}
void Tela::apply_surface( float x, float y,float h, float w, SDL_Surface* source, SDL_Surface* destination)
{

    SDL_Rect polozaj;


    polozaj.x = x;
    polozaj.y = y;
    polozaj.h = h;
    polozaj.w = w;

    SDL_BlitSurface( source, NULL, destination, &polozaj );
}
SDL_Surface* Tela::load_image(std::string filename)
{

    SDL_Surface *loadedImage = NULL;


    SDL_Surface *optimizedImage = NULL;


    loadedImage = IMG_Load(filename.c_str());


    if(loadedImage != NULL)
    {

        optimizedImage = SDL_DisplayFormat( loadedImage);

        SDL_FreeSurface(loadedImage);

    }

    return optimizedImage;
}
Tela::~Tela()
{

}
