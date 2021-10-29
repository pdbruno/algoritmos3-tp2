#include <iostream>
#include "types.h"

int Costo(Grafo &G, vector<Vertice> &ciclo);
void Swap(vector<Vertice> &ciclo, int i, int j);
int CostoSwapeado(Grafo &G, int costo, int i, int j, vector<Vertice> &ciclo);

template<class T>
void print_vector(vector<T> &vector);