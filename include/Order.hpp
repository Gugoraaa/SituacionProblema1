#include <iostream>
#pragma once

class Order {
public:
    Order(std::string date, std::string restaurant, std::string order, int price);
    std::string getDate() ;
    std::string getRestaurant() ;
    std::string getOrder() ;
    int getPrice() ;
    int getNumberDate();
    void setNumberDate(int nDate);
private:
    std::string date;
    std::string restaurant;
    std::string order;
    float numberDate; 
    int price;
};