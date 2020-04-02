#ifndef TELA_H
#define TELA_H
#include <string>
#include <SDL/SDL.h>


class Tela
{
    public:
        Tela();
        virtual ~Tela();
        void apply_surface( float x, float y,float h, float w, SDL_Surface *source,  SDL_Surface *destination);
        void apply_surfaceC( float x, float y,float h, float w, SDL_Surface* source, SDL_Surface* destination,SDL_Rect Corte);
        SDL_Surface* load_image(std::string filename);
        void clean_surface(SDL_Surface* prozor, float x, float y, float h, float w);
    protected:
    private:
};

#endif // TELA_H
