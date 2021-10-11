using namespace std;

// Heuristica constructiva golosa
int H_CG(vector<tuple<int, int, int>> &aristas, int m, int n) {
  vector<int> grados(n, 0);
  vector<tuple<int, int, int, bool>> seleccionadas(m, {0,0,0,false})
	for (int i = 0; i < m; ++i) {
		auto[v1, v2, c] = aristas[i];
    seleccionadas[i] = {v1,v2,c,false};
	}	
  
  for (int i = 0; i < n; ++i) { // Cuantas veces tengo que tomar minimo antes de hacer un C. Hamiltonino?
		auto[v1, v2, c, sel] = seleccionadas[i];
    
	}


}

tuple<int, int, int> get_min(vector<tuple<int, int, int, bool>> &list) {}
