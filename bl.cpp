#include "utils.h"
#include "bl.h"
using namespace std;

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
