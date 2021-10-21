using namespace std;

int Costo(Grafo &G, vector<Vertice> &ciclo) {
    int costo_total = 0;
    int n = G.size();

    for (size_t i = 0; i < n - 1; i++) {
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

    costo -= G[pre_v][v];
    costo -= G[v][post_v];

    costo -= G[pre_w][w];
    costo -= G[w][post_w];

    costo += G[pre_v][w];
    costo += G[w][post_v];

    costo += G[pre_w][v];
    costo += G[v][post_w];

    return costo;
}


void BL(Grafo &G, int m, int n, vector<Vertice> &ciclo) {
    H_AGM(G, m, n, ciclo);

    int costo_ciclo = Costo(G, ciclo);
    bool hubo_mejora = true;

    while (hubo_mejora) {
        hubo_mejora = false;
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < i; j++) {

                int costo_candidato = CostoSwapeado(G, costo_ciclo, i, j, ciclo);

                if (costo_candidato < costo_ciclo) {
                    hubo_mejora = true;
                    Swap(ciclo, i, j);
                    costo_ciclo = costo_candidato;
                }
            }
        }
    }

}
