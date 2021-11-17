#include "utils.h"
#include "bl-tabu.h"
#include "h-cg.h"
using namespace std;

#include <iterator>

// PARAMETROS QUE DEBERIAN LLEGAR A LA FUNCION
int T;

bool EstaEnLaMemoria(vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria) {
    for (int i = 0; i < memoria.size(); i++) {
        bool es_igual = true;
        for (int j = 0; j < memoria[i].size() && es_igual; j++) {
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


int MejorCicloConMemoria(Grafo &G, vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria, int n) {
    int costo_ciclo = MAX_INT;
    
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < i; j++) {
            vector<Vertice> candidato(ciclo);
            Swap(candidato, i, j);
            int costo_candidato = Costo(G, candidato);
            if (costo_candidato < costo_ciclo && !EstaEnLaMemoria(candidato, memoria)) {
                Swap(ciclo, i, j);
                costo_ciclo = costo_candidato;
            }
        }
    }

    return costo_ciclo;
}

void Memorizar(vector<Vertice> ciclo, deque<vector<Vertice>> &memoria) {
    if (memoria.size() == T) {
        memoria.pop_front();
    }
    memoria.push_back(ciclo);
}

void BL_Tabu(Grafo &G, int m, int n, vector<Vertice> &ciclo, int max_iteraciones, int max_memoria) {
    T = max_memoria;

    H_CG(G, m, n, ciclo);
    vector<Vertice> mejorCiclo = ciclo;
    int mejorCosto = Costo(G, ciclo);

    deque<vector<Vertice>> memoria;

    for (size_t i = 0; i < max_iteraciones; i++) {
        int costo_candidato = MejorCicloConMemoria(G, ciclo, memoria, n);
        Memorizar(ciclo, memoria);
        if (costo_candidato < mejorCosto) {
            mejorCosto = costo_candidato;
            mejorCiclo = ciclo;
        }
    }

    for (int i = 0; i < n; i++) {
        ciclo[i] = mejorCiclo[i];
    }
}