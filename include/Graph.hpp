#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "CustomString.hpp"

/*
    struct: NodoAdyacencia
    Descripción: Es un nodo de una lista enlazada.
                 Representa una conexión desde un nodo A hacia un nodo B.
    Campos:
        - idDestino: El ID numérico del restaurante/platillo al que apunta.
        - peso: Cuántas veces se ha pedido ese platillo en ese restaurante.
        - siguiente: Puntero al siguiente nodo en la lista.
*/
struct NodoAdyacencia {
    int idDestino;
    int peso;
    NodoAdyacencia* siguiente;
    
    NodoAdyacencia(int destino, int pesoInicial = 1);
    
    ~NodoAdyacencia();
};

/*
    struct: Vertice
    Descripcion: Representa a un Platillo o a un Restaurante en el grafo.
    Campos:
        - nombre: El texto identificador (ej. "Pizza", "Dominos").
        - tipo: 'P' (Platillo) o 'R' (Restaurante).
        - cabezaLista: Inicio de la lista de conexiones (adyacencias).
*/
struct Vertice {
    String nombre;
    char tipo;
    NodoAdyacencia* cabezaLista;
    Vertice();
    Vertice(const String& nom, char t);
    ~Vertice();
    void limpiarLista();
};

/*
    class: Graph
    Descripcion: Grafo BIDIRECCIONAL (no dirigido) implementado con listas de adyacencia enlazadas.
                 Representa las relaciones Platillo <-> Restaurante.
                 
    CARACTERÍSTICAS:
    - Grafo BIDIRECCIONAL: Conectamos Platillo <-> Restaurante en ambas direcciones
    - Listas enlazadas manuales (sin std::vector)
    - Soporta BFS y DFS
    - Manejo manual de memoria con new/delete
*/
class Graph {
public:
    Graph();
    int obtenerOcrearNodo(const String& nombre, char tipo);
    NodoAdyacencia* buscarArista(int idOrigen, int idDestino) const;
    void agregarArista(int idOrigen, int idDestino);  // Bidireccional
    void ejecutarBFS(int nodoInicio) const;
    void ejecutarDFS(int nodoInicio) const;
    int buscarNodoPorNombre(const String& nombre) const;
    void imprimirGrafo() const;
    void imprimirEstadisticas() const;
    void obtenerRestaurantesDePlatillo(const String& nombrePlatillo) const;
    void obtenerPlatilloMasConectado() const;
    int getNumNodos() const;
    String getNombreNodo(int id) const;
    char getTipoNodo(int id) const;
    void limpiarGrafo();
    ~Graph();

private:
    static const int MAX_NODOS = 15000;
    Vertice* grafo;
    int numNodos;
    
    void dfsRecursivo(int nodo, bool* visitado) const;
    void agregarAristaUnidireccional(int idOrigen, int idDestino);  // Función auxiliar
};

#endif // GRAPH_HPP
