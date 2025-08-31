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
private:
    String date;
    String restaurant;
    String order; 
    long long numberDate; 
    int price;
};

#endif 