#include "types.h"
#include <tuple> 
using namespace std;


bool EstaEnLaMemoria(vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria);

int MejorCicloConMemoria(Grafo &G, vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria, int n);

void Memorizar(vector<Vertice> arista, deque<vector<Vertice>> &memoria);

void BL_Tabu(Grafo &G, int m, int n, vector<Vertice> &ciclo, int max_memoria, int max_iteraciones);