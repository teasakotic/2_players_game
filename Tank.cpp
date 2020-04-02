#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include "Tank.h"
#include "Tela.h"
#include "Mapa.h"
#include "SDL/SDL_rotozoom.h"


Tank::Tank(int num,SDL_Surface* Prozor, float visina_prozor, float sirina_prozor)
{
    prozor = Prozor;
    player = num;
    if(player == 1)
    {
        tank = load_image("Tank1.png");
        life_cut.x = 0;
    }
    if(player == 2)
    {
        tank = load_image("Tank2.png");
        life_cut.x = 20;

    }

    life_cut.w = 20;
    life_cut.h = 32;
    life_cut.y = 0;

    SDL_SetColorKey(tank, SDL_SRCCOLORKEY, SDL_MapRGB(tank->format,255,255,255));
    tankR = rotozoomSurface(tank, 0,1.0,0);

    boom = load_image("Boom.png");
    SDL_SetColorKey(boom, SDL_SRCCOLORKEY, SDL_MapRGB(boom->format,255,255,255));
    TempoExpFinal = 0;
    TempoExpInicial = 0;

    eksplozija.x = 0;
    eksplozija.y = 0;
    eksplozija.h = 50;
    eksplozija.w = 50;

    life = load_image("Life.png");
    zivotTemp = 5;
    zivot = 5;

    standardne_pozicije[0][0] = 178;
    standardne_pozicije[0][1] = 560;
    standardne_pozicije[0][2] = 0;
    standardne_pozicije[1][0] = 1072;
    standardne_pozicije[1][1] = 50;
    standardne_pozicije[1][2] = 180;


    visina = 50;
    sirina = 50;
    vx = 2;
    vy = 2;
    sudar_cisterne = false;
    uzrok_ostecenje = false;
    if(player == 1)
    {

        x = standardne_pozicije[0][0];
        y = standardne_pozicije[0][1];
        ugao = standardne_pozicije[0][2];

    }
    if(player == 2)
    {

        x = standardne_pozicije[1][0];
        y = standardne_pozicije[1][1];
        ugao = standardne_pozicije[1][2];
    }


    vMetak = 4;
    brojac_metak = 0;
    hMetak = 10;
    wMetak = 10;
    bullet = load_image("Bala.png");
    SDL_SetColorKey(bullet, SDL_SRCCOLORKEY, SDL_MapRGB(bullet->format,255,0,0));
    bulletR = rotozoomSurface(bullet, 0,1.0,0);
    TempoPucanje = 300;
    TempoFinalMetak = 0;
    TempoInicialMetak = 0;

    for(int i = 0; i <= 99; i++)
    {
        metak[i][0] = 0;
        metak[i][1] = 0;
        metak[i][2] = 0;
        sudar_metak1[i][0] = true;
    }

    pozadina.Sudari(Prozor,visina_prozor,sirina_prozor, "metak");
    pozadina.TipPromene();

}


SDL_Surface* Tank::getImagem()
{
    return tank;
}

