#include "types.h"
#include <tuple> 
using namespace std;



bool EstaEnLaMemoria(vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria);


void Memorizar(vector<Vertice> ciclo, deque<vector<Vertice>> &memoria);

int MejorCicloConMemoria(Grafo &G, vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria, int n);

bool EstaEnLaMemoriaArista(vector<Vertice> &arista, deque<vector<Vertice>> &memoria);

tuple<int,int,int> MejorCicloConMemoriaAristas(Grafo &G, vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria, int n);

void MemorizarArista(vector<Vertice> arista, deque<vector<Vertice>> &memoria);

void BL_Tabu_Ciclos(Grafo &G, int m, int n, vector<Vertice> &ciclo);
void BL_Tabu_Aristas(Grafo &G, int m, int n, vector<Vertice> &ciclo);

void BL_Tabu(Grafo &G, int m, int n, vector<Vertice> &ciclo, string tipo_de_memoria, int max_memoria, int max_iteraciones);