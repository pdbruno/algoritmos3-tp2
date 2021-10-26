#include <deque> 
using namespace std;

// PARAMETROS QUE DEBERIAN LLEGAR A LA FUNCION
int T = 10;
int MAX_ITERATIONS = 100000;

int CostoTabu(Grafo &G, vector<Vertice> &ciclo) {
    int costo_total = 0;
    int n = G.size();

    for (size_t i = 0; i < n; i++) {
        Vertice v = ciclo[i];
        Vertice w = ciclo[i + 1];
        costo_total += G[v][w];
    }

    return costo_total;
}

void SwapTabu(vector<Vertice> &ciclo, int i, int j) {
    Vertice aux = ciclo[i];
    ciclo[i] = ciclo[j];
    ciclo[j] = aux;
}

int CostoSwapeadoTabu(Grafo &G, int costo, int i, int j, vector<Vertice> &ciclo) {
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

bool EstaEnLaMemoria(vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria) {
    for (int i = 0; i < memoria.size(); i++) {
        bool es_igual = true;
        for (int j = 0; j< memoria[i].size() && es_igual; j++) {
            if (memoria[i][j] != ciclo[j]) {
                es_igual = false;
            }
        }
        if (es_igual) {
            return true;
        }
    }
    return false;
}


void Memorizar(vector<Vertice> ciclo, deque<vector<Vertice>> &memoria) {
    if (memoria.size() == T) {
       memoria.pop_front();
    }
    memoria.push_back(ciclo);
}

int MejorCicloConMemoria(Grafo &G, vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria, int n) {
    int costo_ciclo = MAX_INT;
    bool hubo_mejora = true;

    while (hubo_mejora) {
        hubo_mejora = false;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < i; j++) {
                vector<Vertice> candidato(ciclo);
                SwapTabu(candidato, i, j);
                int costo_candidato = CostoTabu(G, candidato);
                if (costo_candidato < costo_ciclo && !EstaEnLaMemoria(candidato, memoria)) {
                    hubo_mejora = true;
                    SwapTabu(ciclo, i, j);
                    costo_ciclo = costo_candidato;
                }
            }
        }
    }

    return costo_ciclo;
}

void BL_Tabu(Grafo &G, int m, int n, vector<Vertice> &ciclo) {
    H_AGM(G, m, n, ciclo);
    vector<Vertice> mejorCiclo = ciclo;
    int mejorCosto = CostoTabu(G, ciclo);

    deque<vector<Vertice>> memoria;

    int i = 0;
    while (i < MAX_ITERATIONS) {
        int costo_candidato = MejorCicloConMemoria(G, ciclo, memoria, n);
        Memorizar(ciclo, memoria);
        if (costo_candidato < mejorCosto) {
            mejorCosto = costo_candidato;
            mejorCiclo = ciclo;
        }
        i++;
    }
    for(int i = 0; i < n; i++) {
        ciclo[i] = mejorCiclo[i];
    }
}