float Tank::gethMetak()
{
    return hMetak;
}
float Tank::getwMetak()
{
    return wMetak;
}
float Tank::getX()
{
    return x;
}
float Tank::getY()
{
    return y;
}
float Tank::getVisina()
{
    return visina;
}
float Tank::getSirina()
{
    return sirina;
}
void Tank::printTank(SDL_Surface* prozor,float x2,float y2,float h2,float w2)
{
    if(TempoExpInicial == 0)
    {
        apply_surface(x,y,visina,sirina,tankR,prozor);
    }
    else
    {
        TempoExpFinal = SDL_GetTicks();
        if(TempoExpFinal - TempoExpInicial >=200)
        {
            eksplozija.x += 50;
            TempoExpInicial = SDL_GetTicks();

        }
        if(eksplozija.x >= 200)
        {
            TempoExpFinal = 0;
            TempoExpInicial = 0;
            eksplozija.x = 0;
            VratiPoziciju(x2, y2, h2, w2);
        }
        apply_surfaceC(x,y,visina,sirina,boom,prozor, eksplozija);
    }
}
void Tank::VratiPoziciju(float x2,float y2,float h2,float w2)
{
    if(x2 >= 650)
    {
        x = standardne_pozicije[0][0];
        y = standardne_pozicije[0][1];
        ugao = standardne_pozicije[0][2];
        sudariIgraca(x2,y2,h2,w2);
        if(sudar_cisterne)
        {
            x = standardne_pozicije[1][0];
            y = standardne_pozicije[1][1];
            ugao = standardne_pozicije[1][2];
            sudar_cisterne = false;
        }
    }
    else
    {
        x = standardne_pozicije[1][0];
        y = standardne_pozicije[1][1];
        ugao = standardne_pozicije[1][2];
        sudariIgraca(x2,y2,h2,w2);

        if(sudar_cisterne)
        {
            x = standardne_pozicije[0][0];
            y = standardne_pozicije[0][1];
            ugao = standardne_pozicije[0][2];
            sudar_cisterne = false;
        }

    }

}
void Tank::printMetak()
{
    for(int i = 0; i <= 99; i++)
    {
        if(metak[i][0] != 0 && metak[i][1] != 0)
        {
            bulletR = rotozoomSurface(bullet,metak[i][2],1.0,0);
            apply_surface(metak[i][0],metak[i][1],20,20,bulletR,prozor);
        }
    }

}
void Tank::printLife(float visina_prozor, float sirina_prozor)
{
    if(player == 1)
    {
        clean_surface(prozor,0,0,visina_prozor, 138);
        clean_surface(prozor,sirina_prozor-138,0,visina_prozor, 138);
        float posx = 118;
        for(float i = 0; i < zivot; i++)
        {
            apply_surfaceC(posx,50,life_cut.h,life_cut.w,life,prozor, life_cut);
            posx -= 29;
        }

    }
    if(player == 2)
    {
        float posx = sirina_prozor-138;
        for(float i = 0; i< zivot; i++)
        {
            apply_surfaceC(posx,50,life_cut.h,life_cut.w,life,prozor, life_cut);
            posx += 29;
        }

    }

}
void Tank::moveMetak()
{
    for(int i = 0; i <= 99; i++)
    {
        if(metak[i][0] != 0 && metak[i][1] != 0)
        {
            clean_surface(prozor,metak[i][0],metak[i][1],hMetak,wMetak+1);

            if(metak[i][2] == 0)
            {
                metak[i][1] -= vMetak;
            }
            else if(metak[i][2] == 180)
            {
                metak[i][1] += vMetak;
            }
            else if(metak[i][2] == 90)
            {
                metak[i][0] -= vMetak;
            }
            else if(metak[i][2] == 270)
            {
                metak[i][0] += vMetak;
            }

            if(sudar_metak1[i][0])
            {
                sudar_metak1[i][0] = false;
                metak[i][0] = 0;
                metak[i][1] = 0;
            }

            if(pozadina.proveraSudara(metak[i][0], metak[i][1], hMetak, wMetak,"metak"))
            {

                metak[i][0] = 0;
                metak[i][1] = 0;
                break;
            }
        }
    }

}

void Tank::sudarMetak(float x2, float y2, float h2, float w2)
{

    uzrok_ostecenje = false;
    for(int i = 0; i<=99; i++)
    {
        if( metak[i][0]<= x2 + w2 && metak[i][0] + wMetak >= x2 && metak[i][1] <= y2 + h2 && metak[i][1] + hMetak >= y2)
        {
            sudar_metak1[i][0] = true;
            uzrok_ostecenje = true;
            break;

        }
        else
        {
            sudar_metak1[i][0] = false;
        }

    }

}

bool Tank::getUzrok_ostecenje()
{
    return uzrok_ostecenje;
}
void Tank::sudariIgraca(float x2, float y2, float h2, float w2)
{
    if(x < x2 + w2 && x + sirina > x2 && y < y2 + h2 && y + visina > y2)
    {
        sudar_cisterne = true;
    }
    else
    {
        sudar_cisterne = false;
    }

}

