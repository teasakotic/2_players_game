#include "Tela.h"
#include <iostream>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
Tela::Tela()
{
    //ctor
}

void Tela::clean_surface(SDL_Surface* janela, float x, float y, float h, float w)
{
    SDL_Rect area;
    area.x = x;
    area.y = y;
    area.h = h;
    area.w = w;
    //SDL_FillRect "limpa" a tela: pega a area a ser utilizada, o local de aplicacao
    //e a cor a ser utilizada. SDL_MapRGB cria uma cor com o mesmo formato da tela
    //logo, o SDL nao precisa converter nada
    SDL_FillRect(janela, &area, SDL_MapRGB( janela->format, 0,0,0));
}
void Tela::apply_surfaceC( float x, float y,float h, float w, SDL_Surface* source, SDL_Surface* destination,SDL_Rect Corte)
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect posicao;

    //Give the offsets to the rectangle
    posicao.x = x;
    posicao.y = y;
    posicao.h = h;
    posicao.w = w;
    //Blit the surface
    SDL_BlitSurface( source, &Corte, destination, &posicao );
}
void Tela::apply_surface( float x, float y,float h, float w, SDL_Surface* source, SDL_Surface* destination)
{
    //Make a temporary rectangle to hold the offsets
    SDL_Rect posicao;

    //Give the offsets to the rectangle
    posicao.x = x;
    posicao.y = y;
    posicao.h = h;
    posicao.w = w;
    //Blit the surface
    SDL_BlitSurface( source, NULL, destination, &posicao );
}
SDL_Surface* Tela::load_image(std::string filename)
{
    //local temporario para armazenar a imagem
    SDL_Surface *loadedImage = NULL;

    //imagem otimizada
    SDL_Surface *optimizedImage = NULL;

    //abre a imagem
    loadedImage = IMG_Load(filename.c_str());

    //se der certo...
    if(loadedImage != NULL)
    {
        //cria a imagem otimizada
        optimizedImage = SDL_DisplayFormat( loadedImage);

        //libera a imagem carregada
        SDL_FreeSurface(loadedImage);

    }
    //retorna a imagem otimizada
    return optimizedImage;
}
Tela::~Tela()
{
    //dtor
}
