#include "main.h"

using namespace std;
// Recibe por parámetro qué algoritmos utilizar para la ejecución separados por espacios.
// Imprime por clog la información de ejecución de los algoritmos.
// Imprime por cout el resultado de algun algoritmo ejecutado.

void print(char *printable) {
	cout << printable << endl;
}

int main(int argc, char **argv) {
	int max_iteraciones, max_memoria;

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

	// Verificar que sea memoria por aristas o ciclos.
	if (argc > 3) {
		if (argc <= 3) {
			cerr << "Falta el 2do parametro de busqueda tabu, el tamanio de la memoria" << endl; return 0;
		}
		if (argc <= 4) {
			cerr << "Falta el 3er parametro de busqueda tabu, la cantidad de iteraciones" << endl; return 0;
		}
		max_iteraciones = atoi(argv[3]);
		max_memoria = atoi(argv[4]);
	}
	string input = argv[2];

	// lectura del input
	ifstream input_file;
	input_file.open(input);

	if (!input_file.is_open()) {
		printf("Archivo de entrada invalido.\n");
		return 1;
	}

	// Leemos el input.
	int n, m;
	int primer_vertice, segundo_vertice, primer_peso;
	bool primer_vertice_es_0 = false;
	input_file >> n >> m >> primer_vertice >> segundo_vertice >> primer_peso;

	if (primer_vertice == 0) {
		primer_vertice_es_0 = true;
	}

	m = n*(n-1)/2;
	Grafo G(n, vector<int>(n, MAX_INT));
	string line = "";
	getline(input_file, line, '\n');
	
	G[0][1] = primer_peso;
	G[1][0] = primer_peso;

	while (getline(input_file, line, '\n')) {
		stringstream ss(line);
		int v, w, peso;
		ss >> v >> w >> peso;
 		if (!primer_vertice_es_0) {
			v--;
			w--;
		} 
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
		BL_Tabu(G, m, n, res, max_iteraciones, max_memoria);

	auto end = chrono::steady_clock::now();
	double total_time = chrono::duration<double, milli>(end - start).count();

	// Imprimimos el tiempo de ejecución por stderr.
	clog << total_time << endl;

	int64_t costo_total = Costo(G, res);

	cout << n << " " << costo_total << endl;

	for (size_t i = 0; i < n; i++) {
		Vertice v = res[i];
		if (!primer_vertice_es_0) v++;
		cout << v << " ";
	}

	cout << endl;

	// Imprimimos el resultado por stdout.
	//cout << optimum << endl;
	return 0;
}