#include "Dish.hpp"

Dish::Dish() {
    name = "";
}

Dish::Dish(String name) {
    this->name = name;
}

String Dish::getName() const {
    return name;
}

int Dish::getTotalOrders() const {
    return totalOrders;
}

void Dish::addOrder() {
    totalOrders++;
}
