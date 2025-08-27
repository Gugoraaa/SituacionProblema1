#include <iostream>
#include "Order.hpp"

Order::Order(std::string date, std::string restaurant, std::string order, int price)
    : date(date), restaurant(restaurant), order(order), price(price) {
    numberDate = 0;
}

std::string Order::getDate() {
    return this -> date;
}

std::string Order::getRestaurant() {
    return this -> restaurant;
}

std::string Order::getOrder() {
    return this ->  order;
}

int Order::getPrice() {
    return this -> price;
}

int Order::getNumberDate(){
    return this -> numberDate;
}

void Order::setNumberDate(int nDate){
    this -> numberDate = nDate;
    return ; 
}