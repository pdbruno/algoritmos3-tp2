#include "utils.h"
using namespace std;


template<class T>
void print_vector(vector<T> &vector) {
    for (T i: vector)
        cout << i << ' ';
    cout << "!" << endl;
}

int Costo(Grafo &G, vector<Vertice> &ciclo) {
    int costo_total = 0;
    int n = G.size();

    for (size_t i = 0; i < n; i++) {
        Vertice v = ciclo[i];
        Vertice w = ciclo[i + 1];
        costo_total += G[v][w];
    }

    return costo_total;
}

void Swap(vector<Vertice> &ciclo, int i, int j) {
    Vertice aux = ciclo[i];
    ciclo[i] = ciclo[j];
    ciclo[j] = aux;
}

int CostoSwapeado(Grafo &G, int costo, int i, int j, vector<Vertice> &ciclo) {
    int n = G.size();

    Vertice pre_v = ciclo[i - 1];
    Vertice v = ciclo[i];
    Vertice post_v = ciclo[i + 1];

    Vertice pre_w = ciclo[j - 1];
    Vertice w = ciclo[j];
    Vertice post_w = ciclo[j + 1];

    if (i == j + 1) { //pre_v = w, post_w = v
        costo -= G[pre_w][w];
        costo -= G[v][post_v];

        costo += G[pre_w][v];
        costo += G[w][post_v];
    }
    else {
        costo -= G[pre_v][v];
        costo -= G[v][post_v];

        costo -= G[pre_w][w];
        costo -= G[w][post_w];

        costo += G[pre_v][w];
        costo += G[w][post_v];

        costo += G[pre_w][v];
        costo += G[v][post_w];
    }


    return costo;
}