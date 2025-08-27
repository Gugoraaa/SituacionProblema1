#include <iostream>
#pragma once

class Order {
public:
    Order(std::string date, std::string restaurant, std::string order, int price, float numberDate);
    std::string getDate() ;
    std::string getRestaurant() ;
    std::string getOrder() ;
    int getPrice() ;
    

private:
    std::string date;
    std::string restaurant;
    std::string order;
    float numberDate; 
    int price;
};
