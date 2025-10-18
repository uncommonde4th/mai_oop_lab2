#ifndef TWELVE_H
#define TWELVE_H

#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <stdexcept>
#include <algorithm>
#include <initializer_list>

class Twelve{
private:
    static const unsigned int base = 12;
    unsigned char* nums;
    size_t size;

    void initString(const std::string& str);
    void initNumber(unsigned int value);
    void normalize();
    
    static bool isValidChar(unsigned char c);

public:
    Twelve();
    Twelve(const size_t& n, unsigned char t = 0);
    Twelve(const std::initializer_list<unsigned char>& t);
    Twelve(const std::string& t);
    Twelve(unsigned int value);
    Twelve(const Twelve& other);
    Twelve(Twelve&& other) noexcept;
    ~Twelve() noexcept;

    Twelve& operator=(const Twelve& other);
    Twelve& operator=(Twelve&& other) noexcept;

    Twelve plus(const Twelve& other) const;
    Twelve minus(const Twelve& other) const;
    Twelve copy() const;

    Twelve& plusAssign(const Twelve& other);
    Twelve& minusAssign(const Twelve& other);

    bool equal(const Twelve& other) const;
    bool less(const Twelve& other) const;
    bool greater(const Twelve& other) const;

    size_t getSize() const;
    unsigned char getDigit(size_t index) const;

    void print() const;
    std::string toString() const;

    static bool isValidDigit(unsigned char digit);
    static unsigned char charToDigit(char c);
    static char digitToChar(unsigned char digit);
};

#endif
