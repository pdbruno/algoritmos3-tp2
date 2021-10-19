using namespace std;


Vertice get_min_cg(vector<int> &vecinos, vector<bool> &visitados) {
	int minimo = MAX_INT;

	for (size_t i = 0; i < vecinos.size(); i++) {
		if (!visitados[i] && (minimo == MAX_INT || vecinos[minimo] > vecinos[i])) {
			minimo = i;
		}
	}

	return minimo;
}

// Heuristica constructiva golosa
void H_CG(Grafo &G, int m, int n, vector<Vertice> &res) {
	vector<bool> visitados(n, 0);
	Vertice v = 0;
	res[0] = v;

	for (size_t i = 1; i < n; i++) {
		Vertice w = get_min_cg(G[i], visitados);
		visitados[w] = true;
		res[i] = w;
		v = w;
	}
}
