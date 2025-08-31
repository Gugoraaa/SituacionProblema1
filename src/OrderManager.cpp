#include "OrderManager.hpp"
#include "DataConverter.hpp"
#include "Order.hpp"
#include "CustomString.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>


OrderManager::OrderManager() : orderCount(0) {
    
}

bool OrderManager:: loadOrders(const String & filename) {
    std::ifstream file(filename);
    String line;

    if (!file.is_open()) {
        return false;  
    }

    while (getline(file, line)) {
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


Order OrderManager::parseLine(String& line) {
    String month = line.substr(0, 3);

    
    size_t day_start = 4;
    size_t day_end = line.find_first_not_of("0123456789", day_start);
    String day = line.substr(day_start, day_end - day_start);  

    String time = line.substr(day_end + 1, 8);  

    
    size_t hour_end = time.find(":");
    String hour = time.substr(0, hour_end);
    
    size_t minute_end = time.find(":", hour_end + 1);
    String minute = time.substr(hour_end + 1, minute_end - hour_end - 1);
    
    String second = time.substr(minute_end + 1);

    
    if (hour.length() == 1) hour = "0" + hour;
    if (minute.length() == 1) minute = "0" + minute;
    if (second.length() == 1) second = "0" + second;

    
    String formattedTime = hour + ":" + minute + ":" + second;

    String date = month + " " + day + " " + formattedTime;

    
    size_t r_pos = line.find("R:") + 2;  
    size_t o_pos = line.find("O:");

    
    String restaurant = line.substr(r_pos, o_pos - r_pos);  

    
    size_t dish_start = o_pos + 2;
    size_t price_start = line.find("(") + 1;  
    size_t price_end = line.find(")");  


    String order = line.substr(dish_start, price_start - dish_start - 1);  

    
    int price = std::atoi(line.substr(price_start, price_end - price_start));

    long long numberDate = convertToComparableDate(date.c_str());
    return {date, restaurant, order, price, numberDate};
}


int OrderManager::findOrder(const long long val,const bool exact = true,const bool last = false) const {
  const int n = orderCount;
  if (val < orders[0].getNumberDate()) return exact ?  -1 :  0;
  if (val > orders[n-1].getNumberDate()) return exact ?  -1 :  n;
  bool found = false;
  int findIndex = -1;

  int low = 0;
  int high = n-1;
  while (low<= high && !found) {
    if (const int mid = low + (high - low) / 2; orders[mid].getNumberDate() == val) {
      found = true;
      findIndex = mid;
    } else if (orders[mid].getNumberDate() > val) {
      high = mid - 1;
    } else{
      low = mid + 1;
    }
  }

  if (!exact && findIndex == -1) {
    if (low != 0) {
      const long long diff = abs(val - orders[low].getNumberDate());
      if (const long long diff2 = abs(val - orders[low - 1].getNumberDate());
          diff2 < diff) findIndex = low - 1;
      else findIndex = low;
    }else return 0;
  }else if (findIndex == -1) return -1;

  if (last) {
    bool isLast = false;
    while (!isLast) {
      if (findIndex+1 > n-1 || orders[findIndex].getNumberDate() != orders[findIndex+1].getNumberDate()) {
        isLast = true;
      } else {
        findIndex++;
      }
    }
    return findIndex;
  }else {
    bool isFirst = false;
    while (!isFirst) {
      if (findIndex-1 < 0 || orders[findIndex].getNumberDate() != orders[findIndex-1].getNumberDate()) {
        isFirst = true;
      } else {
        findIndex--;
      }
    }
    return findIndex;
  }
}



void OrderManager::sortOrders() {
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

void OrderManager::filterOrdersByDate(const String &startDate,const String &endDate, const bool details) {
  if (startDate.length() < 5) throw std::invalid_argument("Invalid start date");
  if (endDate.length() < 5) throw std::invalid_argument("Invalid end date");
  String finalEndDate;
  finalEndDate = (endDate.length() <= 6 && endDate.length() >= 5? endDate + " 23:59:59" : endDate);
  const long long start = convertToComparableDate(startDate.c_str()), end = convertToComparableDate(finalEndDate.c_str());
  const int first = findOrder(start, false, false), last = findOrder(end,false,true);
  int count = last - first;
  if(details) std::cout << count << " results founded"<< std::endl;
  for (int i = first; i <= last; i++) {
    std::cout << orders[i].getDate() << " " << orders[i].getRestaurant() << " " << orders[i].getOrder() << " " << orders[i].getPrice() << std::endl;
  }
}

void OrderManager::filterOrdersByDate(const char *startDate,const char *endDate, const bool details) {
  return this->filterOrdersByDate(String(startDate), String(endDate), details);
}


void OrderManager::displayOrders(const size_t from,const size_t count){
  for (int i = from; i < from + count; i++) {
    std::cout << orders[i].getDate() << " " << orders[i].getRestaurant() << " " << orders[i].getOrder() << " " << orders[i].getPrice() << std::endl;
  }
}
