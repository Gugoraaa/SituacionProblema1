//
// Created by Brian Roberto Gómez Martínez on 26/08/25.
//

#include "CustomString.hpp"

const unsigned int String::npos = -1;

/*
    funcion: String (Constructor por defecto)
    Descripcion: Inicializa un objeto String como una cadena vacía ("").
    Parametros: Ninguno
    Return: N/A
    Complejidad: O(1)
*/
String::String() : value(new char[1]{'\0'}), len(0) {}

/*
    funcion: String (Constructor con const char*)
    Descripcion: Inicializa un objeto String a partir de una cadena de caracteres estilo C (terminada en nulo).
    Parametros:
        - a (const char*): Puntero a la cadena de caracteres para inicializar el objeto.
    Return: N/A
    Complejidad: O(n), donde n es la longitud de la cadena 'a'.
*/
String::String(const char *a)
{
    if (a == nullptr)
    {
        len = 0;
        value = new char[1];
        value[0] = '\0';
        return;
    }

    unsigned int temp_len = 0;
    while (a[temp_len] != '\0')
    {
        temp_len++;
    }
    len = temp_len;
    value = new char[len + 1];

    for (unsigned int i = 0; i < len; ++i)
    {
        value[i] = a[i];
    }
    value[len] = '\0';
}

/*
    funcion: String (Constructor de copia)
    Descripcion: Crea una copia profunda de otro objeto String, asignando nueva memoria.
    Parametros:
        - other (const String&): El objeto String que se va a copiar.
    Return: N/A
    Complejidad: O(n), donde n es la longitud de la cadena 'other'.
*/
String::String(const String &other) : len(other.len)
{
    value = new char[len + 1];
    for (unsigned int i = 0; i < len; ++i)
    {
        value[i] = other.value[i];
    }
    value[len] = '\0';
}

/*
    funcion: length
    Descripcion: Devuelve la cantidad de caracteres en la cadena.
    Parametros: Ninguno
    Return: (size_t) La longitud de la cadena (sin contar el carácter nulo).
    Complejidad: O(1)
*/
size_t String::length() const
{
    return len;
}

/*
    funcion: find
    Descripcion: Busca la primera ocurrencia de una subcadena a partir de una posición.
    Parametros:
        - sub (const String&): La subcadena a buscar.
        - pos (unsigned int): La posición inicial para la búsqueda.
    Return: (unsigned int) El índice de inicio de la subcadena encontrada, o String::npos si no se encuentra.
    Complejidad: O(n*m), donde n es la longitud de la cadena y m la de la subcadena.
*/
unsigned int String::find(const String& sub, unsigned int pos) const {
    if (sub.len == 0) {
        return pos < len ? pos : len;
    }
    if (sub.len > len) {
        return npos;
    }

    for (unsigned int i = pos; i <= len - sub.len; ++i) {
        bool found = true;
        for (unsigned int j = 0; j < sub.len; ++j) {
            if (value[i + j] != sub.value[j]) {
                found = false;
                break;
            }
        }
        if (found) {
            return i;
        }
    }

    return npos;
}

/*
    funcion: find (sobrecarga)
    Descripcion: Busca la primera ocurrencia de un carácter a partir de una posición.
    Parametros:
        - sub (const char&): El carácter a buscar.
        - pos (unsigned int): La posición inicial para la búsqueda.
    Return: (unsigned int) El índice del carácter encontrado, o String::npos si no se encuentra.
    Complejidad: O(n), donde n es la longitud de la cadena.
*/
unsigned int String::find(const char& sub, unsigned int pos) const {
    char temp[2] = {sub, '\0'};
    return find(String(temp), pos);
}

/*
    funcion: find_first_not_of
    Descripcion: Busca el primer carácter en la cadena que no coincide con ninguno de los caracteres en un conjunto dado.
    Parametros:
        - s (const char*): Cadena de estilo C con los caracteres a evitar.
        - pos (size_t): La posición inicial para la búsqueda.
    Return: (size_t) El índice del primer carácter no encontrado en 's', o String::npos si todos coinciden.
    Complejidad: O(n*m), donde n es la longitud de la cadena y m la del conjunto 's'.
*/
size_t String::find_first_not_of(const char* s, size_t pos) const {
    if (pos >= len) {
        return npos;
    }
    for (size_t i = pos; i < len; ++i) {
        bool match = false;
        for (size_t j = 0; s[j] != '\0'; ++j) {
            if (value[i] == s[j]) {
                match = true;
                break;
            }
        }
        if (!match) {
            return i;
        }
    }
    return npos;
}

/*
    funcion: substr
    Descripcion: Extrae una subcadena de la cadena actual.
    Parametros:
        - from (const size_t): El índice de inicio de la subcadena.
        - count (const size_t): El número de caracteres a extraer.
    Return: (String) Un nuevo objeto String con la subcadena extraída.
    Complejidad: O(k), donde k es el tamaño de la subcadena a crear ('count').
*/
String String::substr(const size_t from,const size_t count) const{
    char* buffer = new char[count+1];
    for (int i = 0; i < count;i++) {
        buffer[i] = value[from+i];
    }
    buffer[count] = '\0';
    return {buffer};
}

