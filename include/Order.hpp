#ifndef ORDER_HPP
#define ORDER_HPP
#include <iostream>

class Order {
public:
    Order();
    Order(std::string date, std::string restaurant, std::string order, int pric, long long numberDate);
    std::string getDate() const;
    std::string getRestaurant() const;
    std::string getOrder() const;
    int getPrice() const;
    long long getNumberDate() const;
private:
    std::string date;
    std::string restaurant;
    std::string order; 
    long long numberDate; 
    int price;
};

#endif 