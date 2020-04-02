#ifndef MAPA_H
#define MAPA_H
#include <string>
#include <fstream>
#include "Tela.h"

class Mapa : public Tela
{
    public:
        Mapa();
        ~Mapa();
        void printPozadina(SDL_Surface *prozor, float visina_prozor, float sirina_prozor);
        void Sudar(SDL_Surface *prozor, float visina_prozor, float sirina_prozor, std::string tipo);
        bool proveraSudara(float xTk, float yTk, float visinaTk, float sirinaTk, std::string parametar);
        float getVisina();
        float getSirina();
        void TipPromene();


    protected:
    private:
    SDL_Surface* blokovi;
    SDL_Rect trava;
    SDL_Rect kamen;
    SDL_Rect voda;
    SDL_Rect cigla;
    SDL_Rect zemlja;
    int visina;
    int sirina;
    std::string MapaText;
    std::string linijaTemp;
    std::ifstream map;
    float MapaSudara[640][4];
    std::string Tipo;

};

#endif // MAPA_H