/*
    funcion: substr (sobrecarga)
    Descripcion: Extrae una subcadena desde una posición hasta el final de la cadena.
    Parametros:
        - from (const size_t): El índice de inicio de la subcadena.
    Return: (String) Un nuevo objeto String con la subcadena extraída.
    Complejidad: O(k), donde k es la longitud de la subcadena creada (len - from).
*/
String String::substr(const size_t from) const{
    return substr(from, len - from);
}

/*
    funcion: c_str
    Descripcion: Devuelve un puntero constante a la representación interna de la cadena como un arreglo de caracteres terminado en nulo.
    Parametros: Ninguno
    Return: (const char*) Puntero a la cadena estilo C.
    Complejidad: O(1)
*/
const char *String::c_str() const {
    return value;
}

/*
    funcion: operator[]
    Descripcion: Permite acceder a un carácter de la cadena por su índice.
    Parametros:
        - index (const size_t): Índice del carácter a acceder.
    Return: (const char&) Referencia constante al carácter en la posición especificada.
    Complejidad: O(1)
*/
const char &String::operator[](const size_t index) const{

    return value[index];
}

/*
    funcion: operator+
    Descripcion: Concatena esta cadena con otra.
    Parametros:
        - other (const String&): La cadena a añadir al final de la actual.
    Return: (String) Un nuevo objeto String que es el resultado de la concatenación.
    Complejidad: O(n+m), donde n y m son las longitudes de las dos cadenas.
*/
String String::operator+(const String &other) const
{
    const unsigned int new_len = other.length() + len;
    char *buffer = new char[new_len + 1];
    int i = 0;
    for (; i < len; i++)
    {
        buffer[i] = this->value[i];
    }
    for (int j = 0; j + i < new_len; ++j)
    {
        buffer[i + j] = other.value[j];
    }
    buffer[new_len] = '\0';
    const String newString(buffer);
    delete[] buffer;
    return newString;
}

/*
    funcion: operator=
    Descripcion: Asigna el contenido de una cadena estilo C a este objeto String.
    Parametros:
        - a (const char*): La cadena de caracteres a asignar.
    Return: (String&) Referencia a este mismo objeto.
    Complejidad: O(n), donde n es la longitud de la cadena 'a'.
*/
String &String::operator=(const char *a)
{
    delete[] value;

    if (a == nullptr)
    {
        len = 0;
        value = new char[1];
        value[0] = '\0';
        return *this;
    }

    unsigned int temp_len = 0;
    while (a[temp_len] != '\0')
    {
        temp_len++;
    }
    len = temp_len;
    value = new char[len + 1];

    for (unsigned int i = 0; i < len; ++i)
    {
        value[i] = a[i];
    }
    value[len] = '\0';
    return *this;
}

/*
    funcion: operator= (sobrecarga de copia)
    Descripcion: Realiza una asignación de copia profunda desde otro objeto String.
    Parametros:
        - other (const String&): El objeto String del cual se copiará el contenido.
    Return: (String&) Referencia a este mismo objeto.
    Complejidad: O(n), donde n es la longitud de la cadena 'other'.
*/
String &String::operator=(const String &other)
{
    if (this == &other) {
        return *this;
    }
    delete[] value;
    len = other.len;
    value = new char[len + 1];
    for (unsigned int i = 0; i < len; ++i) {
        value[i] = other.value[i];
    }
    value[len] = '\0';
    return *this;
}

/*
    funcion: operator==
    Descripcion: Compara si dos objetos String son idénticos.
    Parametros:
        - other (const String&): El otro objeto String para la comparación.
    Return: (bool) True si las cadenas son iguales, false en caso contrario.
    Complejidad: O(n), donde n es la longitud de las cadenas.
*/
bool String::operator==(const String &other) const
{
    bool isEqual = true;
    if (len != other.len)
        return false;
    for (int i = 0; i < len; i++)
    {
        if (value[i] != other.value[i])
        {
            isEqual = false;
            break;
        };
    }
    return isEqual;
}

/*
    funcion: operator== (sobrecarga con const char*)
    Descripcion: Compara si un String es idéntico a una cadena estilo C.
    Parametros:
        - chars (const char*): La cadena de caracteres para la comparación.
    Return: (bool) True si las cadenas son iguales, false en caso contrario.
    Complejidad: O(n), donde n es la longitud de las cadenas.
*/
bool String::operator==(const char *chars) const {
  return *this == String(chars);
}

/*
    funcion: operator!=
    Descripcion: Compara si dos objetos String son distintos.
    Parametros:
        - other (const String&): El otro objeto String para la comparación.
    Return: (bool) False si las cadenas son iguales, true en caso contrario.
    Complejidad: O(n), donde n es la longitud de las cadenas.
*/
bool String::operator!=(const String &other) const {
  return !(*this == other);
}

