#include "types.cpp"
#include "h-agm.cpp"
using namespace std;

void BL(Grafo &G, int m, int n, vector<Vertice> &res) {
    H_AGM(G, m, n, res);

    vector<Vertice> mejorCiclo = res;
    while (costo(G, mejorCiclo) < costo(G, res)) {
        res = mejorCiclo;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                vector<Vertice> cicloCandidato = swap(mejorCiclo, i, j);
                if (costo(G, cicloCandidato) < costo(G, mejorCiclo)) {
                    mejorCiclo = cicloCandidato;
                }
            }
        }
    }

}

int costo(Grafo &G, vector<Vertice> &ciclo) {
    int costo_total = 0;
    for (int i = 0; i < ciclo.size(); i++) {
        Vertice v = ciclo[i];
        int siguiente = i+1;
        if (siguiente === ciclo.size()) {
            siguiente = 0;
        }
        costo_total += G[i][siguiente].peso;
    }
    return costo_total;
}

vector<Vertice> swap(vector<Vertice> &ciclo, int i, int j) {
    vector<Vertice> res = ciclo;
    Vertice aux = res[i];
    res[i] = res[j];
    res[j] = aux;
    return res;
}
