#include "Graph.hpp"
#include <iostream>

/*
    funcion: NodoAdyacencia (Constructor)
    Descripcion: Inicializa un nodo de adyacencia con destino y peso.
    Parametros:
        - destino: ID del nodo destino
        - pesoInicial: Peso inicial de la arista (default = 1)
    Complejidad: O(1)
*/
NodoAdyacencia::NodoAdyacencia(int destino, int pesoInicial)
    : idDestino(destino), peso(pesoInicial), siguiente(nullptr) {
}

/*
    funcion: ~NodoAdyacencia (Destructor)
    Descripcion: Destructor del nodo. La liberación de la cadena se hace
                 desde el Vertice para evitar eliminación recursiva profunda.
    Complejidad: O(1)
*/
NodoAdyacencia::~NodoAdyacencia() {
}

/*
    funcion: Vertice (Constructor por defecto)
    Descripcion: Inicializa un vértice vacío.
    Complejidad: O(1)
*/
Vertice::Vertice() : nombre(""), tipo(' '), cabezaLista(nullptr) {
}

/*
    funcion: Vertice (Constructor con parámetros)
    Descripcion: Inicializa un vértice con nombre y tipo.
    Parametros:
        - nom: Nombre del vértice
        - t: Tipo ('P' o 'R')
    Complejidad: O(1)
*/
Vertice::Vertice(const String& nom, char t)
    : nombre(nom), tipo(t), cabezaLista(nullptr) {
}

/*
    funcion: ~Vertice (Destructor)
    Descripcion: Libera la memoria de la lista de adyacencias.
    Complejidad: O(k) donde k es el número de aristas del vértice
*/
Vertice::~Vertice() {
    limpiarLista();
}

