#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>
#include "bl-tabu.cpp"
#include "bl.cpp"
#include "h-cg.cpp"
#include "h-agm.cpp"

using namespace std;
// Recibe por parámetro qué algoritmos utilizar para la ejecución separados por espacios.
// Imprime por clog la información de ejecución de los algoritmos.
// Imprime por cout el resultado de algun algoritmo ejecutado.
vector<tuple<int, int, int>> aristas;
int n, m;
int main(int argc, char **argv) {
	// Leemos el parametro que indica el algoritmo a ejecutar.
	map<string, string> algoritmos_implementados = {
		{"H-CG", "Heuristica constructiva golosa"}, {"H-AGM", "Heuristica basada en AGM", }, {"BL", "Algoritmo de busqueda local"},
		{"BL-Tabu", "Algoritmo de busqueda local con Tabu Search"}
	};

	// Verificar que el algoritmo pedido exista.
	if (argc < 2 || algoritmos_implementados.find(argv[1]) == algoritmos_implementados.end()) {
		cerr << "Algoritmo no encontrado: " << argv[1] << endl;
		cerr << "Los algoritmos existentes son: " << endl;
		for (auto &alg_desc : algoritmos_implementados) cerr << "\t- " << alg_desc.first << ": " << alg_desc.second << endl;
		return 0;
	}
	string algoritmo = argv[1];

	// Leemos el input.
	cin >> n >> m;
	aristas.assign(m, { 0, 0, 0 });
	for (int i = 0; i < m; ++i) {
		int v1, v2, c;
		cin >> v1 >> v2 >> c;
		aristas[i] = {v1, v2, c};
	}

	int optimum;

	auto start = chrono::steady_clock::now();

	for (int i = 0; i < m; ++i) {
		cout << get<0>aristas[i] << get<1>aristas[i] << get<2>aristas[i];
	}

	if (algoritmo == "H-CG")
		optimum = H_CG(aristas);
	else if (algoritmo == "H-AGM")
		optimum = H_AGM(aristas);
	else if (algoritmo == "BL")
		optimum = BL(aristas);
	else if (algoritmo == "BL-Tabu")
		optimum = BL_Tabu(aristas);

	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << total_time << endl;

	// Imprimimos el resultado por stdout.
	cout << optimum << endl;
	return 0;
}