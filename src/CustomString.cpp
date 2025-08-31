//
// Created by Brian Roberto Gómez Martínez on 26/08/25.
//

#include "CustomString.hpp"

const unsigned int String::npos = -1;

String::String() : value(new char[1]{'\0'}), len(0) {}

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

String::String(const String &other) : len(other.len)
{
    value = new char[len + 1];
    for (unsigned int i = 0; i < len; ++i)
    {
        value[i] = other.value[i];
    }
    value[len] = '\0';
}

size_t String::length() const
{
    return len;
}

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

unsigned int String::find(const char& sub, unsigned int pos) const {
    char temp[2] = {sub, '\0'};
    return find(String(temp), pos);
}

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


String String::substr(const size_t from,const size_t count) const{
    char* buffer = new char[count+1];
    for (int i = 0; i < count;i++) {
        buffer[i] = value[from+i];
    }
    buffer[count] = '\0';
    return {buffer};
}

String String::substr(const size_t from) const{
    return substr(from, len - from);
}

const char *String::c_str() const {
    return value;
}


const char &String::operator[](const size_t index) const{

    return value[index];
}

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

bool String::operator==(const char *chars) const {
  return *this == String(chars);
}

String::operator bool() const
{
    return len != 0;
}

 String::operator const char *() const {
 return value;
 }

std::ostream &operator<<(std::ostream &os, const String &str)
{
    os << str.value;
    return os;
}

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

String operator+(const char* lhs, const String& rhs) {
    return String(lhs) + rhs;
}


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

String::~String()
{
    delete[] value;
}
