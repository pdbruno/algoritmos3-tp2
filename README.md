# TSP - TP2 de Algoritmos y Estructuras de Datos 3
## 2021, 2do cuatrimestre


## Instrucciones


### Compilación y ejecución
1. Compilar 


```
make
```


3. Instancias


En el repo se encuentran dos tipos de instancias:
- Instancias de tsplib: Estas instancias son las parseadas desde ```tsplib``` las cuales tienen óptimos conocidos. Se encuentran en `instancias/parseadas`
- Instancias nuestras: Estas son instancias aleatorias creadas usando la función ```randint``` de python. Tienen tamaños desde los 10 hasta los 100 vértices, con la particularidad de que generamos 100 instancias extra de tamaño 50. Se encuentran en `instancias/nuestras`


4. Ejecución de algoritmos


Para correr algún algoritmo necesitamos el identificador del algoritmo en cuestión y una ruta hacia una instancia.
Los algoritmos existentes son: 
        - BL: Algoritmo de búsqueda local
        - BL-Tabu: Algoritmo de búsqueda local con Tabu Search
        - H-AGM: Heuristica basada en AGM
        - H-CG: Heuristica constructiva golosa


Ejemplo de comando para ejecutar:
```
./main H-CG "instancias/parseadas/pcb442.txt"
```


En el caso de querer correr Tabu search, el cual tiene más parámetros se envían en el siguiente orden: tipo de memoria, cantidad de iteraciones y tamaño de memoria. 


Ejemplo de comando para ejecutar ```BL-Tabu```:
```
./main BL-Tabu "instancias/parseadas/pcb442.txt" ciclos 1000 1000
```


### Experimentación y Análisis


Para reproducir los experimentos listados en el informe, contamos con dos Jupyter Notebooks.

- La notebook de experimentos cuenta datasets preparados para la ejecución de las instancias descritas anteriormente sobre todos los algoritmos.
- La notebook de análisis genera distintos tipos de gráficos y tablas para la comparación de los algoritmos.