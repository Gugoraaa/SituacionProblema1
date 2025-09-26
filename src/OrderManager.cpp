#include "OrderManager.hpp"
#include "DataConverter.hpp"
#include "Order.hpp"
#include "CustomString.hpp"
#include <fstream>
#include <iostream>
#include <cstdlib>


/*
    Created by Gustavo Gonzalez Ramos 
    funcion: OrderManager (Constructor)
    Descripcion: Inicializa un objeto OrderManager con un contador de órdenes en 0
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(1)
*/
OrderManager::OrderManager() : orderCount(0) {  
}

/*
    Created by Gustavo Gonzalez Ramos
    funcion: loadOrders
    Descripcion: Carga las órdenes desde un archivo al arreglo de órdenes
    Parametros:
        - filename (const String&): Ruta del archivo que contiene los datos de las órdenes
    Return: (bool) true si se cargaron las órdenes correctamente, false en caso de error
    Complejidad: O(n * m)
*/
bool OrderManager::loadOrders(const String & filename) {
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


/*
    Created by Gustavo Gonzalez Ramos
    funcion: parseLine
    Descripcion: Procesa una línea de texto que contiene información de una orden y la convierte en un objeto Order
    Parametros:
        - line (String&): Línea de texto con el formato "MMM DD HH:MM:SS Restaurant, Order, Price"
    Return: (Order) Objeto Order creado a partir de los datos de la línea
    Complejidad: O(1)
*/
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

/*
    Created by Brian R. Gómez Martínez
    funcion: findOrder
    Descripcion: Realiza una búsqueda binaria para encontrar una orden por su numberDate.
                 Puede encontrar una coincidencia exacta o la más cercana, y la primera o última en caso de duplicados.
    Parametros:
        - val (long long): Número de identificación de la orden (numberDate) a buscar.
        - exact (bool): Si es true, solo devuelve coincidencias exactas. Si es false, devuelve el índice del elemento más cercano.
        - last (bool): Si hay múltiples coincidencias, true devuelve el índice de la última y false el de la primera.
    Return: (int) Índice de la orden encontrada. Devuelve -1 si no se encuentra y 'exact' es true.
    Complejidad: O(log n + k), donde n es el número de órdenes y k el número de duplicados consecutivos. En el peor caso (muchos duplicados) se aproxima a O(n).
*/
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



/*
    Created by Gustavo Gonzalez Ramos
    funcion: partition
    Descripcion: Función auxiliar para el algoritmo QuickSort que particiona el arreglo alrededor de un pivote
    Parametros:
        - arr (Order*): Arreglo de objetos Order a particionar
        - low (int): Índice inicial del subarreglo a particionar
        - high (int): Índice final del subarreglo a particionar (se usa como pivote)
    Return: (int) Índice de la posición final del pivote después de la partición
    Complejidad: O(n)
*/
int OrderManager::partition(Order* arr, int low, int high) {
    
    long long pivot = arr[high].getNumberDate();
    int i = low - 1;  

    
    for (int j = low; j < high; ++j) {
        if (arr[j].getNumberDate() <= pivot) {
            ++i;
            
            Order temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    
    Order temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;  
}


/*
    Created by Gustavo Gonzalez Ramos
    funcion: quickSort
    Descripcion: Implementa el algoritmo de ordenamiento QuickSort para ordenar un arreglo de objetos Order
    Parametros:
        - arr (Order*): Arreglo de objetos Order a ordenar
        - low (int): Índice inicial del subarreglo a ordenar
        - high (int): Índice final del subarreglo a ordenar
    Return: N/A
    Complejidad: O(n log n)
*/
void OrderManager::quickSort(Order* arr, int low, int high) {
    if (low < high) {
        
        int pi = partition(arr, low, high);

        
        quickSort(arr, low, pi - 1);  
        quickSort(arr, pi + 1, high); 
    }
}

void OrderManager::sortOrders() {
    quickSort(orders, 0, orderCount - 1);  
}

/*
    Created by Brian R. Gómez Martínez
    funcion: filterOrdersByDate
    Descripcion: Filtra y muestra en consola las órdenes que se encuentran dentro de un rango de fechas específico.
                 Utiliza búsqueda binaria para encontrar los límites del rango de manera eficiente.
    Parametros:
        - startDate (const String &): Fecha de inicio del filtro. Formato "YY/MM/DD HH:MM:SS" o similar.
        - endDate (const String &): Fecha de fin del filtro. Si se omite la hora, se considera hasta las 23:59:59 de ese día.
        - details (const bool): Si es true, imprime un conteo de los resultados encontrados antes de listarlos.
    Return: (void)
    Complejidad: O(log n + m), donde n es el total de órdenes y m es el número de órdenes dentro del rango de fechas.
*/
void OrderManager::filterOrdersByDate(const String &startDate,const String &endDate, const bool details) {
  if (orderCount == 0) throw std::invalid_argument("No orders to filter");
  if (startDate.length() < 5) throw std::invalid_argument("Invalid start date");
  if (endDate.length() < 5) throw std::invalid_argument("Invalid end date");
  String  startMonth = startDate.substr(0, 3);
  if ( startMonth!= "ene" &&  startMonth != "Feb" &&  startMonth != "Mar" && startMonth != "Abr"
    &&  startMonth != "May" &&  startMonth != "Jun" &&  startMonth != "Jul"
    &&  startMonth != "Ago" &&  startMonth != "Sep" &&  startMonth != "Oct"
    &&  startMonth != "Nov" &&  startMonth != "Dic") throw std::invalid_argument("Invalid start month. Trying using month: "+startMonth);
  String  endMonth = endDate.substr(0, 3);
  if ( endMonth!= "ene" &&  endMonth != "Feb" &&  endMonth != "Mar" && endMonth != "Abr"
    &&  endMonth != "May" &&  endMonth != "Jun" &&  endMonth != "Jul"
    &&  endMonth != "Ago" &&  endMonth != "Sep" &&  endMonth != "Oct"
    &&  endMonth != "Nov" &&  endMonth != "Dic") throw std::invalid_argument("Invalid end month. Trying using month: "+endMonth);
  String finalEndDate;
  finalEndDate = (endDate.length() <= 6 && endDate.length() >= 5? endDate + " 23:59:59" : endDate);
  const long long start = convertToComparableDate(startDate.c_str()), end = convertToComparableDate(finalEndDate.c_str());
  if (start > end) throw std::invalid_argument("Invalid date range");
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


void OrderManager::printOrders() const {
    // Check if there are orders to print
    int printLimit = (orderCount < 10) ? orderCount : 10;  // Limit to 10 orders or less
    for (int i = 0; i < printLimit; ++i) {
        std::cout << "Order " << (i + 1) << ": " << std::endl;
        std::cout << "  Date: " << orders[i].getDate() << std::endl;
        std::cout << "  Restaurant: " << orders[i].getRestaurant() << std::endl;
        std::cout << "  Order: " << orders[i].getOrder() << std::endl;
        std::cout << "  Price: " << orders[i].getPrice() << std::endl;
        std::cout << "  Date (Comparable): " << orders[i].getNumberDate() << std::endl;
        std::cout << "----------------------------------------" << std::endl;
    }
}