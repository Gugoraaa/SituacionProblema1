#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP
#include <Order.hpp>
#include <Dish.hpp>

class OrderManager {
public:
    // Constructor sin parametros
    OrderManager();

    // Metodos para el manejo del contenido de los archivos de texto
    bool loadOrders(const String & filename);
    void sortOrders();
    void filterOrdersByDate(const String & startDate,const String & endDate, bool details = true);
    void filterOrdersByDate(const char *startDate, const char *endDate, bool details = true);
    void displayOrders(size_t from, size_t count);
    // void saveToFile( String& filename) ;

    // Metodo para mostrar las ordenes
    void printOrders() const;

    //metodos para agregar dishes 
    void addDish(String name);
    Dish* findDish(String name);
    void printDishes() const;
private:
    Order parseLine(String& line);
    int findOrder(long long val,bool exact,bool last) const;
    int orderCount = 0;
    static const int MAX_ORDERS = 11000; 
    Order orders[MAX_ORDERS]; 
    Dish dishes[MAX_ORDERS];
    int partition(Order* arr, int low, int high);
    void quickSort(Order* arr, int low, int high);
    int dishesCount = 0;
    

};

#endif  