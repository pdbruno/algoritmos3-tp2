#include "types.cpp"
using namespace std;


// Heuristica constructiva golosa
void H_CG(Grafo &G, int m, int n, vector<Vertice> &res) {
	vector<bool> visitados(n, 0);
	Vertice v = 0;
	res[0] = v;

	for (size_t i = 1; i < n; i++) {
		Vertice w = get_min(G[v], visitados);
		visitados[w] = true;
		res[i] = w;
		v = w;
	}
}
Vertice get_min(vector<Vecino> &vecinos, vector<bool> &visitados) {

	Vecino *minimo = nullptr;

	for (size_t i = 0; i < vecinos.size(); i++) {
		if (!visitados[vecinos[i].dst] && (minimo == nullptr || minimo->peso > vecinos[i].peso)) {
			minimo = &vecinos[i];
		}
	}
	return minimo == nullptr ? -1 : minimo->dst;
}