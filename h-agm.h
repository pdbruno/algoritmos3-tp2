#include <stack>
#include <deque>
#include "types.h"
using namespace std;

Vertice get_min(vector<int> &distancia, vector<bool> &visitados);

void Prim(Grafo &G, int n, Grafo &res);

void DFS(Grafo &T, int n, vector<Vertice> &res);

void H_AGM(Grafo &G, int m, int n, vector<Vertice> &res);