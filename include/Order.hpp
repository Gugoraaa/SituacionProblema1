#ifndef ORDER_HPP
#define ORDER_HPP
#include "CustomString.hpp"

class Order {
public:
    Order();
    Order(String date, String restaurant, String order, int pric, long long numberDate);
    String getDate() const;
    String getRestaurant() const;
    String getOrder() const;
    int getPrice() const;
    long long getNumberDate() const;

    /* Operadores sobrecargados; El fin de sobrecargar los operadores "<>" es para poder usar en condicionales de los
     * ciclos if - else, while y for comparaciones entre las fechas de dos objetos de tipo "Orden" */
    bool operator>(const Order Orden1) const;
    bool operator<(const Order Orden2) const;

private:
    String date;
    String restaurant;
    String order; 
    long long numberDate; 
    int price;
};

#endif 