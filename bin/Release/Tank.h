#ifndef TANK_H
#define TANK_H
#include <string>
#include "Tela.h"
#include "Mapa.h"
#include <SDL/SDL.h>



class Tank: public Tela
{
    public:
        Tank(int num, SDL_Surface* Janela,float altura_janela, float largura_janela);
        virtual ~Tank();
        void move(float altura_janela, float largura_janela, Uint8 *tecla,
                float alturaBloco, float larguraBloco, bool colisao,
                float x2, float y2, float h2, float w2
                );

        float getX();
        float getY();
        float getAltura();
        float getLargura();
        float gethBala();
        float getwBala();
        SDL_Surface* getImagem();
        void printTank(SDL_Surface* janela, float x2,float y2,float h2,float w2);
        void colisaoJogadores(float x2, float y2, float h2, float w2);
        void printbala();
        void moveBala();
        void colisaoBala(float x2, float y2, float h2, float w2);
        void leva_dano(bool dano);
        bool getCausa_dano();
        void printLife(float altura_janela, float largura_janela);
        int dano;


    protected:
    private:
    int vidaTemp;
    int vida;
    struct e;
    SDL_Surface* life;
    SDL_Rect life_cut;
    bool causa_dano;
    float posicoes_padrao[2][3];
    float bala[100][3];
    bool colisao_bala1[100][1];
   // bool colisao_bala2[100][1];
    int contador_bala;
    float vBala;
    float hBala;
    float wBala;
    SDL_Surface* bullet;
    SDL_Surface* bulletR;
    SDL_Surface *tank;
    float altura;
    float largura;
    float x;
    float y;
    float vx;
    float vy;
    int player;
    SDL_Rect tankReal;
    int angulo;
    SDL_Surface* tankR;
    bool colisao_tanks;
    Mapa fundo;
    float TempoInicialBala;
    float TempoFinalBala;
    float TempoDeTiro;
    SDL_Surface* boom;
    SDL_Rect explosao;
    SDL_Surface* janela;
    float TempoExpInicial;
    float TempoExpFinal;
    void RestauraPosicao(float x2,float y2,float h2,float w2);



};

#endif // TANK_H