/*
    funcion: limpiarLista
    Descripcion: Libera iterativamente todos los nodos de la lista enlazada.
                 Evita recursión profunda que podría causar stack overflow.
    Complejidad: O(k) donde k es el número de aristas
*/
void Vertice::limpiarLista() {
    NodoAdyacencia* actual = cabezaLista;
    while (actual != nullptr) {
        NodoAdyacencia* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabezaLista = nullptr;
}

// ============================================================================
// IMPLEMENTACIÓN DE Graph
// ============================================================================

/*
    funcion: Graph (Constructor)
    Descripcion: Inicializa el grafo con capacidad para MAX_NODOS vértices.
    Complejidad: O(MAX_NODOS)
*/
Graph::Graph() : numNodos(0) {
    grafo = new Vertice[MAX_NODOS];
}

/*
    funcion: ~Graph (Destructor)
    Descripcion: Libera toda la memoria del grafo.
    Complejidad: O(V + E)
*/
Graph::~Graph() {
    delete[] grafo;
}

/*
    funcion: obtenerOcrearNodo
    Descripcion: Busca un nodo por nombre. Si no existe, lo crea.
                 Garantiza que cada nombre tenga un ID único.
    Parametros:
        - nombre: Nombre del vértice
        - tipo: 'P' para Platillo, 'R' para Restaurante
    Return: ID numérico del nodo
    Complejidad: O(n) búsqueda lineal
*/
int Graph::obtenerOcrearNodo(const String& nombre, char tipo) {
    // Buscar si ya existe
    for (int i = 0; i < numNodos; ++i) {
        if (grafo[i].nombre == nombre && grafo[i].tipo == tipo) {
            return i;
        }
    }
    
    // No existe, crear nuevo nodo
    if (numNodos >= MAX_NODOS) {
        std::cerr << "Error: Capacidad máxima del grafo alcanzada." << std::endl;
        return -1;
    }
    
    grafo[numNodos].nombre = nombre;
    grafo[numNodos].tipo = tipo;
    grafo[numNodos].cabezaLista = nullptr;
    
    return numNodos++;
}

/*
    funcion: buscarArista
    Descripcion: Recorre la lista enlazada del nodo origen buscando
                 una conexión al nodo destino.
    Parametros:
        - idOrigen: ID del nodo origen
        - idDestino: ID del nodo destino
    Return: Puntero al NodoAdyacencia si existe, nullptr si no
    Complejidad: O(k) donde k es el grado del nodo origen
*/
NodoAdyacencia* Graph::buscarArista(int idOrigen, int idDestino) const {
    if (idOrigen < 0 || idOrigen >= numNodos) return nullptr;
    
    NodoAdyacencia* actual = grafo[idOrigen].cabezaLista;
    while (actual != nullptr) {
        if (actual->idDestino == idDestino) {
            return actual;
        }
        actual = actual->siguiente;
    }
    return nullptr;
}

/*
    funcion: agregarAristaUnidireccional
    Descripcion: Función auxiliar que agrega una arista en UNA sola dirección.
                 Si ya existe, incrementa el peso.
    Parametros:
        - idOrigen: ID del nodo origen
        - idDestino: ID del nodo destino
    Complejidad: O(k) búsqueda + O(1) inserción
*/
void Graph::agregarAristaUnidireccional(int idOrigen, int idDestino) {
    // Buscar si ya existe la arista
    NodoAdyacencia* existente = buscarArista(idOrigen, idDestino);
    
    if (existente != nullptr) {
        // CASO 1: Ya existe, solo incrementar peso
        existente->peso++;
    } else {
        // CASO 2: No existe, crear nuevo nodo
        NodoAdyacencia* nuevo = new NodoAdyacencia(idDestino, 1);
        nuevo->siguiente = grafo[idOrigen].cabezaLista;
        grafo[idOrigen].cabezaLista = nuevo;
    }
}

/*
    funcion: agregarArista
    Descripcion: Agrega una arista BIDIRECCIONAL entre origen y destino.
                 Crea conexiones en ambas direcciones:
                   - origen -> destino
                   - destino -> origen
                 Si ya existen, incrementa el peso en ambas direcciones.
                 Usa inserción al inicio para O(1).
    
    Parametros:
        - idOrigen: ID del nodo origen (típicamente un Platillo)
        - idDestino: ID del nodo destino (típicamente un Restaurante)
    Complejidad: O(k1 + k2) búsqueda en ambas listas + O(1) inserción
*/
void Graph::agregarArista(int idOrigen, int idDestino) {
    if (idOrigen < 0 || idOrigen >= numNodos || 
        idDestino < 0 || idDestino >= numNodos) {
        return;
    }
    
    // Agregar arista en ambas direcciones (grafo bidireccional/no dirigido)
    agregarAristaUnidireccional(idOrigen, idDestino);  // origen -> destino
    agregarAristaUnidireccional(idDestino, idOrigen);  // destino -> origen
}

/*
    funcion: ejecutarBFS
    Descripcion: Búsqueda en Anchura (BFS) - recorre nivel por nivel.
                 Imagina una onda expansiva desde el centro.
    
    ALGORITMO:
    1. Crear cola de espera
    2. Meter nodo inicial a la cola
    3. Mientras la cola no esté vacía:
       a. Sacar el primer elemento
       b. Recorrer sus vecinos (lista enlazada)
       c. Si el vecino no fue visitado, agregarlo a la cola
    
    Parametros:
        - nodoInicio: ID del nodo inicial
    Complejidad: O(V + E)
*/
void Graph::ejecutarBFS(const int nodoInicio) const {
    if (nodoInicio < 0 || nodoInicio >= numNodos) {
        std::cout << "Nodo de inicio inválido." << std::endl;
        return;
    }
    
    // Arreglo de visitados
    bool* visitado = new bool[numNodos];
    for (int i = 0; i < numNodos; ++i) {
        visitado[i] = false;
    }
    
    // Cola manual con arreglo circular
    int* cola = new int[numNodos];
    int frente = 0;
    int final_cola = 0;
    
    // Encolar nodo inicial
    cola[final_cola++] = nodoInicio;
    visitado[nodoInicio] = true;
    
    std::cout << "\n===== BFS desde: " << grafo[nodoInicio].nombre 
              << " (Tipo: " << grafo[nodoInicio].tipo << ") =====" << std::endl;
    std::cout << "Recorrido BFS:" << std::endl;
    
    int nivel = 0;
    int nodosEnNivelActual = 1;
    int nodosEnSiguienteNivel = 0;
    
    while (frente < final_cola) {
        std::cout << "  Nivel " << nivel << ": ";
        
        for (int n = 0; n < nodosEnNivelActual && frente < final_cola; ++n) {
            // Desencolar
            int nodoActual = cola[frente++];
            
            std::cout << grafo[nodoActual].nombre;
            if (grafo[nodoActual].tipo == 'R') std::cout << "(R)";
            else std::cout << "(P)";
            
            // Recorrer lista de adyacencias
            NodoAdyacencia* vecino = grafo[nodoActual].cabezaLista;
            while (vecino != nullptr) {
                if (!visitado[vecino->idDestino]) {
                    visitado[vecino->idDestino] = true;
                    cola[final_cola++] = vecino->idDestino;
                    nodosEnSiguienteNivel++;
                }
                vecino = vecino->siguiente;
            }
            
            if (n < nodosEnNivelActual - 1) std::cout << ", ";
        }
        
        std::cout << std::endl;
        nivel++;
        nodosEnNivelActual = nodosEnSiguienteNivel;
        nodosEnSiguienteNivel = 0;
    }
    
    std::cout << "===== Fin BFS =====" << std::endl;
    
    // Liberar memoria
    delete[] visitado;
    delete[] cola;
}

/*
    funcion: ejecutarDFS
    Descripcion: Búsqueda en Profundidad (DFS) - explora tan lejos como sea posible
                 antes de retroceder.
    Parametros:
        - nodoInicio: ID del nodo inicial
    Complejidad: O(V + E)
*/
void Graph::ejecutarDFS(int nodoInicio) const {
    if (nodoInicio < 0 || nodoInicio >= numNodos) {
        std::cout << "Nodo de inicio inválido." << std::endl;
        return;
    }
    
    bool* visitado = new bool[numNodos];
    for (int i = 0; i < numNodos; ++i) {
        visitado[i] = false;
    }
    
    std::cout << "\n===== DFS desde: " << grafo[nodoInicio].nombre 
              << " (Tipo: " << grafo[nodoInicio].tipo << ") =====" << std::endl;
    std::cout << "Recorrido DFS: ";
    
    dfsRecursivo(nodoInicio, visitado);
    
    std::cout << std::endl;
    std::cout << "===== Fin DFS =====" << std::endl;
    
    delete[] visitado;
}

/*
    funcion: dfsRecursivo
    Descripcion: Función auxiliar recursiva para DFS.
    Parametros:
        - nodo: Nodo actual
        - visitado: Arreglo de nodos visitados
    Complejidad: O(V + E) en total
*/
void Graph::dfsRecursivo(int nodo, bool* visitado) const {
    visitado[nodo] = true;
    std::cout << grafo[nodo].nombre;
    if (grafo[nodo].tipo == 'R') std::cout << "(R)";
    else std::cout << "(P)";
    std::cout << " ";
    
    NodoAdyacencia* vecino = grafo[nodo].cabezaLista;
    while (vecino != nullptr) {
        if (!visitado[vecino->idDestino]) {
            dfsRecursivo(vecino->idDestino, visitado);
        }
        vecino = vecino->siguiente;
    }
}

/*
    funcion: buscarNodoPorNombre
    Descripcion: Busca un nodo por su nombre exacto.
    Parametros:
        - nombre: Nombre a buscar
    Return: ID si existe, -1 si no
    Complejidad: O(n)
*/
int Graph::buscarNodoPorNombre(const String& nombre) const {
    for (int i = 0; i < numNodos; ++i) {
        if (grafo[i].nombre == nombre) {
            return i;
        }
    }
    return -1;
}

/*
    funcion: imprimirGrafo
    Descripcion: Muestra la estructura completa del grafo bidireccional con todas sus conexiones.
    Complejidad: O(V + E)
*/
void Graph::imprimirGrafo() const {
    std::cout << "\n========== ESTRUCTURA DEL GRAFO BIDIRECCIONAL ==========" << std::endl;
    std::cout << "Total de nodos: " << numNodos << std::endl;
    std::cout << "---------------------------------------------------------" << std::endl;
    
    int platillosCount = 0;
    int restaurantesCount = 0;
    
    // Primero mostrar platillos y sus conexiones
    std::cout << "\n--- PLATILLOS ---" << std::endl;
    for (int i = 0; i < numNodos; ++i) {
        if (grafo[i].tipo == 'P') {
            platillosCount++;
            std::cout << "\n[PLATILLO] " << grafo[i].nombre << " (ID: " << i << ")" << std::endl;
            std::cout << "  Conexiones bidireccionales:" << std::endl;
            
            NodoAdyacencia* vecino = grafo[i].cabezaLista;
            if (vecino == nullptr) {
                std::cout << "    (sin conexiones)" << std::endl;
            }
            while (vecino != nullptr) {
                std::cout << "    <-> " << grafo[vecino->idDestino].nombre 
                          << " (pedidos: " << vecino->peso << ")" << std::endl;
                vecino = vecino->siguiente;
            }
        }
    }
    
    // Luego mostrar restaurantes y sus conexiones
    std::cout << "\n--- RESTAURANTES ---" << std::endl;
    for (int i = 0; i < numNodos; ++i) {
        if (grafo[i].tipo == 'R') {
            restaurantesCount++;
            std::cout << "\n[RESTAURANTE] " << grafo[i].nombre << " (ID: " << i << ")" << std::endl;
            std::cout << "  Platillos que vende:" << std::endl;
            
            NodoAdyacencia* vecino = grafo[i].cabezaLista;
            if (vecino == nullptr) {
                std::cout << "    (sin platillos)" << std::endl;
            }
            while (vecino != nullptr) {
                std::cout << "    <-> " << grafo[vecino->idDestino].nombre 
                          << " (pedidos: " << vecino->peso << ")" << std::endl;
                vecino = vecino->siguiente;
            }
        }
    }
    
    std::cout << "\n---------------------------------------------------------" << std::endl;
    std::cout << "Resumen: " << platillosCount << " platillos, " 
              << restaurantesCount << " restaurantes" << std::endl;
    std::cout << "=========================================================" << std::endl;
}

/*
    funcion: imprimirEstadisticas
    Descripcion: Muestra estadísticas detalladas del grafo bidireccional.
    Complejidad: O(V + E)
*/
void Graph::imprimirEstadisticas() const {
    int numPlatillos = 0;
    int numRestaurantes = 0;
    int totalAristasContadas = 0;  // Cuenta cada arista 2 veces (bidireccional)
    int pesoTotal = 0;
    int maxConexionesPlatillo = 0;
    int maxConexionesRestaurante = 0;
    String platilloMasConectado = "";
    String restauranteMasConectado = "";
    
    for (int i = 0; i < numNodos; ++i) {
        int conexiones = 0;
        NodoAdyacencia* vecino = grafo[i].cabezaLista;
        while (vecino != nullptr) {
            conexiones++;
            totalAristasContadas++;
            pesoTotal += vecino->peso;
            vecino = vecino->siguiente;
        }
        
        if (grafo[i].tipo == 'P') {
            numPlatillos++;
            if (conexiones > maxConexionesPlatillo) {
                maxConexionesPlatillo = conexiones;
                platilloMasConectado = grafo[i].nombre;
            }
        } else {
            numRestaurantes++;
            if (conexiones > maxConexionesRestaurante) {
                maxConexionesRestaurante = conexiones;
                restauranteMasConectado = grafo[i].nombre;
            }
        }
    }
    
    // En grafo bidireccional, cada arista se cuenta 2 veces
    int aristasReales = totalAristasContadas / 2;
    int pesoReal = pesoTotal / 2;
    
    std::cout << "\n========== ESTADÍSTICAS DEL GRAFO BIDIRECCIONAL ==========" << std::endl;
    std::cout << "Tipo de grafo: NO DIRIGIDO (bidireccional)" << std::endl;
    std::cout << "Número total de nodos: " << numNodos << std::endl;
    std::cout << "  - Platillos: " << numPlatillos << std::endl;
    std::cout << "  - Restaurantes: " << numRestaurantes << std::endl;
    std::cout << "Número total de aristas (conexiones únicas): " << aristasReales << std::endl;
    std::cout << "Suma total de pesos (pedidos): " << pesoReal << std::endl;
    if (aristasReales > 0) {
        std::cout << "Peso promedio por arista: " 
                  << static_cast<double>(pesoReal) / aristasReales << std::endl;
    }
    std::cout << "Platillo más conectado: " << platilloMasConectado 
              << " (" << maxConexionesPlatillo << " restaurantes)" << std::endl;
    std::cout << "Restaurante más conectado: " << restauranteMasConectado 
              << " (" << maxConexionesRestaurante << " platillos)" << std::endl;
    std::cout << "===========================================================" << std::endl;
}

/*
    funcion: obtenerRestaurantesDePlatillo
    Descripcion: Muestra todos los restaurantes donde se vende un platillo específico.
    Parametros:
        - nombrePlatillo: Nombre del platillo
    Complejidad: O(n + k)
*/
void Graph::obtenerRestaurantesDePlatillo(const String& nombrePlatillo) const {
    int idPlatillo = -1;
    
    // Buscar el platillo
    for (int i = 0; i < numNodos; ++i) {
        if (grafo[i].nombre == nombrePlatillo && grafo[i].tipo == 'P') {
            idPlatillo = i;
            break;
        }
    }
    
    if (idPlatillo == -1) {
        std::cout << "Platillo '" << nombrePlatillo << "' no encontrado." << std::endl;
        return;
    }
    
    std::cout << "\n===== Restaurantes que venden: " << nombrePlatillo << " =====" << std::endl;
    
    NodoAdyacencia* vecino = grafo[idPlatillo].cabezaLista;
    int totalPedidos = 0;
    int numRestaurantes = 0;
    
    while (vecino != nullptr) {
        std::cout << "  " << grafo[vecino->idDestino].nombre 
                  << " - " << vecino->peso << " pedidos" << std::endl;
        totalPedidos += vecino->peso;
        numRestaurantes++;
        vecino = vecino->siguiente;
    }
    
    if (numRestaurantes == 0) {
        std::cout << "  (sin conexiones a restaurantes)" << std::endl;
    } else {
        std::cout << "-------------------------------------------" << std::endl;
        std::cout << "Total: " << numRestaurantes << " restaurantes, " 
                  << totalPedidos << " pedidos" << std::endl;
    }
    std::cout << "================================================" << std::endl;
}

/*
    funcion: obtenerPlatilloMasConectado
    Descripcion: Encuentra y muestra el platillo con más conexiones a restaurantes.
    Complejidad: O(V + E)
*/
void Graph::obtenerPlatilloMasConectado() const {
    int maxConexiones = 0;
    int maxPedidos = 0;
    String mejorPlatillo = "";
    int idMejor = -1;
    
    for (int i = 0; i < numNodos; ++i) {
        if (grafo[i].tipo == 'P') {
            int conexiones = 0;
            int pedidos = 0;
            NodoAdyacencia* vecino = grafo[i].cabezaLista;
            while (vecino != nullptr) {
                conexiones++;
                pedidos += vecino->peso;
                vecino = vecino->siguiente;
            }
            if (conexiones > maxConexiones || 
                (conexiones == maxConexiones && pedidos > maxPedidos)) {
                maxConexiones = conexiones;
                maxPedidos = pedidos;
                mejorPlatillo = grafo[i].nombre;
                idMejor = i;
            }
        }
    }
    
    if (idMejor == -1) {
        std::cout << "No hay platillos en el grafo." << std::endl;
        return;
    }
    
    std::cout << "\n===== PLATILLO MÁS CONECTADO =====" << std::endl;
    std::cout << "Nombre: " << mejorPlatillo << std::endl;
    std::cout << "Número de restaurantes: " << maxConexiones << std::endl;
    std::cout << "Total de pedidos: " << maxPedidos << std::endl;
    std::cout << "\nRestaurantes:" << std::endl;
    
    NodoAdyacencia* vecino = grafo[idMejor].cabezaLista;
    while (vecino != nullptr) {
        std::cout << "  -> " << grafo[vecino->idDestino].nombre 
                  << " (" << vecino->peso << " pedidos)" << std::endl;
        vecino = vecino->siguiente;
    }
    std::cout << "==================================" << std::endl;
}

/*
    funcion: getNumNodos
    Descripcion: Retorna el número de nodos en el grafo.
    Return: Número de nodos
    Complejidad: O(1)
*/
int Graph::getNumNodos() const {
    return numNodos;
}

/*
    funcion: getNombreNodo
    Descripcion: Retorna el nombre de un nodo.
    Parametros:
        - id: ID del nodo
    Return: Nombre del nodo
    Complejidad: O(1)
*/
String Graph::getNombreNodo(int id) const {
    if (id < 0 || id >= numNodos) return "";
    return grafo[id].nombre;
}

/*
    funcion: getTipoNodo
    Descripcion: Retorna el tipo de un nodo.
    Parametros:
        - id: ID del nodo
    Return: 'P' o 'R'
    Complejidad: O(1)
*/
char Graph::getTipoNodo(int id) const {
    if (id < 0 || id >= numNodos) return ' ';
    return grafo[id].tipo;
}

/*
    funcion: limpiarGrafo
    Descripcion: Elimina todos los nodos y aristas del grafo.
    Complejidad: O(V + E)
*/
void Graph::limpiarGrafo() {
    for (int i = 0; i < numNodos; ++i) {
        grafo[i].limpiarLista();
        grafo[i].nombre = "";
        grafo[i].tipo = ' ';
    }
    numNodos = 0;
}
