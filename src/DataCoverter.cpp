#include "DataConverter.hpp"
#include <iostream>

// le da un numero tomando en cuenta el mes 
int monthToNumber( const char* month) {
    if (month[0] == 'J') {
        if (month[1] == 'a') return 1; 
        else if (month[2] == 'n') return 6; 
        else return 7; 
    } else if (month[0] == 'F') return 2; 
    else if (month[0] == 'M') {
        if (month[2] == 'r') return 3;
        else return 5; 
    } else if (month[0] == 'A') {
        if (month[1] == 'r') return 4; 
        else return 8; 
    } else if (month[0] == 'S') return 9; 
    else if (month[0] == 'O') return 10; 
    else if (month[0] == 'N') return 11; 
    else return 12;
}

// convierte el conjuto de la fecha a un long long, para que asi sea sencillo de ordenar 
long long convertToComparableDate(const char* dateStr) {
    std::string dateString(dateStr);
    
    
    std::string month = dateString.substr(0, 3);
    int monthNum = monthToNumber(month.c_str());
    
    size_t dayStart = 3;
    while (dayStart < dateString.length() && dateString[dayStart] == ' ') {
        dayStart++;
    }
    
    size_t dayEnd = dayStart;
    while (dayEnd < dateString.length() && dateString[dayEnd] != ' ') {
        dayEnd++;
    }
    
    std::string dayStr = dateString.substr(dayStart, dayEnd - dayStart);
    int dayNum = 0;
    for (char c : dayStr) {
        if (c >= '0' && c <= '9') {
            dayNum = dayNum * 10 + (c - '0');
        }
    }
    
    size_t timeStart = dayEnd;
    while (timeStart < dateString.length() && dateString[timeStart] == ' ') {
        timeStart++;
    }
    
    std::string timeStr = dateString.substr(timeStart);
    
    int hour = 0, minute = 0, second = 0;
    
    size_t firstColon = timeStr.find(':');
    if (firstColon != std::string::npos) {
        std::string hourStr = timeStr.substr(0, firstColon);
        for (char c : hourStr) {
            if (c >= '0' && c <= '9') {
                hour = hour * 10 + (c - '0');
            }
        }
        
        size_t secondColon = timeStr.find(':', firstColon + 1);
        if (secondColon != std::string::npos) {
            std::string minuteStr = timeStr.substr(firstColon + 1, secondColon - firstColon - 1);
            for (char c : minuteStr) {
                if (c >= '0' && c <= '9') {
                    minute = minute * 10 + (c - '0');
                }
            }
            
            std::string secondStr = timeStr.substr(secondColon + 1);
            for (char c : secondStr) {
                if (c >= '0' && c <= '9') {
                    second = second * 10 + (c - '0');
                }
            }
        }
    }

    if (hour < 0 || hour > 23) hour = 0;
    if (minute < 0 || minute > 59) minute = 0;
    if (second < 0 || second > 59) second = 0;
    
    long long comparableDate = 20250000000000LL + 
                              (monthNum * 100000000LL) + 
                              (dayNum * 1000000LL) + 
                              (hour * 10000LL) + 
                              (minute * 100LL) + 
                              second;
    
    
    return comparableDate;
}