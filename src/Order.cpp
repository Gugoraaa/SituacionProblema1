#include <iostream>
#include "Order.hpp"

Order::Order() {
    date = "";
    restaurant = "";
    order = "";
    price = 0;
    numberDate = 0;
}
Order::Order(std::string date, std::string restaurant, std::string order, int price, long long numberDate)
    : date(date), restaurant(restaurant), order(order), price(price),numberDate(numberDate) {
   
}

std::string Order::getDate() const{
    return this -> date;
}

std::string Order::getRestaurant() const{
    return this -> restaurant;
}

std::string Order::getOrder() const{
    return this ->  order;
}

int Order::getPrice() const{
    return this -> price;
}

long long Order::getNumberDate() const{
    return this -> numberDate;
}