void Tank::move(float visina_prozor, float sirina_prozor, Uint8 *kljuc,
                float visinaBlok, float sirinaBlok, bool sudar,
                float x2, float y2, float h2, float w2
                )
{
    clean_surface(prozor,x,y,visina,sirina);
    sudariIgraca(x2,y2,h2,w2);
    TempoFinalMetak = SDL_GetTicks();
    float deltaTempo;
    if(TempoExpInicial == 0)
    {

        if(TempoInicialMetak == 0)
        {
            deltaTempo = TempoPucanje + 1;
        }
        else
        {
            deltaTempo = TempoFinalMetak - TempoInicialMetak;
        }


        if(kljuc[SDLK_2] )
        {
            vy = 1.1*vy;
            vx = 1.1*vx;
            vMetak = 1.1*vMetak;
        }
        if(kljuc[SDLK_1] )
        {
            vy = vy/1.1;
            vx = vx/1.1;
            vMetak = 1.1/vMetak;
        }
        if(kljuc[SDLK_3] )
        {
            vy = 2;
            vx = 2;
            vMetak = 3;
        }
        if(kljuc[SDLK_r])
        {

            ugao += 90;
            tankR = rotozoomSurface(tank, ugao,1.0,2);

        }
        if(kljuc[SDLK_4] )
        {
            zivot = 5;
            zivotTemp = 5;
        }
        if (player == 2)
        {
            if(kljuc[SDLK_RETURN] && deltaTempo >= TempoPucanje)
            {

                TempoInicialMetak = SDL_GetTicks();
                TempoFinalMetak = 0;
                deltaTempo = 0;

                if(ugao == 0)
                {
                    metak[brojac_metak][0] = x + sirina/2 - wMetak/2;
                    metak[brojac_metak][1] = y - hMetak;
                    metak[brojac_metak][2] = 0;
                }
                else if(ugao == 90)
                {
                    metak[brojac_metak][0] = x - hMetak;
                    metak[brojac_metak][1] = y + visina/2 - wMetak/2;
                    metak[brojac_metak][2] = 90;
                }
                else if(ugao == 180)
                {
                    metak[brojac_metak][0] = x + sirina/2 - wMetak/2;
                    metak[brojac_metak][1] = y + visina;
                    metak[brojac_metak][2] = 180;
                }
                else if(ugao == 270)
                {
                    metak[brojac_metak][0] = x + sirina;
                    metak[brojac_metak][1] = y + visina/2 - wMetak/2;
                    metak[brojac_metak][2] = 270;
                }
                if(brojac_metak >= 99)
                {
                    brojac_metak = -1;
                }

                brojac_metak += 1;

            }
            if(kljuc[SDLK_UP] )
            {
                ugao = 0;
                y -= vy;
                sudariIgraca(x2,y2,h2,w2);
                if(sudar == 1)
                {
                    y += 2*vy;

                }
                if(sudar_cisterne)
                {
                    y = y2 + h2;
                }
            }
                else if(kljuc[SDLK_DOWN] )
                {
                    ugao = 180;
                    y += vy;
                    sudariIgraca(x2,y2,h2,w2);
                    if(sudar == 1)
                    {
                        y -= 2*vy;
                    }
                    if(sudar_cisterne)
                    {
                        y = y2 - visina;
                    }

                }
                else if(kljuc[SDLK_LEFT] )
                {
                    ugao = 90;
                    x -= vx;
                    sudariIgraca(x2,y2,h2,w2);
                    if(sudar == 1)
                    {
                        x += 2*vx;
                    }
                    if(sudar_cisterne)
                    {
                        x = x2 + w2;
                    }

                }
                else if(kljuc[SDLK_RIGHT] )
                {
                    ugao = 270;
                    x += vx;
                    sudariIgraca(x2,y2,h2,w2);
                    if(sudar == 1)
                    {
                        x -= 2*vx;
                    }
                    if(sudar_cisterne)
                    {
                        x = x2 - sirina;
                    }

                }

    }

        if (player == 1)
    {
        if(kljuc[SDLK_SPACE] && deltaTempo >= TempoPucanje)
        {

            TempoInicialMetak = SDL_GetTicks();
            TempoFinalMetak = 0;
            deltaTempo = 0;

            if(ugao == 0)
            {
                metak[brojac_metak][0] = x + sirina/2 - wMetak/2;
                metak[brojac_metak][1] = y - hMetak;
                metak[brojac_metak][2] = 0;
            }
            else if(ugao == 90)
            {
                metak[brojac_metak][0] = x - hMetak;
                metak[brojac_metak][1] = y + visina/2 - wMetak/2;
                metak[brojac_metak][2] = 90;
            }
            else if(ugao == 180)
            {
                metak[brojac_metak][0] = x + sirina/2 - wMetak/2;
                metak[brojac_metak][1] = y + visina;
                metak[brojac_metak][2] = 180;
            }
            else if(ugao == 270)
            {
                metak[brojac_metak][0] = x + sirina;
                metak[brojac_metak][1] = y + visina/2 - wMetak/2;
                metak[brojac_metak][2] = 270;
            }
            if(brojac_metak >= 99)
            {
                brojac_metak = -1;
            }

            brojac_metak += 1;

        }
        if(kljuc[SDLK_w] )
        {
            ugao = 0;
            y -= vy;
            sudariIgraca(x2,y2,h2,w2);
            if(sudar == 1)
            {
                y += 2*vy;
            }
            if(sudar_cisterne)
            {
                y = y2 + visina;
            }
        }
            else if(kljuc[SDLK_s] )
            {
                ugao = 180;
                y += vy;
                sudariIgraca(x2,y2,h2,w2);
                if(sudar == 1)
                {
                    y -= 2*vy;
                }
                if(sudar_cisterne)
                {
                    y = y2 - h2;
                }

            }
            else if(kljuc[SDLK_a] )
            {
                ugao = 90;
                x -= vx;
                sudariIgraca(x2,y2,h2,w2);
                if(sudar == 1)
                {
                    x += 2*vx;
                }
                if(sudar_cisterne)
                {
                    x = x2 + w2;
                }

            }
            else if(kljuc[SDLK_d] )
            {
                ugao = 270;
                x += vx;
                sudariIgraca(x2,y2,h2,w2);
                if(sudar == 1)
                {
                    x -= 2*vx;
                }
                if(sudar_cisterne)
                {
                    x = x2  - sirina;
                }

            }

    }
    tankR = rotozoomSurface(tank, ugao,1.0,0);

    }
}

void Tank::dovodi_ostecenje(bool ostecenje)
{
    if(ostecenje && TempoExpInicial == 0)
    {
        zivotTemp -= 1;
        if(zivotTemp <= 0)
        {
            TempoExpInicial = SDL_GetTicks();
            zivot --;

            zivotTemp = 5;
        }

    }

}
Tank::~Tank()
{

}
