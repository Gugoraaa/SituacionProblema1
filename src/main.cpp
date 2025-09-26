#include "OrderManager.hpp"
#include <filesystem>
#include <iostream>
#include "CustomString.hpp"
#include <fstream>

using namespace std;

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
