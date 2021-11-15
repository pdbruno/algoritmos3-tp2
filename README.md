# TSP - TP2 de Algoritmos y Estructuras de Datos 3
## 2021, 2do cuatrimestre

## Instrucciones

### Compilacion y ejecucion
1. Compilar 

```
make
```

3. Instancias

En el repo se encuentran dos tipos de instancias:
- Instancias de tsplib: Estas instancias son las parseadas desde ```tsplib``` las cuales tienen optimos conocidos. Se encuentran en `instancias/parseadas`
- Instancias nuestras: Estas son instancias aleatorias creadas usando la funcion ```randint``` de python. Tienen tamaños desde los 10 hasta los 100 vertices, con la particularidad de que generamos 100 instancias extra de tamaño 50. Se encuentran en `instancias/nuestras`

4. Ejecucion de algoritmos

Para correr algun algoritmo necesitamos el identificador del algoritmo en cuestion y una ruta hacia una instancia.
Los algoritmos existentes son: 
        - BL: Algoritmo de busqueda local
        - BL-Tabu: Algoritmo de busqueda local con Tabu Search
        - H-AGM: Heuristica basada en AGM
        - H-CG: Heuristica constructiva golosa

Ejemplo de comando para ejecutar:
```
./main H-CG "instancias/parseadas/pcb442.txt"
```

En el caso de querer correr Tabu search, el cual tiene mas parametros se envian en el siguiente orden: tipo de memoria, cantidad de iteraciones y tamaño de memoria. 

Ejemplo de comando para ejecutar ```BL-Tabu```:
```
./main BL-Tabu "instancias/parseadas/pcb442.txt" ciclos 1000 1000
```

### Experimentacion y Analisis

Para reproducir los experimentos listados en el informe, contamos con dos Jupyter Notebooks.

- La notebook de experimentos cuenta datasets preparados para la ejecucion de las instancias descritas anteriormente sobre todos los algoritmos.
- La notebook de analisis genera distintos tipos de graficos y tablas para la comparacion de los algoritmos.

