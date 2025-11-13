#include "DishBST.hpp"
#include <iostream>

/*
    funcion: DishNode (Constructor)
    Descripcion: Inicializa un nodo del BST con un platillo y su conteo de pedidos.
    Parametros:
        - count (int): Número de pedidos del platillo (llave del nodo).
        - dish (const Dish&): Platillo a almacenar en el nodo.
    Return: N/A
    Complejidad: O(1)
*/
DishNode::DishNode(int count, const Dish& dish) 
    : orderCount(count), dishCapacity(4), dishCount(0), left(nullptr), right(nullptr) {
    dishes = new Dish[dishCapacity];
    addDish(dish);
}

/*
    funcion: ~DishNode (Destructor)
    Descripcion: Libera la memoria dinámica del array de platillos.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(1)
*/
DishNode::~DishNode() {
    delete[] dishes;
}

/*
    funcion: addDish
    Descripcion: Agrega un platillo al array de platillos del nodo. 
                 Si el array está lleno, lo redimensiona.
    Parametros:
        - dish (const Dish&): Platillo a agregar.
    Return: N/A
    Complejidad: O(1) amortizado, O(n) en el peor caso cuando se redimensiona.
*/
void DishNode::addDish(const Dish& dish) {
    if (dishCount >= dishCapacity) {
        resize();
    }
    dishes[dishCount++] = dish;
}

/*
    funcion: resize
    Descripcion: Duplica la capacidad del array de platillos cuando está lleno.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(n), donde n es la cantidad actual de platillos en el nodo.
*/
void DishNode::resize() {
    dishCapacity *= 2;
    Dish* newDishes = new Dish[dishCapacity];
    for (int i = 0; i < dishCount; ++i) {
        newDishes[i] = dishes[i];
    }
    delete[] dishes;
    dishes = newDishes;
}

/*
    funcion: DishBST (Constructor)
    Descripcion: Inicializa un árbol binario de búsqueda vacío.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(1)
*/
DishBST::DishBST() : root(nullptr) {}

/*
    funcion: ~DishBST (Destructor)
    Descripcion: Libera toda la memoria del árbol.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(n), donde n es el número de nodos en el árbol.
*/
DishBST::~DishBST() {
    deleteTree(root);
}

