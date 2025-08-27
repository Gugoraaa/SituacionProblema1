#pragma once
#include <iostream>
#include <Order.hpp>

class OrderManager {
public:
    bool loadOrders( std::string& filename);
    void sortOrders();
    void filterOrdersByDate( std::string& startDate,  std::string& endDate);
    void displayTop10Orders() ;
    void saveToFile( std::string& filename) ;

private:
    static const int MAX_ORDERS = 11000; 
    Order* orders[MAX_ORDERS]; 
};
