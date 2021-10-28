#include "types.h"
using namespace std;


Vertice get_min_cg(vector<int> &vecinos, vector<bool> &visitados);
// Heuristica constructiva golosa
void H_CG(Grafo &G, int m, int n, vector<Vertice> &res);