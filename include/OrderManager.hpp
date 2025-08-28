#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP
#include <iostream>
#include <Order.hpp>

class OrderManager {
public:
    OrderManager();
    bool loadOrders( std::string& filename);
    void sortOrders();
    // void filterOrdersByDate( std::string& startDate,  std::string& endDate);
    // void displayTop10Orders() ;
    // void saveToFile( std::string& filename) ;

private:
    Order parseLine(std::string& line);
    int orderCount = 0;
    static const int MAX_ORDERS = 11000; 
    Order orders[MAX_ORDERS]; 
};

#endif  