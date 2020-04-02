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
  //  grama = load_image("grama.png");
  //  pedra = load_image("pedra.png");
    blocos = load_image("Blocos.png");
    altura = 32;
    largura = 32;

    grama.x = 0;
    grama.y = 0;
    grama.h = 32;
    grama.w = 32;

    pedra.x = 32;
    pedra.y = 0;
    pedra.h = 32;
    pedra.w = 32;

    agua.x = 0;
    agua.y = 32;
    agua.h = 32;
    agua.w = 32;

    tijolo.x = 0;
    tijolo.y = 64;
    tijolo.h = 32;
    tijolo.w = 32;

    terra.x = 32;
    terra.y = 32;
    terra.h = 32;
    terra.w = 32;


    map.open("mapa.txt");

    if (map.is_open())
    {
        while(map.good())
        {
            getline(map, linhaTemp);
            MapaTexto += linhaTemp ;

        }
        map.close();
    }

}

void Mapa::MudaTipo()
{
    Tipo = "bala";
}
float Mapa::getAltura()
{
    return altura;
}
float Mapa::getLargura()
{
    return largura;
}

void Mapa::printFundo(SDL_Surface *janela, float altura_janela, float largura_janela)

{
    unsigned int contador = 0;
    std::string letra;

    for (float j = 10; j <= altura_janela - 10; j+= altura)
    {
        for (float i = 138; i <= largura_janela - 138 - largura; i+= largura)
        {
            for (int a = 0; a < 2; a+=1)
            {

                    letra = MapaTexto[contador];
                    if (contador >= MapaTexto.size() + 1)
                    {
                        break;
                    }

                    if(letra == "4")
                    {
                        apply_surfaceC(i,j,altura,largura, blocos, janela, terra);
                        printTijolo( janela, i, j);
                    }

                    else if(letra == "0")
                    {
                        //apply_surface(i,j,altura,largura, grama, janela);
                        apply_surfaceC(i,j,altura,largura, blocos, janela, grama);
                    }
                    else if(letra == "1")
                    {
                        //apply_surface(i,j,altura,largura, pedra, janela);
                        apply_surfaceC(i,j,altura,largura, blocos, janela, pedra);

                    }
                    else if(letra == "2")
                    {
                        //apply_surface(i,j,altura,largura, pedra, janela);
                        apply_surfaceC(i,j,altura,largura, blocos, janela, agua);

                    }
                    else if(letra == "3")
                    {
                        //apply_surface(i,j,altura,largura, pedra, janela);
                        apply_surfaceC(i,j,altura,largura, blocos, janela, terra);

                    }

                    contador+= 1;
                };
            };

//
        };

}

void Mapa::printTijolo(SDL_Surface* janela, float i, float j)
{

    SDL_Rect posicao;
    posicao.h = 32;
    posicao.w = 32;
    for(int n = 0; n <= 640; n++)
    {
        if(MapadeColisao[n][0] == i && MapadeColisao[n][1] == j)
        {

            if(MapadeColisao[n][3] <= 1)
            {
                posicao.x = 0;
                posicao.y = 64;
                dano = 1;
            }
            else if(MapadeColisao[n][3] == 2)
            {
                posicao.x = 32;
                posicao.y = 64;
                dano = 2;
            }
            else if(MapadeColisao[n][3] == 3)
            {
                posicao.x = 0;
                posicao.y = 96;
                dano = 3;
            }
            else if(MapadeColisao[n][3] == 4)
            {
                posicao.x = 32;
                posicao.y = 96;
                dano = 4;
            }
            else if(MapadeColisao[n][3] == 5)
            {
                posicao.x = 0;
                posicao.y = 128;
                dano = 5;
            }
            else if(MapadeColisao[n][3] == 6)
            {
                posicao.x = 32;
                posicao.y = 128;
                dano = 6;
            }
            else
            {
                posicao.x = 32;
                posicao.y = 32;
                dano = 7;
            }
            break;
        }
    }
    //SDL_FillRect(janela, &posicao, NULL);
    apply_surfaceC(i,j,altura,largura, blocos, janela, posicao);
}

void Mapa::Colisoes(SDL_Surface *janela, float altura_janela, float largura_janela, std::string tipo)
{
    unsigned int contador = 0;
    std::string letra;
    int num = 0;//numero do indice no array


    for (float j = 10; j <= altura_janela - 10; j+= altura)
    {
        for (float i = 138 ; i <= largura_janela - 138 -largura; i+= largura)
        {
            for (int a = 0; a <= 2; a+=1)
            {
                    contador+= 1;
                    letra = MapaTexto[contador];

                    if (contador >= MapaTexto.size() + 1)
                    {
                        break;
                    }
                    if(letra != "0" && letra != "1" && letra != "2" && letra != "3" && letra != "4")
                    {
                        break;
                    }
                    if (letra != "0" && letra != "3")
                    {
                        if(tipo == "bala" && letra == "2")//colisao com a agua
                        {
                            //continue;
                            MapadeColisao[num][0] = 0;
                            MapadeColisao[num][1] = 0;
                        }
                        else
                        {
                            MapadeColisao[num][0] = i;
                            MapadeColisao[num][1] = j;
                        }

                        if(letra == "4")
                        {
                            MapadeColisao[num][2] = 4;//tijolo
                        }
                        if(letra == "1")
                        {
                            MapadeColisao[num][2] = 1;//pedra
                        }
                        else{MapadeColisao[num][2] = 0;}

                        MapadeColisao[num][3] = 1;//numero de colisoes
                        num ++;
                    }

                };
            };


        };

}

bool Mapa::verificaColisao(float xTk, float yTk, float alturaTk, float larguraTk, std::string parametro)
{

    for(int i = 0; i <= 640; i++)
    {
        //tanque entra por cima
        if(MapadeColisao[i][0] < xTk + larguraTk && MapadeColisao[i][0] + largura > xTk
           && MapadeColisao[i][1] < yTk + alturaTk && MapadeColisao[i][1] + altura > yTk)
        {

            return true;
        }

    }
    if(xTk <= 138 || xTk + larguraTk >=1162|| yTk <= 10 || yTk >= 650 - alturaTk)
    {
        return true;
    }
    return false;
}

void Mapa::mandadano(int n, int numdano)
{
    MapadeColisao[n][3] = numdano;
}

Mapa::~Mapa()
{
    //dtor
}
