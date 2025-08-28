#include "OrderManager.hpp"
#include "DataConverter.hpp"
#include "Order.hpp"
#include <fstream>
#include <iostream>

OrderManager::OrderManager() : orderCount(0) {
    
}

bool OrderManager:: loadOrders(std::string& filename) {
    std::ifstream file(filename);  
    std::string line;

    if (!file.is_open()) {
        return false;  
    }

    while (std::getline(file, line)) {
        if (orderCount >= MAX_ORDERS) {
            std::cerr << "No se aceptan mas de 11000 datos" << std::endl;
            break;  
        }

        
        Order newOrder = parseLine(line);  
        orders[orderCount++] = newOrder;  
    }

    file.close();
    return true;
}


Order OrderManager::parseLine(std::string& line) {
    std::string month = line.substr(0, 3);

    
    size_t day_start = 4;
    size_t day_end = line.find_first_not_of("0123456789", day_start);
    std::string day = line.substr(day_start, day_end - day_start);  

    std::string time = line.substr(day_end + 1, 8);  

    
    size_t hour_end = time.find(":");
    std::string hour = time.substr(0, hour_end);
    
    size_t minute_end = time.find(":", hour_end + 1);
    std::string minute = time.substr(hour_end + 1, minute_end - hour_end - 1);
    
    std::string second = time.substr(minute_end + 1);

    
    if (hour.length() == 1) hour = "0" + hour;
    if (minute.length() == 1) minute = "0" + minute;
    if (second.length() == 1) second = "0" + second;

    
    std::string formattedTime = hour + ":" + minute + ":" + second;

    std::string date = month + " " + day + " " + formattedTime;

    
    size_t r_pos = line.find("R:") + 2;  
    size_t o_pos = line.find("O:");

    
    std::string restaurant = line.substr(r_pos, o_pos - r_pos);  

    
    size_t dish_start = o_pos + 2;
    size_t price_start = line.find("(") + 1;  
    size_t price_end = line.find(")");  


    std::string order = line.substr(dish_start, price_start - dish_start - 1);  

    
    int price = std::stoi(line.substr(price_start, price_end - price_start));

    long long numberDate = convertToComparableDate(date.c_str());
    return Order(date, restaurant, order, price, numberDate);
}





void OrderManager::sortOrders() {
    // Bubble sort: Compare and swap elements based on numberDate
    for (int i = 0; i < orderCount - 1; ++i) {
        for (int j = 0; j < orderCount - i - 1; ++j) {
            if (orders[j].getNumberDate() > orders[j + 1].getNumberDate()) {
                Order temp = orders[j];
                orders[j] = orders[j + 1];
                orders[j + 1] = temp;
            }
        }
    }
}

