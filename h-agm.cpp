#include "types.cpp"
#include <stack>
using namespace std;

#define MAX_INT 2147483647

void H_AGM(Grafo &G, int m, int n, vector<Vertice> &res) {

    Grafo AGM(n, vector<Vecino>());
    Prim(G, n, AGM);

    DFS(AGM, n, res);
    res[n - 1] = 0; //pq el recorrido termina en el primer vertice, que es el 0
}

void Prim(Grafo &G, int n, Grafo &res) {

    vector<bool> visitado(n, false);
    vector<int> distancia(n, MAX_INT);
    vector<Vertice> padre(n, -1);
    Vertice s = 0;
    for (Vecino &vecino : G[s]) {
        distancia[vecino.dst] = vecino.peso;
        padre[vecino.dst] = s;
    }
    distancia[s] = 0;
    visitado[s] = true;

    bool faltan_por_visitar = true;

    while (faltan_por_visitar) {
        faltan_por_visitar = false;
        Vertice v = get_min(distancia, visitado); /*nodo de menor distancia para agregar que no fue visitado aun */
        visitado[v] = true;
        for (Vecino &vecino : G[v]) {
            faltan_por_visitar = faltan_por_visitar || !visitado[vecino.dst];
            distancia[vecino.dst] = vecino.peso;
            padre[vecino.dst] = v;
        }
    }

    for (size_t i = 1; i < n; i++) { //a partir del vector padre armo un AGM pero en formato grafo
        Vertice actual = i;
        Vertice Padre = padre[i];
        Peso p = G[Padre][(actual < Padre) ? actual : actual - 1].peso;
        res[padre[i]].push_back(Vecino(i, p));
    }


}

void DFS(Grafo &T, int n, vector<Vertice> &res) {
    int next = 0;
    Vertice r = 0;
    vector<bool> visitado(n, false);
    stack<Vertice> lista;
    lista.push(r);
    visitado[r] = true;
    res[next++] = r;
    while (!lista.empty()) {
        Vertice i = lista.top();
        bool encontrado = false;
        for (size_t j = 0; j < T[i].size() && !encontrado; i++) {
            Vertice w = T[i][j].dst;
            if (!visitado[w]) {
                encontrado = true;
                visitado[w] = true;
                lista.push(w);
                res[next++] = w;
            }
        }
        if (!encontrado) {
            lista.pop();
        }
    }

}

Vertice get_min(vector<int> &distancia, vector<bool> &visitados) {

    Vertice minimo_no_visitado = -1;

    for (size_t i = 0; i < visitados.size(); i++) {
        if (!visitados[i] && (minimo_no_visitado == -1 || distancia[minimo_no_visitado] > distancia[i])) {
            minimo_no_visitado = i;
        }
    }
    return minimo_no_visitado;
}