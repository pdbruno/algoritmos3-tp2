#include "utils.h"
#include "bl-tabu.h"
#include "h-agm.h"
using namespace std;

#include <iterator>

/* class VecindadStar
{
public:
    struct Iterator 
    {
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = vector<Vertice>;
        using pointer           = vector<Vertice>*;
        using reference         = int&;

        Iterator(pointer ptr) : m_ptr(ptr) {}

        reference operator*() const { return *m_ptr; }
        pointer operator->() { return m_ptr; }
        Iterator& operator++() { m_ptr++; return *this; }  
        Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };  

    private:
        pointer m_ptr;
    };

    VecindadStar()

    Iterator begin() { return Iterator(&m_data[0]); }
    Iterator end()   { return Iterator(&m_data[200]); }

private:
    int m_data[200];
}; */

// PARAMETROS QUE DEBERIAN LLEGAR A LA FUNCION
int T;
int MAX_ITERATIONS;

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
                Swap(candidato, i, j);
                int costo_candidato = Costo(G, candidato);
                if (costo_candidato < costo_ciclo && !EstaEnLaMemoria(candidato, memoria)) {
                    hubo_mejora = true;
                    Swap(ciclo, i, j);
                    costo_ciclo = costo_candidato;
                }
            }
        }
    }

    return costo_ciclo;
}

bool EstaEnLaMemoriaArista(vector<Vertice> &arista, deque<vector<Vertice>> &memoria) {
    for (int i = 0; i < memoria.size(); i++) {
        bool es_igual = true;
        for (int j = 0; j< memoria[i].size() && es_igual; j++) {
            if (memoria[i][j] != arista[j]) {
                es_igual = false;
            }
        }
        if (es_igual) {
            return true;
        }
    }
    return false;
}


tuple<int,int,int> MejorCicloConMemoriaAristas(Grafo &G, vector<Vertice> &ciclo, deque<vector<Vertice>> &memoria, int n) {
    int costo_ciclo = MAX_INT;
    int i_mejor = MAX_INT;
    int j_mejor = MAX_INT;
    bool hubo_mejora = true;

    while (hubo_mejora) {
        hubo_mejora = false;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < i; j++) {
                vector<Vertice> candidato(ciclo);
                Swap(candidato, i, j);
                int costo_candidato = Costo(G, candidato);
                vector<Vertice> vec = {i,j};
                if (costo_candidato < costo_ciclo && !EstaEnLaMemoriaArista(vec, memoria)) {
                    hubo_mejora = true;
                    Swap(ciclo, i, j);
                    i_mejor = i;
                    j_mejor = j;
                    costo_ciclo = costo_candidato;
                }
            }
        }
    }

    return make_tuple(costo_ciclo, i_mejor, j_mejor);
}

void MemorizarArista(vector<Vertice> arista, deque<vector<Vertice>> &memoria) {
    if (memoria.size() == T) {
       memoria.pop_front();
    }
    memoria.push_back(arista);
}

void BL_Tabu_Ciclos(Grafo &G, int m, int n, vector<Vertice> &ciclo) {
    H_AGM(G, m, n, ciclo);
    vector<Vertice> mejorCiclo = ciclo;
    int mejorCosto = Costo(G, ciclo);

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

void BL_Tabu_Aristas(Grafo &G, int m, int n, vector<Vertice> &ciclo) {
    H_AGM(G, m, n, ciclo);
    vector<Vertice> mejorCiclo = ciclo;
    int mejorCosto = Costo(G, ciclo);

    deque<vector<Vertice>> memoria;

    int i = 0;
    while (i < MAX_ITERATIONS) {
        int costo_candidato, i_mejor, j_mejor;
        tie(costo_candidato, i_mejor, j_mejor) = MejorCicloConMemoriaAristas(G, ciclo, memoria, n);
        MemorizarArista({i_mejor, j_mejor}, memoria);
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

void BL_Tabu(Grafo &G, int m, int n, vector<Vertice> &ciclo, string tipo_de_memoria, int max_iteraciones, int max_memoria) {
    T = max_memoria;
    MAX_ITERATIONS = max_iteraciones;
    if (tipo_de_memoria == "aristas") {
        BL_Tabu_Aristas(G, m,  n, ciclo);
    } else {
        BL_Tabu_Ciclos(G, m,  n, ciclo);
    }
}