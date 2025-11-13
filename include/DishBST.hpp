#ifndef BE28BB73_AE78_407D_B280_4A0AAC1EADCB
#define BE28BB73_AE78_407D_B280_4A0AAC1EADCB
#ifndef DISHBST_HPP
#define DISHBST_HPP

#include "CustomString.hpp"
#include "Dish.hpp"

/*
    Clase: DishNode
    Descripcion: Nodo de un árbol binario de búsqueda que almacena platillos.
                 La llave es el número de pedidos del platillo.
*/
class DishNode {
public:
    int orderCount;           // Número de pedidos
    Dish* dishes;             // Array dinámico de platillos con la misma cantidad de pedidos
    int dishCapacity;         // Capacidad del array
    int dishCount;            // Cantidad actual de platillos en el array
    DishNode* left;
    DishNode* right;

    DishNode(int count, const Dish& dish);
    ~DishNode();
    void addDish(const Dish& dish);
    void resize();
};

/*
    Clase: DishBST
    Descripcion: Árbol binario de búsqueda para almacenar platillos organizados por número de pedidos.
*/

class DishBST {
public:
    DishBST();
    ~DishBST();

    void insert(const Dish& dish);
    void findMostOrdered(Dish*& resultDishes, int& resultCount) const;
    void printInOrder() const;
    void printInReverseOrder() const;
    int getMaxOrderCount() const;
    void getTopNDishes(int n, Dish*& resultDishes, int& resultCount) const;
    void showStatistics() const;
    void printNodes() const;

private:
    DishNode* root;

    DishNode* insertNode(DishNode* node, const Dish& dish);
    void deleteTree(DishNode* node);
    void balanceWholeTree(DishNode*& node);
    void balanceSubtree(DishNode*& node);
    void rotateLeft(DishNode*& node);
    void rotateRight(DishNode*& node);
    void printInOrderHelper(DishNode* node) const;
    void printInReverseOrderHelper(DishNode* node) const;
    int getHeight(DishNode* node) const;
    int findMaxOrderCount(DishNode* node) const;
    int getBalanceFactor(DishNode* node) const;
    void collectDishesByCount(DishNode* node, int targetCount, Dish*& resultDishes, int& resultCount) const;
    void collectTopNDishes(DishNode* node, int& remaining, Dish*& resultDishes, int& resultCount) const;
    void printNodeHelper(DishNode* node) const;

};

#endif // DISHBST_HPP


#endif /* BE28BB73_AE78_407D_B280_4A0AAC1EADCB */
