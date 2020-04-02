#include <iostream>
#include <string>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Mapa.h"
#include "Tank.h"
#include "Tela.h"
#include "SDL/SDL_rotozoom.h"

using namespace std;

int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);


    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return 1;
    }


    SDL_WM_SetCaption("Tank", NULL);


    bool running = true;
    SDL_Event dogadjaj;


    struct dimenzije
    {
        float visina, sirina;
    }zatamnjenProzor;


    SDL_Surface *prozor = NULL;
    zatamnjenProzor.sirina = 1300;
    zatamnjenProzor.visina = 660;
    prozor = SDL_SetVideoMode(zatamnjenProzor.sirina, zatamnjenProzor.visina, 32, SDL_HWSURFACE);


    Mapa pozadina;
    Tank player1(1,prozor, zatamnjenProzor.visina, zatamnjenProzor.sirina);
    Tank player2(2,prozor, zatamnjenProzor.visina, zatamnjenProzor.sirina);


    pozadina.Sudari(prozor,zatamnjenProzor.visina,zatamnjenProzor.sirina, "tank");
    float visina = pozadina.getVisina();
    float sirina = pozadina.getSirina();

    const int FRAMES_PER_SECOND = 150;
    int frame = 0;
    float tempoInicial = 0;
    float tempoFinal = 0;
    float DeltaT = 0;

    SDL_Rect test;
    test.x = 0;
    test.y = 0;
    test.h = 660;
    test.w = 1330;

    while (running)
    {
        tempoInicial = SDL_GetTicks();

        SDL_PollEvent(&dogadjaj);
        if(dogadjaj.type == SDL_QUIT)
        {
            running = false;
            break;
        }

        Uint8 *kljuc = SDL_GetKeyState(NULL);

        if(kljuc[SDLK_ESCAPE])
        {
            running = false;
            break;
        }



        player1.move(zatamnjenProzor.visina, zatamnjenProzor.sirina,
                     kljuc,visina, sirina,
                     pozadina.proveraSudara(player1.getX(), player1.getY(),
                                           player1.getVisina(),player1.getSirina(),""),
                     player2.getX(), player2.getY(),player2.getVisina(),player2.getSirina());



        if(pozadina.proveraSudara(player1.getX(), player1.getY(),player1.getVisina(),
                                           player1.getSirina(),"") == 1)
        {
            player1.move(zatamnjenProzor.visina, zatamnjenProzor.sirina,
                          kljuc,visina, sirina,
                          pozadina.proveraSudara(player1.getX(), player1.getY(),
                                                player1.getVisina(),player1.getSirina(),""),
                         player2.getX(), player2.getY(),player2.getVisina(),player2.getSirina());
        }


        player2.move(zatamnjenProzor.visina, zatamnjenProzor.sirina,
                     kljuc,visina, sirina,
                     pozadina.proveraSudara(player2.getX(), player2.getY(),
                                           player2.getVisina(),player2.getSirina(),""),
                     player1.getX(), player1.getY(), player1.getVisina(), player1.getSirina());

        if(pozadina.proveraSudara(player2.getX(), player2.getY(),player2.getVisina(),
                                           player2.getSirina(),"") == 1)
        {
            player2.move(zatamnjenProzor.visina, zatamnjenProzor.sirina,
                          kljuc,visina, sirina,
                          pozadina.proveraSudara(player2.getX(), player2.getY(),
                                                player2.getVisina(),player2.getSirina(),""),
                         player1.getX(), player1.getY(), player1.getVisina(), player1.getSirina());
        }


        player1.moveMetak();
        player2.moveMetak();
        player1.sudarMetak(player2.getX(), player2.getY(), player2.getVisina(), player2.getSirina());
        player2.sudarMetak(player1.getX(), player1.getY(), player1.getVisina(), player1.getSirina());


        player1.dovodi_ostecenje(player2.getCausa_dano());
        player2.dovodi_ostecenje(player1.getCausa_dano());


        pozadina.printPozadina(prozor, zatamnjenProzor.visina, zatamnjenProzor.sirina);
        player1.printTank(prozor, player2.getX(),player2.getY(), player2.getVisina(), player2.getSirina());
        player2.printTank(prozor, player1.getX(),player1.getY(), player1.getVisina(), player1.getSirina());
        player1.printMetak();
        player2.printMetak();
        player1.printLife(zatamnjenProzor.visina, zatamnjenProzor.sirina);
        player2.printLife(zatamnjenProzor.visina, zatamnjenProzor.sirina);


        SDL_Flip(prozor);


        frame++;
        tempoFinal = SDL_GetTicks();
        DeltaT = tempoFinal - tempoInicial;
        if(DeltaT < 1000/ FRAMES_PER_SECOND)
        {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - DeltaT);
        }


    }


    SDL_Quit();

    return 0;

}
