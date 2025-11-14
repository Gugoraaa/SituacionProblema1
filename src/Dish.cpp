#include "Dish.hpp"

/*
    funcion: Dish (Constructor por defecto)
    Descripcion: Inicializa un objeto Dish con nombre vacío y contador de pedidos en cero.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(1)
*/
Dish::Dish() {
    name = "";
}

/*
    funcion: Dish (Constructor con nombre)
    Descripcion: Inicializa un objeto Dish con un nombre específico y contador de pedidos en cero.
    Parametros:
        - name (String): Nombre del platillo.
    Return: N/A
    Complejidad: O(1)
*/
Dish::Dish(String name) {
    this->name = name;
}

/*
    funcion: getName
    Descripcion: Devuelve el nombre del platillo almacenado en el objeto Dish.
    Parametros: Ninguno
    Return: (String) Nombre del platillo.
    Complejidad: O(1)
*/
String Dish::getName() const {
    return name;
}

/*
    funcion: getTotalOrders
    Descripcion: Obtiene la cantidad total de veces que se ha pedido el platillo.
    Parametros: Ninguno
    Return: (int) Número total de pedidos registrados.
    Complejidad: O(1)
*/
int Dish::getTotalOrders() const {
    return totalOrders;
}

/*
    funcion: addOrder
    Descripcion: Incrementa en uno el contador de pedidos del platillo.
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(1)
*/
void Dish::addOrder() {
    totalOrders++;
}
