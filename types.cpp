#include <vector>
using namespace std;
typedef int Vertice;
typedef int Peso;
struct Vecino {
    Vertice dst;
    Peso peso;
    Vecino(Vertice d, Peso p) : dst(d), peso(p) {}
};
typedef vector<vector<Vecino>> Grafo;