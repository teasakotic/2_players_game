#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>
#include <fstream>
#include "Tank.h"
#include "Tela.h"
#include "Mapa.h"
#include "SDL/SDL_rotozoom.h"


Tank::Tank(int num,SDL_Surface* Janela, float altura_janela, float largura_janela)
{
    janela = Janela;
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
    TempoExpFinal = 0;//tempo de explosao final
    TempoExpInicial = 0;//tempo de explosao inicial

    explosao.x = 0;
    explosao.y = 0;
    explosao.h = 50;
    explosao.w = 50;

    life = load_image("Life.png");
    vidaTemp = 5;
    vida = 5;
    //0 - x, 1 - y, 2 - angulo
    posicoes_padrao[0][0] = 178;
    posicoes_padrao[0][1] = 560;
    posicoes_padrao[0][2] = 0;
    posicoes_padrao[1][0] = 1072;
    posicoes_padrao[1][1] = 50;
    posicoes_padrao[1][2] = 180;


    altura = 50;
    largura = 50;
    vx = 2;
    vy = 2;
    colisao_tanks = false;
    causa_dano = false;
    if(player == 1)
    {

        x = posicoes_padrao[0][0];
        y = posicoes_padrao[0][1];
        angulo = posicoes_padrao[0][2];

    }
    if(player == 2)
    {

        x = posicoes_padrao[1][0];
        y = posicoes_padrao[1][1];
        angulo = posicoes_padrao[1][2];
    }

    //bala
    vBala = 4;
    contador_bala = 0;
    hBala = 10;
    wBala = 10;
    bullet = load_image("Bala.png");
    SDL_SetColorKey(bullet, SDL_SRCCOLORKEY, SDL_MapRGB(bullet->format,255,0,0));
    bulletR = rotozoomSurface(bullet, 0,1.0,0);
    TempoDeTiro = 300;
    TempoFinalBala = 0;
    TempoInicialBala = 0;

    for(int i = 0; i <= 99; i++)
    {
        bala[i][0] = 0;
        bala[i][1] = 0;
        bala[i][2] = 0;
        colisao_bala1[i][0] = true;
    }

    fundo.Colisoes(Janela,altura_janela,largura_janela, "bala");
    fundo.MudaTipo();

}


SDL_Surface* Tank::getImagem()
{
    return tank;
}

float Tank::gethBala()
{
    return hBala;
}
float Tank::getwBala()
{
    return wBala;
}
float Tank::getX()
{
    return x;
}
float Tank::getY()
{
    return y;
}
float Tank::getAltura()
{
    return altura;
}
float Tank::getLargura()
{
    return largura;
}
void Tank::printTank(SDL_Surface* janela,float x2,float y2,float h2,float w2)
{
    //apply_surfaceC(x,y,altura,largura,tankR,janela,tankReal);//TANKR -> TANK//
    //fundo.printFundo(janela, 660, 1330);
    if(TempoExpInicial == 0)
    {
        apply_surface(x,y,altura,largura,tankR,janela);
    }
    else
    {
        TempoExpFinal = SDL_GetTicks();
        if(TempoExpFinal - TempoExpInicial >=200)
        {
            explosao.x += 50;
            TempoExpInicial = SDL_GetTicks();

        }
        if(explosao.x >= 200)
        {
            TempoExpFinal = 0;
            TempoExpInicial = 0;
            explosao.x = 0;
            RestauraPosicao(x2, y2, h2, w2);
        }
        apply_surfaceC(x,y,altura,largura,boom,janela, explosao);
    }
}
void Tank::RestauraPosicao(float x2,float y2,float h2,float w2)
{
    if(x2 >= 650)
    {
        x = posicoes_padrao[0][0];
        y = posicoes_padrao[0][1];
        angulo = posicoes_padrao[0][2];
        colisaoJogadores(x2,y2,h2,w2);
        if(colisao_tanks)
        {
            x = posicoes_padrao[1][0];
            y = posicoes_padrao[1][1];
            angulo = posicoes_padrao[1][2];
            colisao_tanks = false;
        }
    }
    else
    {
        x = posicoes_padrao[1][0];
        y = posicoes_padrao[1][1];
        angulo = posicoes_padrao[1][2];
        colisaoJogadores(x2,y2,h2,w2);

        if(colisao_tanks)
        {
            x = posicoes_padrao[0][0];
            y = posicoes_padrao[0][1];
            angulo = posicoes_padrao[0][2];
            colisao_tanks = false;
        }

    }





}
void Tank::printbala()
{
    for(int i = 0; i <= 99; i++)
    {
        if(bala[i][0] != 0 && bala[i][1] != 0)
        {
            bulletR = rotozoomSurface(bullet,bala[i][2],1.0,0);
            apply_surface(bala[i][0],bala[i][1],20,20,bulletR,janela);
        }
    }

}
void Tank::printLife(float altura_janela, float largura_janela)
{
    if(player == 1)
    {   //138 eh onde começa o mapa
        clean_surface(janela,0,0,altura_janela, 138);
        clean_surface(janela,largura_janela-138,0,altura_janela, 138);
        float posx = 118;
        for(float i = 0; i < vida; i++)
        {
            apply_surfaceC(posx,50,life_cut.h,life_cut.w,life,janela, life_cut);
            posx -= 29;
        }

    }
    if(player == 2)
    {
        float posx = largura_janela-138;
        for(float i = 0; i< vida; i++)
        {
            apply_surfaceC(posx,50,life_cut.h,life_cut.w,life,janela, life_cut);
            posx += 29;
        }

    }

}
void Tank::moveBala()
{
    for(int i = 0; i <= 99; i++)
    {
        if(bala[i][0] != 0 && bala[i][1] != 0)
        {
            clean_surface(janela,bala[i][0],bala[i][1],hBala,wBala+1);

            if(bala[i][2] == 0)
            {
                bala[i][1] -= vBala;
            }
            else if(bala[i][2] == 180)
            {
                bala[i][1] += vBala;
            }
            else if(bala[i][2] == 90)
            {
                bala[i][0] -= vBala;
            }
            else if(bala[i][2] == 270)
            {
                bala[i][0] += vBala;
            }
            //colisao com o jogador
            if(colisao_bala1[i][0])
            {
                colisao_bala1[i][0] = false;
                bala[i][0] = 0;
                bala[i][1] = 0;
            }
            //colisao com o fundo
            if(fundo.verificaColisao(bala[i][0], bala[i][1], hBala, wBala,"bala"))
            {

                bala[i][0] = 0;
                bala[i][1] = 0;
                break;
            }
        }
    }

}

