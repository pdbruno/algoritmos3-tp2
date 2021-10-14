#include "types.cpp"
using namespace std;


void H_AGM(Grafo &G, int m, int n, vector<Vertice> &res) {
    //T = AGM(G)
	vector<Vertice> T(n, -1);
    AGM(G, T);
    //E = duplicar aristas de T
	vector<Vertice> E(n, -1);
    //whatever(E)
    //D = recorrer E usando DFS
	vector<Vertice> D(n, -1);
    DFS(E, D)
    //H = armar un circuito hamiltoniano siguiendo el orden dado por D

//chau me fui a comprar queso port salut light y entrenar

    //yo: de qué sirve duplicar las aristas en el segundo paso?
    //profe: No es necesario hacerlo, es sólo para tratar de que sea más clara la demo de la cota. 
    //Si tenés tiempo y ganas, mirá el video complementario que en el instante 2:20 menciono eso. Cualquier duda decime.
}

void AGM(Grafo &G, vector<Vertice> &res){
    //hay que ver si usar Prim o Kruskal. 
    //hoy pregunte en discord si vamos a trabajar solamente con grafos completos, que son super densos por lo que conviene usar Prim que es O(n²)
    //en caso contrario, conviene usar algun algoritmo O(mlog(n))
}
void DFS(vector<Vertice> &E, vector<Vertice> &res){
    //DFS bro
}