/*
    funcion: deleteTree
    Descripcion: Función auxiliar recursiva para eliminar todos los nodos del árbol.
    Parametros:
        - node (DishNode*): Raíz del subárbol a eliminar.
    Return: N/A
    Complejidad: O(n), donde n es el número de nodos en el subárbol.
*/
void DishBST::deleteTree(DishNode* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

/*
    funcion: insert
    Descripcion: Inserta un platillo en el BST. Si ya existe un nodo con el mismo
                 número de pedidos, agrega el platillo a ese nodo.
    Parametros:
        - dish (const Dish&): Platillo a insertar.
    Return: N/A
    Complejidad: O(h + k), donde h es la altura del árbol y k es el número de platillos
                 en el nodo (si se necesita redimensionar el array).
*/
void DishBST::insert(const Dish& dish) {
    root = insertNode(root, dish);
    this->balanceWholeTree(root);
}

/*
    funcion: insertNode
    Descripcion: Función auxiliar recursiva para insertar un platillo en el BST.
    Parametros:
        - node (DishNode*): Raíz del subárbol actual.
        - dish (const Dish&): Platillo a insertar.
    Return: (DishNode*) Raíz del subárbol modificado.
    Complejidad: O(h + k), donde h es la altura del subárbol y k es el número de platillos
                 en el nodo si se necesita redimensionar.
*/
DishNode* DishBST::insertNode(DishNode* node, const Dish& dish) {
    int orderCount = dish.getTotalOrders();
    
    if (node == nullptr) return new DishNode(orderCount, dish);
    
    if (orderCount == node->orderCount) {
        // El nodo ya existe con este conteo, agregar el platillo al array
        node->addDish(dish);
    } else if (orderCount < node->orderCount) {
        node->left = insertNode(node->left, dish);
    } else {
        node->right = insertNode(node->right, dish);
    }
    return node;
}

/*
    funcion: getMaxOrderCount
    Descripcion: Encuentra el número máximo de pedidos en el BST.
    Parametros: Ninguno
    Return: (int) El número máximo de pedidos, o 0 si el árbol está vacío.
    Complejidad: O(h), donde h es la altura del árbol.
*/
int DishBST::getMaxOrderCount() const {
    return findMaxOrderCount(root);
}

/*
    funcion: findMaxOrderCount
    Descripcion: Función auxiliar recursiva para encontrar el máximo número de pedidos.
                 En un BST, el valor máximo está en el nodo más a la derecha.
    Parametros:
        - node (DishNode*): Raíz del subárbol actual.
    Return: (int) El número máximo de pedidos en el subárbol.
    Complejidad: O(h), donde h es la altura del subárbol.
*/
int DishBST::findMaxOrderCount(DishNode* node) const {
    if (node == nullptr) return 0;
    if (node->right == nullptr) return node->orderCount;
    return findMaxOrderCount(node->right);
}

/*
    funcion: findMostOrdered
    Descripcion: Encuentra todos los platillos con el mayor número de pedidos.
                 Maneja el caso de múltiples platillos con la misma cantidad máxima.
    Parametros:
        - resultDishes (Dish*&): Referencia al puntero donde se almacenarán los platillos encontrados.
        - resultCount (int&): Referencia a la variable donde se almacenará la cantidad de platillos encontrados.
    Return: N/A (los resultados se devuelven por referencia)
    Complejidad: O(h + k), donde h es la altura del árbol y k es el número de platillos
                 con el conteo máximo.
*/
void DishBST::findMostOrdered(Dish*& resultDishes, int& resultCount) const {
    if (root == nullptr) {
        resultDishes = nullptr;
        resultCount = 0;
        return;
    }
    
    int maxCount = getMaxOrderCount();
    resultCount = 0;
    
    // Primera pasada: contar cuántos platillos hay con el conteo máximo
    collectDishesByCount(root, maxCount, resultDishes, resultCount);
    
    // Asignar memoria para los resultados
    resultDishes = new Dish[resultCount];
    int tempCount = 0;
    
    // Segunda pasada: copiar los platillos
    collectDishesByCount(root, maxCount, resultDishes, tempCount);
}

/*
    funcion: collectDishesByCount
    Descripcion: Función auxiliar recursiva que recolecta todos los platillos con un
                 conteo específico de pedidos.
    Parametros:
        - node (DishNode*): Raíz del subárbol actual.
        - targetCount (int): Número de pedidos objetivo a buscar.
        - resultDishes (Dish*&): Array donde se copiarán los platillos (puede ser nullptr en la primera pasada).
        - resultCount (int&): Contador de platillos encontrados/copiados.
    Return: N/A (los resultados se devuelven por referencia)
    Complejidad: O(n), donde n es el número total de nodos en el árbol.
*/
void DishBST::collectDishesByCount(DishNode* node, int targetCount, Dish*& resultDishes, int& resultCount) const {
    if (node == nullptr) return;
    
    collectDishesByCount(node->left, targetCount, resultDishes, resultCount);
    
    if (node->orderCount == targetCount) {
        if (resultDishes == nullptr) {
            resultCount += node->dishCount;
        } else {
            for (int i = 0; i < node->dishCount; ++i) {
                resultDishes[resultCount++] = node->dishes[i];
            }
        }
    }
    
    collectDishesByCount(node->right, targetCount, resultDishes, resultCount);
}

/*
    funcion: printInOrder
    Descripcion: Imprime todos los platillos del árbol en orden ascendente por número de pedidos.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(n * m), donde n es el número de nodos y m es el promedio de platillos por nodo.
*/
void DishBST::printInOrder() const {
    printInOrderHelper(root);
}

/*
    funcion: printInOrderHelper
    Descripcion: Función auxiliar recursiva para imprimir el árbol en orden.
    Parametros:
        - node (DishNode*): Raíz del subárbol a imprimir.
    Return: N/A
    Complejidad: O(n * m), donde n es el número de nodos y m es el promedio de platillos por nodo.
*/
void DishBST::printInOrderHelper(DishNode* node) const {
    if (node == nullptr) return;
    
    printInOrderHelper(node->left);
    
    std::cout << "Pedidos: " << node->orderCount << " | Platillos: ";
    for (int i = 0; i < node->dishCount; ++i) {
        std::cout << node->dishes[i].getName();
        if (i < node->dishCount - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    printInOrderHelper(node->right);
}

/*
    funcion: printInReverseOrder
    Descripcion: Imprime todos los platillos del árbol en orden descendente por número de pedidos.
                 Útil para mostrar los platillos más populares primero.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(n * m), donde n es el número de nodos y m es el promedio de platillos por nodo.
*/
void DishBST::printInReverseOrder() const {
    printInReverseOrderHelper(root);
}

/*
    funcion: printInReverseOrderHelper
    Descripcion: Función auxiliar recursiva para imprimir el árbol en orden inverso (descendente).
    Parametros:
        - node (DishNode*): Raíz del subárbol a imprimir.
    Return: N/A
    Complejidad: O(n * m), donde n es el número de nodos y m es el promedio de platillos por nodo.
*/
void DishBST::printInReverseOrderHelper(DishNode* node) const {
    if (node == nullptr) return;
    
    printInReverseOrderHelper(node->right);
    
    std::cout << "Pedidos: " << node->orderCount << " | Platillos (" << node->dishCount << "): ";
    for (int i = 0; i < node->dishCount; ++i) {
        std::cout << node->dishes[i].getName();
        if (i < node->dishCount - 1) std::cout << ", ";
    }
    std::cout << std::endl;
    
    printInReverseOrderHelper(node->left);
}

/*
    funcion: getTopNDishes
    Descripcion: Obtiene los N platillos con más pedidos, en orden descendente.
                 Si hay empates, incluye todos los platillos con el mismo número de pedidos
                 hasta completar o superar N platillos.
    Parametros:
        - n (int): Número de platillos a obtener (aproximado si hay empates).
        - resultDishes (Dish*&): Referencia al puntero donde se almacenarán los platillos.
        - resultCount (int&): Referencia a la variable donde se almacenará la cantidad real de platillos.
    Return: N/A (los resultados se devuelven por referencia)
    Complejidad: O(h + k), donde h es la altura del árbol y k es el número de platillos recolectados.
*/
void DishBST::getTopNDishes(int n, Dish*& resultDishes, int& resultCount) const {
    if (root == nullptr || n <= 0) {
        resultDishes = nullptr;
        resultCount = 0;
        return;
    }
    
    Dish* tempDishes = new Dish[n * 2];
    resultCount = 0;
    int remaining = n;
    
    collectTopNDishes(root, remaining, tempDishes, resultCount);
    
    resultDishes = new Dish[resultCount];
    for (int i = 0; i < resultCount; ++i) {
        resultDishes[i] = tempDishes[i];
    }
    
    delete[] tempDishes;
}

/*
    funcion: collectTopNDishes
    Descripcion: Función auxiliar recursiva que recolecta los N platillos con más pedidos
                 en orden descendente (recorrido in-order inverso).
    Parametros:
        - node (DishNode*): Raíz del subárbol actual.
        - remaining (int&): Número de platillos que aún faltan por recolectar.
        - resultDishes (Dish*&): Array donde se almacenan los platillos.
        - resultCount (int&): Contador de platillos recolectados.
    Return: N/A (los resultados se devuelven por referencia)
    Complejidad: O(h + k), donde h es la altura y k es el número de platillos recolectados.
*/
void DishBST::collectTopNDishes(DishNode* node, int& remaining, Dish*& resultDishes, int& resultCount) const {
    if (node == nullptr || remaining <= 0) return;
    
    // Primero visitar el subárbol derecho (valores mayores)
    collectTopNDishes(node->right, remaining, resultDishes, resultCount);
    
    // Si aún necesitamos más platillos
    if (remaining > 0) {
        // Agregar todos los platillos de este nodo
        for (int i = 0; i < node->dishCount; ++i) {
            resultDishes[resultCount++] = node->dishes[i];
        }
        remaining -= node->dishCount;
    }
    
    // Luego visitar el subárbol izquierdo (valores menores)
    collectTopNDishes(node->left, remaining, resultDishes, resultCount);
}

int DishBST::getHeight(DishNode *node) const {
    if (node == nullptr) return 0;
    const int leftHeight = getHeight(node->left);
    const int rightHeight = getHeight(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void DishBST::balanceWholeTree(DishNode*& node){
  if (node == nullptr) return;
  balanceWholeTree(node->left);
  balanceWholeTree(node->right);
  const int balance = getBalanceFactor(node);

  if (balance > 1) {
      if (node->left != nullptr && getBalanceFactor(node->left) < 0) {
          rotateLeft(node->left);
      }
      rotateRight(node);
  } else if (balance < -1) {
      if (node->right != nullptr && getBalanceFactor(node->right) > 0) {
          rotateRight(node->right);
      }
      rotateLeft(node);
  }
}

void DishBST::balanceSubtree(DishNode*& node) {
  if (node == nullptr) return;
  const int balance = getBalanceFactor(node);

  if (balance > 1) {
    if (node->left != nullptr && getBalanceFactor(node->left) < 0) {
      rotateLeft(node->left);
    }
    rotateRight(node);
  } else if (balance < -1) {
    if (node->right != nullptr && getBalanceFactor(node->right) > 0) {
      rotateRight(node->right);
    }
    rotateLeft(node);
  }
}

void DishBST::rotateLeft(DishNode *&node) {
  DishNode *rightChild = node->right;
  node->right = rightChild->left;
  rightChild->left = node;
  node = rightChild;
}

void DishBST::rotateRight(DishNode *&node) {
  DishNode *leftChild = node->left;
  node->left = leftChild->right;
  leftChild->right = node;
  node = leftChild;
}

int DishBST::getBalanceFactor(DishNode *node) const {
  if (node == nullptr) return 0;
    const int leftSubTreeDepth = getHeight(node->left);
    const int rightSubTreeDepth = getHeight(node->right);
    return leftSubTreeDepth - rightSubTreeDepth;
}

void DishBST::showStatistics() const {
  std::cout << "Balance factor: " << getBalanceFactor(root) << std::endl;
  printNodes();
}

void DishBST::printNodes() const {
  printNodeHelper(root);
}

void DishBST::printNodeHelper(DishNode *node) const {
  std::cout << node->orderCount << " | izq: " << (node->left != nullptr ? node->left->orderCount : -1) << " | der: " << (node->right != nullptr ? node->right->orderCount : -1) << std::endl;
  if (node->left != nullptr) printNodeHelper(node->left);
  if (node->right != nullptr) printNodeHelper(node->right);
}

