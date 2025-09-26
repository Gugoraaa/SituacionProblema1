#include "OrderManager.hpp"
#include <filesystem>
#include <iostream>
#include "CustomString.hpp"
#include <fstream>

using namespace std;

/* Funcionamiento basico del programa:
 *
 * 1. Se abre el archivo de texto "orders.txt", si no se abre, el programa lanza un mensaje de error
 * 2. Cada línea de texto del archivo se almacena como un elemento individual dentro de un arreglo/vector
 * 3. Luego un algoritmo de ordenamiento se encarga de ordenar la información del arreglo
 * 4. La información ya ordenada se escribe y almacena después en el archivo de texto "salida.txt"
 * 5. Ahora el programa leé el archivo "salida.txt" y despliega las primeras 10 órdenes en pantalla
 * 6. Después el programa pregunta al usuario que ordenes, dentro de que rango de fechas les gustaría ver
 * 7. El usuario inserta la fecha y hora inicial, y la fecha y hora final
 * 8. Mediante un algoritmo de búsqueda el archivo lee el archivo arreglo ordenado (¿O el archivo "salida.txt"),
 * busca las ordenes que se encuentran en dicho rango de fechas y las muestra en pantalla
 * 9. El programa pregunta al usuario si quiere guardar los resultados de búsqueda en un archivo de texto con el
 * nombre que el usuario quiera ponerle
 * 10. Si la respuesta es 'sí', el programa crea el archivo o sobreescribe el existente en caso de tener el mismo
 * nombre y el programa finaliza
 * 11. Si la respuesta es 'no', se destruyen todos los objetos del programa para liberar memoria, incluyendo el arreglo
 * en el que se almacenaron los resultado de búsqueda y el programa finaliza
 *
 * */

 /*
    Created by Axel Omar Lugo Aguilera
    funcion: main
    Descripcion: Función principal del programa. 
                 Carga los registros desde un archivo, las ordena cronológicamente, 
                 muestra resultados en consola y permite búsquedas por rango de fechas.
                 También guarda los resultados en archivos de salida.
    Parametros: Ninguno
    Return: (int) 0 si el programa finaliza correctamente, 1 en caso de error.
    Complejidad: O(n log n + m), 
                 donde n es el número total de órdenes (por QuickSort y búsqueda binaria) 
                 y m el número de órdenes dentro del rango consultado.
*/

int main() {

  OrderManager manager;

  const String inputFile = "orders.txt";
  if (!manager.loadOrders(inputFile)) {
    cerr << "Error: no se pudo abrir " << inputFile <<endl;
    return 1;
  }

  manager.sortOrders();

  cout << "---- Primeros 10 registros ----- "<< endl;
  manager.printOrders(); 

  {
    ofstream out("salida.txt");
    if (!out.is_open()) {
      cerr << "Error: no se pudo abrir salida.txt"<< endl;
      return 1;
    }
    std::streambuf* old_buf = cout.rdbuf(out.rdbuf()); 

    manager.filterOrdersByDate("ene 1 00:00:00", "Dic 31 23:59:59",false);

    cout.rdbuf(old_buf); 
    cout << "\nArchivo 'salida.txt' ordenada "
            "completa.\n";
  }

  cout << "\n---- Busqueda por rango de fechas -----" << endl;
  cout << "Formato: 'Mon DD HH:MM:SS' (ej: 'Jun 7 14:23:05')" << endl;

  String startDate, endDate;
  cout << "Fecha de inicio: ";
  getline(cin, startDate);
  cout << "Fecha de fin: ";
  getline(cin, endDate);

  cout << "\n--- Resultados dentro del rango ---" << endl;
  try {
    manager.filterOrdersByDate(startDate, endDate,true); 
  } catch (const std::exception &ex) {
    cerr << "Error en la busqueda: " << ex.what() << endl;
    return 1;
  }

  cout << "\n¿Deseas guardar estos resultados en un archivo? (s/n): ";
  String opcion;
  getline(cin, opcion);

  if (opcion == "s" || opcion == "S") {
    cout << "Nombre de archivo de salida (ej. 'busqueda.txt'): ";
    String outName;
    getline(cin, outName);

    ofstream outSearch(outName.c_str());
    if (!outSearch.is_open()) {
      cerr << "Error: no se pudo abrir '" << outName << "' para escribir."
           << endl;
      return 1;
    }

    std::streambuf* old_buf = cout.rdbuf(outSearch.rdbuf());
    try {
      manager.filterOrdersByDate(startDate, endDate,false);
    } catch (const std::exception &ex) {
      cout.rdbuf(old_buf);
      cerr << "Error al guardar la busqueda: " << ex.what() << endl;
      return 1;
    }
    cout.rdbuf(old_buf);

    cout << "Resultados guardados en '" << outName << "'.\n";
  }

  cout << "\nListo.\n";
  return 0;
}
