#ifndef TANK_H
#define TANK_H
#include <string>
#include "Tela.h"
#include "Mapa.h"
#include <SDL/SDL.h>



class Tank: public Tela
{
    public:
        Tank(int num, SDL_Surface* Prozor,float visina_prozor, float sirina_prozor);
        virtual ~Tank();
        void move(float visina_prozor, float sirina_prozor, Uint8 *kljuc,
                float visinaBlok, float sirinaBlok, bool sudar,
                float x2, float y2, float h2, float w2
                );

        float getX();
        float getY();
        float getVisina();
        float getSirina();
        float gethMetak();
        float getwMetak();
        SDL_Surface* getImagem();
        void printTank(SDL_Surface* prozor, float x2,float y2,float h2,float w2);
        void sudariIgraca(float x2, float y2, float h2, float w2);
        void printMetak();
        void moveMetak();
        void sudarMetak(float x2, float y2, float h2, float w2);
        void dovodi_ostecenje(bool ostecenje);
        bool getUzrok_ostecenje();
        void printLife(float visina_prozor, float sirina_prozor);
        int ostecenje;


    protected:
    private:
    int zivotTemp;
    int zivot;
    struct e;
    SDL_Surface* life;
    SDL_Rect life_cut;
    bool uzrok_ostecenje;
    float standardne_pozicije[2][3];
    float metak[100][3];
    bool sudar_metak1[100][1];
    int brojac_metak;
    float vMetak;
    float hMetak;
    float wMetak;
    SDL_Surface* bullet;
    SDL_Surface* bulletR;
    SDL_Surface *tank;
    float visina;
    float sirina;
    float x;
    float y;
    float vx;
    float vy;
    int player;
    SDL_Rect tankReal;
    int ugao;
    SDL_Surface* tankR;
    bool sudar_cisterne;
    Mapa pozadina;
    float TempoInicialMetak;
    float TempoFinalMetak;
    float TempoPucanje;
    SDL_Surface* boom;
    SDL_Rect eksplozija;
    SDL_Surface* prozor;
    float TempoExpInicial;
    float TempoExpFinal;
    void VratiPoziciju(float x2,float y2,float h2,float w2);



};

#endif // TANK_H
