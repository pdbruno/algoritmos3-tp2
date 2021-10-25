#include <stack>
using namespace std;


Vertice get_min(vector<int> &distancia, vector<bool> &visitados) {

    Vertice minimo_no_visitado = -1;

    for (size_t i = 0; i < visitados.size(); i++) {
        if (!visitados[i] && (minimo_no_visitado == -1 || distancia[minimo_no_visitado] > distancia[i])) {
            minimo_no_visitado = i;
        }
    }
    return minimo_no_visitado;
}

void Prim(Grafo &G, int n, Grafo &res) {

    vector<bool> visitado(n, false);
    Vertice s = 0;
    vector<Vertice> padre(n, s);
    vector<int> distancia = G[s];

    distancia[s] = 0;
    visitado[s] = true;

    bool faltan_por_visitar = true;

    while (faltan_por_visitar) {
        faltan_por_visitar = false;
        Vertice v = get_min(distancia, visitado); /*nodo de menor distancia para agregar que no fue visitado aun */
        visitado[v] = true;
        for (int i = 0; i < n; i++) {
            if (v == i) i++;
            faltan_por_visitar = faltan_por_visitar || !visitado[i];
            if (!visitado[i] && distancia[i] > G[v][i]) {
                distancia[i] = G[v][i];
                padre[i] = v;
            }
        }
    }

    for (size_t i = 1; i < n; i++) { //a partir del vector padre armo un AGM pero en formato grafo
        res[padre[i]][i] = distancia[i];
        res[i][padre[i]] = distancia[i];
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
        for (size_t j = 0; j < n && !encontrado; j++) {
            if (j == i) j++;
            if (!visitado[j] && T[i][j] != MAX_INT) {
                encontrado = true;
                visitado[j] = true;
                lista.push(j);
                res[next++] = j;
            }
        }
        if (!encontrado) {
            lista.pop();
        }
    }

}

void H_AGM(Grafo &G, int m, int n, vector<Vertice> &res) {

    Grafo AGM(n, vector<int>(n, MAX_INT));
    Prim(G, n, AGM);

    DFS(AGM, n, res);
    res[n] = 0; //pq el recorrido termina en el primer vertice, que es el 0
}