#ifndef DISH_HPP
#define DISH_HPP

#include "CustomString.hpp"

class Dish {
public:
    Dish();
    Dish(String name);
    String getName() const;
    int getTotalOrders() const;
    void addOrder();
private:
    String name;
    int totalOrders = 0;
};

#endif
