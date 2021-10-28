#include <vector>
#include <queue>
#include <deque>
#include <string>
using namespace std;
typedef int Vertice;
typedef int Peso;
typedef vector<vector<int>> Grafo;
#define MAX_INT 2147483647

void H_AGM(Grafo &G, int m, int n, vector<Vertice> &res);
void H_CG(Grafo &G, int m, int n, vector<Vertice> &res);
void BL(Grafo &G, int m, int n, vector<Vertice> &res);
void BL_Tabu(Grafo &G, int m, int n, vector<Vertice> &ciclo, string tipo_de_memoria, int max_memoria, int max_iteraciones);

