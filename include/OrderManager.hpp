#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP
#include <Order.hpp>

class OrderManager {
public:
    OrderManager();
    bool loadOrders(const String & filename);
    void sortOrders();
    void filterOrdersByDate(const String & startDate,const String & endDate, bool details = true);
    void filterOrdersByDate(const char *startDate, const char *endDate, bool details = true);
    void displayOrders(size_t from, size_t count);
    // void saveToFile( String& filename) ;
    void printOrders() const;

private:
    Order parseLine(String& line);
    int findOrder(long long val,bool exact,bool last) const;
    int orderCount = 0;
    static const int MAX_ORDERS = 11000; 
    Order orders[MAX_ORDERS]; 
    int partition(Order* arr, int low, int high);
    void quickSort(Order* arr, int low, int high);

};

#endif  