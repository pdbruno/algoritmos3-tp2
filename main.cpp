#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <map>
#include "utils.cpp"
#include "types.cpp"
#include "h-agm.cpp"
#include "h-cg.cpp"
#include "bl-tabu.cpp"
#include "bl.cpp"

using namespace std;
// Recibe por parámetro qué algoritmos utilizar para la ejecución separados por espacios.
// Imprime por clog la información de ejecución de los algoritmos.
// Imprime por cout el resultado de algun algoritmo ejecutado.
int n, m;
string tipo_de_memoria;
int max_iteraciones, max_memoria;
int main(int argc, char **argv) {
	// Leemos el parametro que indica el algoritmo a ejecutar.
	map<string, string> algoritmos_implementados = {
		{"H-CG", "Heuristica constructiva golosa"}, {"H-AGM", "Heuristica basada en AGM", }, {"BL", "Algoritmo de busqueda local"},
		{"BL-Tabu", "Algoritmo de busqueda local con Tabu Search"}
	};

	map<string, string> tipos_de_memoria = {
		{"aristas", "Memoria por aristas"}, {"ciclos", "Memoria por ciclos", }
	};



	// Verificar que el algoritmo pedido exista.
	if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end()) {
		cerr << "Algoritmo no encontrado: " << argv[1] << endl;
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto &alg_desc : algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
	string algoritmo = argv[1];

	// Verificar que sea memoria por aristas o ciclos.
	if (argc >= 2) {
		if (tipos_de_memoria.find(argv[2]) == tipos_de_memoria.end()) {
			cerr << "Tipo de memoria no encontrado: " << argv[2] << endl;
			cerr << "Los tipos existentes son: " << endl;
			for (auto &mem_desc : tipos_de_memoria) cerr << "\t- " << mem_desc.first << ": " << mem_desc.second << endl;
			return 0;
		}
		if (argc <= 3) { 
			cerr << "Falta el 3to parametro de busqueda tabu, el tamanio de la memoria" << endl; return 0;
		}
		if (argc <= 4) { 
			cerr << "Falta el 4to parametro de busqueda tabu, la cantidad de iteraciones" << endl; return 0;
		}
		tipo_de_memoria = argv[2];
		max_iteraciones = atoi(argv[3]);
		max_memoria = atoi(argv[4]);
	}

	// Leemos el input.
	int n, m;
	cin >> n >> m;
	Grafo G(n, vector<int>(n, MAX_INT));


	for (int i = 0; i < m; i++) {
		int v, w, peso;
		cin >> v >> w >> peso;
		G[v][w] = peso;
		G[w][v] = peso;
	}

	vector<Vertice> res(n + 1, -1);

	auto start = chrono::steady_clock::now();
	if (algoritmo == "H-CG")
		H_CG(G, m, n, res);
	else if (algoritmo == "H-AGM")
		H_AGM(G, m, n, res);
	else if (algoritmo == "BL")
		BL(G, m, n, res);
	else if (algoritmo == "BL-Tabu")
		BL_Tabu(G, m, n, res, tipo_de_memoria, max_iteraciones, max_memoria);

	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << "Total time: " << total_time << endl;

	int costo_total = 0;
    for (size_t i = 0; i < n; i++) {
        Vertice v = res[i];
        Vertice w = res[i + 1];
        costo_total += G[v][w];
    }

	cout << n << " " << costo_total << endl;

    for (size_t i = 0; i < n; i++) {
        Vertice v = res[i];
		cout << v << " ";
    }

	cout << endl;

	// Imprimimos el resultado por stdout.
	//cout << optimum << endl;
	return 0;
}