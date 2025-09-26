//

#ifndef C1B09453_D042_4488_AB90_C08EEBC60004
#define C1B09453_D042_4488_AB90_C08EEBC60004
// Created by Brian Roberto Gómez Martínez on 26/08/25.
//

#ifndef CUSTOMSTRING_H
#define CUSTOMSTRING_H
#include <iostream>

class String
{
private:
    char *value;
    size_t len;

public:
    static const unsigned int npos;

    // Constructor sin parametros
    String();

    // Constructores con parametros
    String(const char *a);
    String(const String &other);

    size_t length() const;
    unsigned int find(const String& sub, unsigned int pos = 0) const;
    unsigned int find(const char& sub, unsigned int pos = 0) const;
    size_t find_first_not_of(const char* s, size_t pos) const;
    operator const char*() const;
    String substr(size_t from,size_t count) const;
    String substr(size_t from) const;
    const char* c_str() const;

    // Operadores sobrecargados
    const char &operator[](size_t index) const;
    String &operator=(const char *str);
    String &operator=(const String &other);
    bool operator==(const String &other) const;
    bool operator==(const char *chars) const;
    explicit operator bool() const;
    String operator+(const String &other) const;
    friend std::ostream &operator<<(std::ostream &os, const String &str);

    // Destructor de la clase
    ~String();

    char* begin();
    char* end();
    const char* begin() const;
    const char* end() const;
};
std::istream &getline(std::istream &is, String &str);
String operator+(const char* lhs, const String& rhs);


#endif // CUSTOMSTRING_H

#endif /* C1B09453_D042_4488_AB90_C08EEBC60004 */
