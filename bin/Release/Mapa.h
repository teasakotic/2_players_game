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
        void printFundo(SDL_Surface *janela, float altura_janela, float largura_janela);
        void Colisoes(SDL_Surface *janela, float altura_janela, float largura_janela, std::string tipo);
        bool verificaColisao(float xTk, float yTk, float alturaTk, float larguraTk, std::string parametro);
        float getAltura();
        float getLargura();
        void MudaTipo();
        int dano;
        void mandadano(int n, int numdano);


    protected:
    private:
    //SDL_Surface *grama;

    SDL_Surface* blocos;
    SDL_Rect grama;
    SDL_Rect pedra;
    SDL_Rect agua;
    SDL_Rect tijolo;
    SDL_Rect terra;
    int altura;
    int largura;
    //SDL_Surface *pedra;
    std::string MapaTexto;
    std::string linhaTemp;//linha temporaria
    std::ifstream map;
    float MapadeColisao[640][4];
    void printTijolo(SDL_Surface* janela, float i, float j);
    std::string Tipo;//verifica se o objeto foi criado pela classe tank

};

#endif // MAPA_H