void Tank::colisaoBala(float x2, float y2, float h2, float w2)
{
    //colisao da bala com o jogador
    causa_dano = false;
    for(int i = 0; i<=99; i++)
    {
        if( bala[i][0]<= x2 + w2 && bala[i][0] + wBala >= x2 && bala[i][1] <= y2 + h2 && bala[i][1] + hBala >= y2)
        {
            colisao_bala1[i][0] = true;
            causa_dano = true;
            break;

        }
        else
        {
            colisao_bala1[i][0] = false;
        }

    }

}

bool Tank::getCausa_dano()
{
    return causa_dano;
}
void Tank::colisaoJogadores(float x2, float y2, float h2, float w2)
{
    if(x < x2 + w2 && x + largura > x2 && y < y2 + h2 && y + altura > y2)
    {
        colisao_tanks = true;
    }
    else
    {
        colisao_tanks = false;
    }

}

void Tank::move(float altura_janela, float largura_janela, Uint8 *tecla,
                float alturaBloco, float larguraBloco,bool colisao,
                float x2, float y2, float h2, float w2
                )
{
    clean_surface(janela,x,y,altura,largura);
    colisaoJogadores(x2,y2,h2,w2);
    TempoFinalBala = SDL_GetTicks();
    float deltaTempo;
    if(TempoExpInicial == 0)
    {//tempoexpinicial == 0 para nao andar enquanto explode

        if(TempoInicialBala == 0)
        {
            deltaTempo = TempoDeTiro + 1;
        }
        else
        {
            deltaTempo = TempoFinalBala - TempoInicialBala;
        }


        if(tecla[SDLK_2] )
        {
            vy = 1.1*vy;
            vx = 1.1*vx;
            vBala = 1.1*vBala;
        }
        if(tecla[SDLK_1] )
        {
            vy = vy/1.1;
            vx = vx/1.1;
            vBala = 1.1/vBala;
        }
        if(tecla[SDLK_3] )
        {
            vy = 2;
            vx = 2;
            vBala = 3;
        }
        if(tecla[SDLK_r])
        {

            angulo += 90;
            tankR = rotozoomSurface(tank, angulo,1.0,2);

        }
        if(tecla[SDLK_4] )
        {
            vida = 5;
            vidaTemp = 5;
        }
        if (player == 2)
        {//////////////USAR DIFERENCA DE TEMPO: SE FOR MAIOR QUE X, PODE ATIRAR////////////////
            if(tecla[SDLK_RETURN] && deltaTempo >= TempoDeTiro)
            {

                TempoInicialBala = SDL_GetTicks();
                TempoFinalBala = 0;
                deltaTempo = 0;

                if(angulo == 0)
                {
                    bala[contador_bala][0] = x + largura/2 - wBala/2;
                    bala[contador_bala][1] = y - hBala;
                    bala[contador_bala][2] = 0;
                }
                else if(angulo == 90)
                {
                    bala[contador_bala][0] = x - hBala;
                    bala[contador_bala][1] = y + altura/2 - wBala/2;
                    bala[contador_bala][2] = 90;
                }
                else if(angulo == 180)
                {
                    bala[contador_bala][0] = x + largura/2 - wBala/2;
                    bala[contador_bala][1] = y + altura;
                    bala[contador_bala][2] = 180;
                }
                else if(angulo == 270)
                {
                    bala[contador_bala][0] = x + largura;
                    bala[contador_bala][1] = y + altura/2 - wBala/2;
                    bala[contador_bala][2] = 270;
                }
                if(contador_bala >= 99)
                {
                    contador_bala = -1;
                }

                contador_bala += 1;

            }
            if(tecla[SDLK_UP] )
            {
                angulo = 0;
                y -= vy;
                colisaoJogadores(x2,y2,h2,w2);
                if(colisao == 1)
                {
                    y += 2*vy;

                }
                if(colisao_tanks)
                {
                    y = y2 + h2;
                }
            }
                else if(tecla[SDLK_DOWN] )
                {
                    angulo = 180;
                    y += vy;
                    colisaoJogadores(x2,y2,h2,w2);
                    if(colisao == 1)
                    {
                        y -= 2*vy;
                    }
                    if(colisao_tanks)
                    {
                        y = y2 - altura;
                    }

                }
                else if(tecla[SDLK_LEFT] )
                {
                    angulo = 90;
                    x -= vx;
                    colisaoJogadores(x2,y2,h2,w2);
                    if(colisao == 1)
                    {
                        x += 2*vx;
                    }
                    if(colisao_tanks)
                    {
                        x = x2 + w2;
                    }

                }
                else if(tecla[SDLK_RIGHT] )
                {
                    angulo = 270;
                    x += vx;
                    colisaoJogadores(x2,y2,h2,w2);
                    if(colisao == 1)
                    {
                        x -= 2*vx;
                    }
                    if(colisao_tanks)
                    {
                        x = x2 - largura;
                    }

                }

    }

        if (player == 1)
    {
        if(tecla[SDLK_SPACE] && deltaTempo >= TempoDeTiro)
        {

            TempoInicialBala = SDL_GetTicks();
            TempoFinalBala = 0;
            deltaTempo = 0;

            if(angulo == 0)
            {
                bala[contador_bala][0] = x + largura/2 - wBala/2;
                bala[contador_bala][1] = y - hBala;
                bala[contador_bala][2] = 0;
            }
            else if(angulo == 90)
            {
                bala[contador_bala][0] = x - hBala;
                bala[contador_bala][1] = y + altura/2 - wBala/2;
                bala[contador_bala][2] = 90;
            }
            else if(angulo == 180)
            {
                bala[contador_bala][0] = x + largura/2 - wBala/2;
                bala[contador_bala][1] = y + altura;
                bala[contador_bala][2] = 180;
            }
            else if(angulo == 270)
            {
                bala[contador_bala][0] = x + largura;
                bala[contador_bala][1] = y + altura/2 - wBala/2;
                bala[contador_bala][2] = 270;
            }
            if(contador_bala >= 99)
            {
                contador_bala = -1;
            }

            contador_bala += 1;

        }
        if(tecla[SDLK_w] )
        {
            angulo = 0;
            y -= vy;
            colisaoJogadores(x2,y2,h2,w2);
            if(colisao == 1)
            {
                y += 2*vy;
            }
            if(colisao_tanks)
            {
                y = y2 + altura;
            }
        }
            else if(tecla[SDLK_s] )
            {
                angulo = 180;
                y += vy;
                colisaoJogadores(x2,y2,h2,w2);
                if(colisao == 1)
                {
                    y -= 2*vy;
                }
                if(colisao_tanks)
                {
                    y = y2 - h2;
                }

            }
            else if(tecla[SDLK_a] )
            {
                angulo = 90;
                x -= vx;
                colisaoJogadores(x2,y2,h2,w2);
                if(colisao == 1)
                {
                    x += 2*vx;
                }
                if(colisao_tanks)
                {
                    x = x2 + w2;
                }

            }
            else if(tecla[SDLK_d] )
            {
                angulo = 270;
                x += vx;
                colisaoJogadores(x2,y2,h2,w2);
                if(colisao == 1)
                {
                    x -= 2*vx;
                }
                if(colisao_tanks)
                {
                    x = x2  - largura;
                }

            }

    }
    tankR = rotozoomSurface(tank, angulo,1.0,0);

    }
}

void Tank::leva_dano(bool dano)
{
    if(dano && TempoExpInicial == 0)
    {//tempoexpinicial == 0 para nao tomar dano enquanto explode
        vidaTemp -= 1;
        if(vidaTemp <= 0)
        {
            TempoExpInicial = SDL_GetTicks();
            vida --;
            //se vida == 0, mostra mensagem
            vidaTemp = 5;
        }

    }

}
Tank::~Tank()
{
    //dtor
}
