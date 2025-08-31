#include <iostream>
#include "CustomString.hpp"
#include "Order.hpp"

Order::Order() {
    date = "";
    restaurant = "";
    order = "";
    price = 0;
    numberDate = 0;
}
Order::Order(String date, String restaurant, String order, int price, long long numberDate)
    : date(date), restaurant(restaurant), order(order), price(price),numberDate(numberDate) {
   
}

String Order::getDate() const{
    return this -> date;
}

String Order::getRestaurant() const{
    return this -> restaurant;
}

String Order::getOrder() const{
    return this ->  order;
}

int Order::getPrice() const{
    return this -> price;
}

long long Order::getNumberDate() const{
    return this -> numberDate;
}

