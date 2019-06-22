#ifndef _AET__
#define _AET__

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include <algorithm>
#include <math.h>

using namespace std;

// classe para definir arestas do poligono e seus respectivos valores xy
class arestas {
    public:
        //valores xmin,xmax,ymin,ymax para calculo da inclinacao
        int ymin;
        int ymax;
        int xmin;
        int xmax;
        float xval; //valor de x do vertice de ymin, ou seja xmin
        float inclinacao;//inclinacao da aresta para calculo das linhas de varredura

        // define tuplas de vertices para aresta
        arestas(tuple<int, int> vertice1, tuple<int, int> vertice2);
};

// preenche pixels para bloco da scanline
void desenhaPixel(float x1, float x2);
// remove arestas da AET se ymax = y da varredura
void removerAET();
//atualia o valor de xval(inicialmente x do ymin) xval + 1/m
void atualizaXval();
// adiciona novas arestas(AET) a partir da tabela de arestas ET caso ymin = y
void atualizaAET();
//inicializa linha de varredura
void inicializaAlgVarredura();
// ordena arestas para saber quais arestas a linha de varredura intercepta
void ordenar_e_preencherArestas_ET();
//ordena AET pelo valor de x = xmin
void ordenaAETxval();
// encontra as interseccoes da linha de varredura, preenche o bloco e atualiza
void preencherPoligono();
//cria pontos que foram desenhados na tela(enquanto nao esta conectado com a interface)
void criarET(vector<float> input);

vector<float> PoliFill(vector<float> input_coordinates);



#endif
