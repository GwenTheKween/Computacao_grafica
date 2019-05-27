#include "AET.h"

#define width 500
#define height 500

// calcular valores dos vertices para AET sempre considerando uma tupla de 2 vertices, ou seja, uma aresta
arestas::arestas(tuple<int, int> vertice1, tuple<int, int> vertice2) {
    this->ymin = min(get<1>(vertice1), get<1>(vertice2)); //pega menor y entre y1 e y2
    this->ymax = max(get<1>(vertice1), get<1>(vertice2)); //pega maior y entre y1 e y2
    this->xmin = min(get<0>(vertice1), get<0>(vertice2)); //pega menor x entre x1 e x2
    this->xmax = max(get<0>(vertice1), get<0>(vertice2)); //pega maior x entre x1 e x2

    
    //pega o valor de x do vertice de ymin, ou seja o x do menor vertice da aresta
    if (min(get<1>(vertice1), get<1>(vertice2)) == get<1>(vertice1)) {
        this->xval = get<0>(vertice1);
    } else {
        this->xval = get<0>(vertice2);
    }

    // calcula inclinacao da aresta, como os valores dos vertices sao do tipo int eh necessario utilizar a funcao static_cast<float> para retornar o valor float corretamente
    this->inclinacao = static_cast<float>(static_cast<float>(get<1>(vertice1) - get<1>(vertice2))) / static_cast<float>((get<0>(vertice1) - get<0>(vertice2)));
}

// ordena arestas pelo valor de ymin, em caso de ymin iguais ordena por xmin
struct ordenaymin {
    inline bool operator() (const arestas& struct1, const arestas& struct2) {
        if (struct1.ymin != struct2.ymin)
            return (struct1.ymin < struct2.ymin);
        return (struct1.xmin < struct2.xmin);
    }
};

//ordena pelo valor de xmin
struct ordenaXmin {
    inline bool operator() (const arestas& struct1, const arestas& struct2) {
        return (struct1.xval < struct2.xval);
    }
};

//------ VARIAVEIS GLOBAIS ------
int varredura;
bool paridade;
vector<tuple<int, int>> pontos; // vertices
vector<float> pixelsInternos; //pixels de preenchimento do poligono
vector<arestas> ET; // todas as arestas
vector<arestas> AET; // arestas de interseccao da linha de varredura
//-------------------------------

// preenche pixels para bloco da scanline
void desenhaPixel(float x1, float x2) {
    // arredonda valores de x
    int i1 = roundf(x1);
    int i2 = roundf(x2);
    int count = 0;
    float x,y;
    
    //preenche o bloco da linha de varredura de x1 ate x2
    for (int i = ((height * (width - varredura)) + i1); i < ((height * (width - varredura)) + i2); i++, count++) {
        //pixelsInternos.push_back(tuple<int, int>((i1 + count), varredura));
        x = (float) i1 + count;
        y = (float) varredura;
        pixelsInternos.push_back((float)x);
        pixelsInternos.push_back((float)y);
    }
}

// remove arestas da AET se ymax = y da varredura
void removerAET() {
    //para cada aresta no vetor EAT
    for (vector<arestas>::iterator it = AET.begin(); it < AET.end(); ) {
        if (it->ymax == varredura) {
            AET.erase(it);
        } else {
            it++;
        }
    }
}

//atualia o valor de xval(inicialmente x do ymin) xval + 1/m
void atualizaXval() {
    for (vector<arestas>::iterator it = AET.begin(); it < AET.end(); it++) {
        it->xval += (1/it->inclinacao);
    }
}

// adiciona novas arestas(AET) a partir da tabela de arestas ET caso ymin = y
void atualizaAET() {
    for (vector<arestas>::iterator it = ET.begin(); it < ET.end(); it++) {
        if (it->ymin == varredura) {
            AET.push_back(*it);
        }
        if (it->ymin > varredura) {
            return;
        }
    }
}

//inicializa linha de varredura
void inicializaAlgVarredura() {
    if (ET.size() != 0) {
        varredura = ET.at(0).ymin;
    }
}

// ordena arestas para saber quais arestas a linha de varredura intercepta
void ordenar_e_preencherArestas_ET() {
    sort(ET.begin(), ET.end(), ordenaymin());
    for (vector<arestas>::iterator it = ET.begin(); it < ET.end(); it++) {
        // caso inclinacao = 0 entao temos uma linha horizontal, 
        // nao precisamos tratar no algoritmo no algoritmo AET pois essa eh uma borda externa do poligono
        if (it->inclinacao == 0) {
            ET.erase(it);
        }
    }
}

//ordena AET pelo valor de x = xmin
void ordenaAETxval() {
    sort(AET.begin(), AET.end(), ordenaXmin());
}

// encontra as interseccoes da linha de varredura, preenche o bloco e atualiza
void preencherPoligono() {
    while (AET.size() != 0) {
        for (vector<arestas>::iterator it = AET.begin(); it < AET.end(); it++) {
            desenhaPixel(it->xval, (it+1)->xval);
            it++;
        }
        varredura++;
        removerAET();
        atualizaXval();
        atualizaAET();
        ordenaAETxval();
    }
}

//cria pontos que foram desenhados na tela(enquanto nao esta conectado com a interface)
void criarET(vector<float> input) {

    int i,x,y;

    for(i = 0 ; i < (int) input.size()-1; i+=2) {
        x = (int) input.at(i);
        y = (int) input.at(i+1);
        pontos.push_back(tuple<int, int>(x, y));
    }


    for(i=0; i<(int)pontos.size()-1;i++) {
        arestas nAresta(pontos.at(i), pontos.at(i+1));
        ET.push_back(nAresta);
    }

    //fecha o poligono ligando o primeiro e o ultimo ponto do poligono
    arestas nAresta(pontos.at(0), pontos.at(pontos.size()-1));
    ET.push_back(nAresta);
}


vector<float> PoliFill(vector<float> input_coordinates) {
//int main(int argc, char **argv) {


	//confirma que os vectors estao vazios
	pixelsInternos.clear();
	pontos.clear();
	ET.clear();
	AET.clear();
    //cria pontos(pega da tela) e insere na ET em ordem de chegada
    criarET(input_coordinates);
    //ordena ET em relacao a ymin dos pontos inseridos
    ordenar_e_preencherArestas_ET();
    inicializaAlgVarredura();
    atualizaAET();
    preencherPoligono();
    //desenha_borda_do_poligono();
    return pixelsInternos;
}