/*
    funcion: operator!= (sobrecarga con const char*)
    Descripcion: Compara si un String es distinta a una cadena estilo C.
    Parametros:
        - chars (const char*): La cadena de caracteres para la comparación.
    Return: (bool) False si las cadenas son iguales, true en caso contrario.
    Complejidad: O(n), donde n es la longitud de las cadenas.
*/
bool String::operator!=(const char *chars) const {
  return !(*this == chars);
}


/*
    funcion: operator bool
    Descripcion: Permite evaluar un objeto String en un contexto booleano.
    Parametros: Ninguno
    Return: (bool) True si la cadena no está vacía, false si lo está.
    Complejidad: O(1)
*/
String::operator bool() const
{
    return len != 0;
}

/*
    funcion: operator const char*
    Descripcion: Permite la conversión implícita de un objeto String a un const char*.
    Parametros: Ninguno
    Return: (const char*) Puntero a la cadena interna de estilo C.
    Complejidad: O(1)
*/
 String::operator const char *() const {
 return value;
 }

/*
    funcion: operator<< (función no miembro)
    Descripcion: Sobrecarga del operador de inserción para imprimir un objeto String en un stream de salida.
    Parametros:
        - os (std::ostream&): El stream de salida (ej. std::cout).
        - str (const String&): El objeto String a imprimir.
    Return: (std::ostream&) Referencia al stream de salida.
*/
std::ostream &operator<<(std::ostream &os, const String &str)
{
    os << str.value;
    return os;
}

/*
    funcion: getline (función no miembro)
    Descripcion: Lee una línea completa de un stream de entrada y la guarda en un objeto String.
    Parametros:
        - is (std::istream&): El stream de entrada (ej. std::cin).
        - str (String&): El objeto String donde se almacenará la línea leída.
    Return: (std::istream&) Referencia al stream de entrada.
*/
std::istream &getline(std::istream &is, String &str) {
    char ch;
    size_t size = 0;
    size_t capacity = 128;
    char* buffer = new char[capacity];

    while (is.get(ch) && ch != '\n') {
        if (size == capacity - 1) {
            capacity *= 2;
            char* new_buffer = new char[capacity];
            for (size_t i = 0; i < size; ++i) {
                new_buffer[i] = buffer[i];
            }
            delete[] buffer;
            buffer = new_buffer;
        }
        buffer[size++] = ch;
    }

    buffer[size] = '\0';

    str = buffer;

    delete[] buffer;
    return is;
}

/*
    funcion: operator+ (función no miembro)
    Descripcion: Permite la concatenación cuando una cadena estilo C está a la izquierda del operador.
    Parametros:
        - lhs (const char*): La cadena de la izquierda.
        - rhs (const String&): El objeto String de la derecha.
    Return: (String) Un nuevo objeto String con el resultado de la concatenación.
*/
String operator+(const char* lhs, const String& rhs) {
    return String(lhs) + rhs;
}

/*
    funcion: toUpperCase
    Descripcion: Convierte todos los caracteres alfabéticos de la cadena a mayúsculas.
    Parametros: Ninguno
    Return: (String) Un nuevo objeto String con todos los caracteres en mayúsculas.
    Complejidad: O(n), donde n es la longitud de la cadena.
*/
String String::toUpperCase() const {
    char* buffer = new char[len + 1];
    
    for (unsigned int i = 0; i < len; ++i) {
        char c = value[i];
        
        if (c >= 'a' && c <= 'z') {
            buffer[i] = c - 'a' + 'A';
        } else {
            buffer[i] = c;
        }
    }
    buffer[len] = '\0';
    
    String result(buffer);
    delete[] buffer;
    return result;
}

/*
    funcion: toLowerCase
    Descripcion: Convierte todos los caracteres alfabéticos de la cadena a minúsculas.
    Parametros: Ninguno
    Return: (String) Un nuevo objeto String con todos los caracteres en minúsculas.
    Complejidad: O(n), donde n es la longitud de la cadena.
*/
String String::toLowerCase() const {
    char* buffer = new char[len + 1];
    
    for (unsigned int i = 0; i < len; ++i) {
        char c = value[i];
        if (c >= 'A' && c <= 'Z') {
            buffer[i] = c - 'A' + 'a';
        } else {
            buffer[i] = c;
        }
    }
    buffer[len] = '\0';
    
    String result(buffer);
    delete[] buffer;
    return result;
}

// --- Iteradores ---
char* String::begin() {
    return value;
}

char* String::end() {
    return value + len;
}

const char* String::begin() const {
    return value;
}

const char* String::end() const {
    return value + len;
}
// --- Fin de Iteradores ---

/*
    funcion: ~String (Destructor)
    Descripcion: Libera la memoria dinámica asignada para almacenar la cadena.
    Parametros: Ninguno
    Return: N/A
*/
String::~String()
{
    delete[] value;
}