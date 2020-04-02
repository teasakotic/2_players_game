#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include "Mapa.h"
#include "Tela.h"

Mapa::Mapa()
{
    Tipo = "normal";
    blokovi = load_image("Blocos.png");
    visina = 32;
    sirina = 32;

    trava.x = 0;
    trava.y = 0;
    trava.h = 32;
    trava.w = 32;

    kamen.x = 32;
    kamen.y = 0;
    kamen.h = 32;
    kamen.w = 32;

    voda.x = 0;
    voda.y = 32;
    voda.h = 32;
    voda.w = 32;

    cigla.x = 0;
    cigla.y = 64;
    cigla.h = 32;
    cigla.w = 32;

    zemlja.x = 32;
    zemlja.y = 32;
    zemlja.h = 32;
    zemlja.w = 32;


    map.open("mapa.txt");

    if (map.is_open())
    {
        while(map.good())
        {
            getline(map, linijaTemp);
            MapaText += linijaTemp ;

        }
        map.close();
    }

}

void Mapa::TipPromene()
{
    Tipo = "metak";
}
float Mapa::getVisina()
{
    return visina;
}
float Mapa::getSirina()
{
    return sirina;
}

void Mapa::printPozadina(SDL_Surface *prozor, float visina_prozor, float sirina_prozor)

{
    unsigned int brojac = 0;
    std::string rukopis;

    for (float j = 10; j <= visina_prozor - 10; j+= visina)
    {
        for (float i = 138; i <= sirina_prozor - 138 - sirina; i+= sirina)
        {
            for (int a = 0; a < 2; a+=1)
            {

                    rukopis = MapaText[brojac];
                    if (brojac >= MapaText.size() + 1)
                    {
                        break;
                    }

                    if(rukopis == "4")
                    {
                        apply_surfaceC(i,j,visina,sirina, blokovi, prozor, cigla);
                    }

                    else if(rukopis == "0")
                    {
                        apply_surfaceC(i,j,visina,sirina, blokovi, prozor, trava);
                    }
                    else if(rukopis == "1")
                    {
                        apply_surfaceC(i,j,visina,sirina, blokovi, prozor, kamen);

                    }
                    else if(rukopis == "2")
                    {
                        apply_surfaceC(i,j,visina,sirina, blokovi, prozor, voda);

                    }
                    else if(rukopis == "3")
                    {
                        apply_surfaceC(i,j,visina,sirina, blokovi, prozor, zemlja);

                    }

                    brojac+= 1;
                };
            };

//
        };

}

void Mapa::Sudari(SDL_Surface *prozor, float visina_prozor, float sirina_prozor, std::string tipo)
{
    unsigned int brojac = 0;
    std::string rukopis;
    int num = 0;


    for (float j = 10; j <= visina_prozor - 10; j+= visina)
    {
        for (float i = 138 ; i <= sirina_prozor - 138 -sirina; i+= sirina)
        {
            for (int a = 0; a <= 2; a+=1)
            {
                    brojac+= 1;
                    rukopis = MapaText[brojac];

                    if (brojac >= MapaText.size() + 1)
                    {
                        break;
                    }
                    if(rukopis != "0" && rukopis != "1" && rukopis != "2" && rukopis != "3" && rukopis != "4")
                    {
                        break;
                    }
                    if (rukopis != "0" && rukopis != "3")
                    {
                        if(tipo == "metak" && rukopis == "2")
                        {
                            MapaSudara[num][0] = 0;
                            MapaSudara[num][1] = 0;
                        }
                        else
                        {
                            MapaSudara[num][0] = i;
                            MapaSudara[num][1] = j;
                        }

                        if(rukopis == "4")
                        {
                            MapaSudara[num][2] = 4;
                        }
                        if(rukopis == "1")
                        {
                            MapaSudara[num][2] = 1;
                        }
                        else{MapaSudara[num][2] = 0;}

                        MapaSudara[num][3] = 1;
                        num ++;
                    }

                };
            };


        };

}

bool Mapa::proveraSudara(float xTk, float yTk, float visinaTk, float sirinaTk, std::string parametar)
{

    for(int i = 0; i <= 640; i++)
    {

        if(MapaSudara[i][0] < xTk + sirinaTk && MapaSudara[i][0] + sirina > xTk
           && MapaSudara[i][1] < yTk + visinaTk && MapaSudara[i][1] + visina > yTk)
        {

            return true;
        }

    }
    if(xTk <= 138 || xTk + sirinaTk >=1162|| yTk <= 10 || yTk >= 650 - visinaTk)
    {
        return true;
    }
    return false;
}


Mapa::~Mapa()
{

}
