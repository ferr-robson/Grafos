#include <iostream>

using namespace std;

//typedef string string;

class Grafo{
    private:
        int arestaNula;
        int maxVertices;
        int numVertices;
        string* vertices;
        int** matrizAdjacencias;

    public:
        Grafo(int max, int valorArestaNula);
        ~Grafo();
        int getIndicePorNomeVertice(string item);
        bool isFull();
        void insereVertice(string item);
        void insereAresta(string saida, string entrada, int peso);
        int getPeso(string saida, string entrada);
        int obterGrau(string item);
        void imprimirMatriz();
        void imprimirVertices();
};

Grafo::Grafo(int max, int valorArestaNula){
    numVertices = 0;
    maxVertices = max;
    arestaNula = valorArestaNula;
    vertices = new string[maxVertices];
    matrizAdjacencias = new int*[maxVertices];
    
    for(int i = 0; i < maxVertices; i++)
        matrizAdjacencias[i] = new int[maxVertices];
    
    
    for(int i = 0; i < maxVertices; i++)
        for(int j = 0; j < maxVertices; j++)
            matrizAdjacencias[i][j] = arestaNula;
}

Grafo::~Grafo(){
    delete [] vertices;
    for(int i = 0; i < maxVertices; i++)
        delete [] matrizAdjacencias[i];
        
    delete [] matrizAdjacencias;
}

int Grafo::getIndicePorNomeVertice(string item){
    int indice = 0;

    while((item != vertices[indice]) && (indice < numVertices))
        indice++;

    if(item != vertices[indice])
        indice = -1;

    return indice;
}


bool Grafo::isFull(){
    return numVertices == maxVertices;
}

void Grafo::insereVertice(string item){
    if(isFull()){
        cout << "O numero max de vertices foi alcancado" << endl;
    } else {
        vertices[numVertices] = item;
        numVertices++;
    }
}

void Grafo::insereAresta(string saida, string entrada, int peso){
    int linha = getIndicePorNomeVertice(saida);
    int col = getIndicePorNomeVertice(entrada);

    if((linha != -1) && (col != -1)){
        matrizAdjacencias[linha][col] = peso;
        
        // Remover se trata-se de um grafo direcionado
        //matrizAdjacencias[col][linha] = peso;
    }
}

int Grafo::getPeso(string saida, string entrada){
    int linha = getIndicePorNomeVertice(saida);
    int col = getIndicePorNomeVertice(entrada);
    
    if((linha != -1) && (col != -1))
        return matrizAdjacencias[linha][col];
    else return 0;
}

int Grafo::obterGrau(string item){
    int grau = 0;
    int linha = getIndicePorNomeVertice(item);

    /*if(linha != -1){
        for(int i = 0; i < maxVertices; i++){
            if(matrizAdjacencias[linha][i] != arestaNula)
                grau++;
        }
        return grau;
    } else {
        return 0;
    }*/

    // Grafo direcionado
    if(linha != -1){
        for(int i = 0; i < maxVertices; i++){
            if(matrizAdjacencias[linha][i] != arestaNula)
                grau++;
            if((matrizAdjacencias[i][linha] != arestaNula) && (i != linha))
                grau++;
        }
        return grau;
    } else {
        return 0;
    }
}

void Grafo::imprimirMatriz(){
    for(int i = 0; i < maxVertices; i++){
        for(int j = 0; j < maxVertices; j++)
            cout << matrizAdjacencias[i][j] << " ";
        cout << endl;
    }
}

void Grafo::imprimirVertices(){
    for(int i = 0; i < numVertices; i++){
        cout << vertices[i] << endl;
    }
}

main(){
    int max, nulo;
    cout << "Num max de vertices e valor nulo" << endl;
    cin >> max >> nulo;

    Grafo grafo(max, nulo);

    string item, item2;

    int opcao, valor, peso;

    do{
        cout << "0 - Sair" << endl;
        cout << "1 - inserir vertice" << endl;
        cout << "2 - inserir aresta" << endl;
        cout << "3 - imprimir grau do vertice" << endl;
        cout << "4 - inprimir peso da aresta" << endl;
        cout << "5 - imprimir matriz" << endl;
        cout << "6 - listar vertices" << endl;
        cout << "Informe a opcao: ";
        cin >> opcao;
        
        switch (opcao){
            case 0:
                cout << "Saindo...";
                break;
            case 1:
                cout << "Nome do vertice: ";
                cin >> item;
                grafo.insereVertice(item);
                break;
            case 2:
                cout << "Vertice saida, vertice entrada e peso: " << endl;
                cin >> item >> item2 >> peso;
                grafo.insereAresta(item, item2, peso);
                break;
            case 3:
                cout << "Nome do vertice a calcular o grau: ";
                cin >> item;
                cout << "O grau do vertice e: " << grafo.obterGrau(item) << endl;
                break;
            case 4:
                cout << "Vertice1 e vertice2: " << endl;
                cin >> item >> item2;
                cout << "O peso da aresta e: " << grafo.getPeso(item, item2) << endl;
                break;
            case 5:
                grafo.imprimirMatriz();
                break;
            case 6:
                grafo.imprimirVertices();
                break;
            default:
                cout << "ERROR" << endl;
                break;
        }
    }while (opcao != 0);
    cout<<"fim do programa";
}