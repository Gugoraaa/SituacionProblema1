#include <iostream>
#include "CustomString.hpp"
#include "Order.hpp"


/*
    Created by Gustavo Gonzalez Ramos
    funcion: Order (Constructor por defecto)
    Descripcion: Inicializa un objeto Order con valores predeterminados
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(1)
*/
Order::Order() {
    date = "";
    restaurant = "";
    order = "";
    price = 0;
    numberDate = 0;
}
/*
    Created by Gustavo Gonzalez Ramos
    funcion: Order (Constructor con parámetros)
    Descripcion: Inicializa un objeto Order con los valores proporcionados
    Parametros:
        - date (String): Fecha del pedido
        - restaurant (String): Nombre del restaurante
        - order (String): Descripción del pedido
        - price (int): Precio del pedido
        - numberDate (long long): Representación numérica de la fecha para ordenamiento
    Return: N/A
    Complejidad: O(1)
*/
Order::Order(String date, String restaurant, String order, int price, long long numberDate)
    : date(date), restaurant(restaurant), order(order), price(price),numberDate(numberDate) {
   
}

/*
    Created by Gustavo Gonzalez Ramos
    funcion: getDate
    Descripcion: Obtiene la fecha del pedido
    Parametros: Ninguno
    Return: (String) Fecha del pedido
    Complejidad: O(1)
*/
String Order::getDate() const{
    return this -> date;
}

/*
    Created by Gustavo Gonzalez Ramos
    funcion: getRestaurant
    Descripcion: Obtiene el nombre del restaurante
    Parametros: Ninguno
    Return: (String) Nombre del restaurante
    Complejidad: O(1)
*/
String Order::getRestaurant() const{
    return this -> restaurant;
}

/*
    Created by Gustavo Gonzalez Ramos
    funcion: getOrder
    Descripcion: Obtiene la descripción del pedido
    Parametros: Ninguno
    Return: (String) Descripción del pedido
    Complejidad: O(1)
*/
String Order::getOrder() const{
    return this ->  order;
}

/*
    Created by Gustavo Gonzalez Ramos
    funcion: getPrice
    Descripcion: Obtiene el precio del pedido
    Parametros: Ninguno
    Return: (int) Precio del pedido
    Complejidad: O(1)
*/
int Order::getPrice() const{
    return this -> price;
}

/*
    Created by Gustavo Gonzalez Ramos
    funcion: getNumberDate
    Descripcion: Obtiene la representación numérica de la fecha para ordenamiento
    Parametros: Ninguno
    Return: (long long) Valor numérico de la fecha (formato: YYYYMMDDHHMMSS)
    Complejidad: O(1)
*/
long long Order::getNumberDate() const{
    return this -> numberDate;
}

