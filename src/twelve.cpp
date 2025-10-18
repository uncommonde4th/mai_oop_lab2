#include "../include/Twelve.h"
#include <algorithm>
#include <stdexcept>

void Twelve::initString(const std::string& str){
    if (str.empty()){
        size = 1;
        nums = new unsigned char[1];
        nums[0] = '0';
        return;
    }
    
    size_t start = 0;
    while (start < str.length() && str[start] == '0') {
        start++;
    }
    
    if (start == str.length()) {
        size = 1;
        nums = new unsigned char[1];
        nums[0] = '0';
        return;
    }
    
    size = str.length() - start;
    nums = new unsigned char[size];

    for (size_t i = 0; i < size; i++){
        char c = str[str.length() - 1 - i];
        if (!isValidChar(c)) {
            delete[] nums;
            throw std::invalid_argument("Неприемлимая цифра для СИ с основанием 12");
        }
        nums[i] = c;
    }
    normalize();
}

void Twelve::initNumber(unsigned int value){
    if (value == 0){
        size = 1;
        nums = new unsigned char[1];
        nums[0] = '0';
        return;
    }
    unsigned int temp = value;
    size_t num_digits = 0;
    while (temp > 0){
        temp /= base;
        num_digits++;
    }
    size = num_digits;
    nums = new unsigned char[size];

    temp = value;
    for (size_t i = 0; i < size; i++){
        nums[i] = digitToChar(temp % base);
        temp /= base;
    }
    normalize();
}

void Twelve::normalize(){
    while (size > 1 && nums[size - 1] == '0'){
        size--;
    }
}   

Twelve::Twelve() : size(1){
    nums = new unsigned char[1];
    nums[0] = '0';
}

Twelve::Twelve(const size_t& n, unsigned char t) : size(n){
    if (t >= base){
        throw std::invalid_argument("Слишком большая цифра для СИ с основанием 12");
    }
    nums = new unsigned char[size];
    for (size_t i = 0; i < size; i++){
        nums[i] = digitToChar(t);
    }
    normalize();
}

Twelve::Twelve(const std::initializer_list<unsigned char>& t) : size(t.size()){
    nums = new unsigned char[size];
    size_t i = 0;
    for (auto it = t.end(); it != t.begin(); ) {
        --it;
        if (!isValidChar(*it)) {
            delete[] nums;
            throw std::invalid_argument("Неприемлимая цифра для СИ с основанием 12");
        }
        nums[i++] = *it;
    }
    normalize();
}

Twelve::Twelve(const std::string& t){
    initString(t);
}

Twelve::Twelve(unsigned int value){
    initNumber(value);
}

Twelve::Twelve(const Twelve& other) : size(other.size) {
    nums = new unsigned char[size];
    for (size_t i = 0; i < size; i++){
        nums[i] = other.nums[i];
    }
}

Twelve::Twelve(Twelve&& other) noexcept : nums(other.nums), size(other.size) {
    other.nums = nullptr;
    other.size = 0;
}

Twelve::~Twelve() noexcept{
    delete[] nums;
}

Twelve Twelve::plus(const Twelve& other) const{
    size_t max_size = std::max(size, other.size);
    unsigned char* result_array = new unsigned char[max_size + 1];

    int carry = 0;
    size_t i = 0;
    while (i < max_size) {
        int first = (i >= size) ? 0 : charToDigit(nums[i]);
        int second = (i >= other.size) ? 0 : charToDigit(other.nums[i]);

        int sum = first + second + carry;
        result_array[i] = digitToChar(sum % base);
        carry = sum / base;

        i++;
    }

    if (carry) {
        result_array[i] = digitToChar(carry);
        max_size++;
    }

    Twelve result;
    result.size = max_size;
    result.nums = result_array;
    result.normalize();

    return result;
}

Twelve Twelve::minus(const Twelve& other) const{
    if (this->less(other)){
        throw std::logic_error("Отрицательный результат при вычитании");
    }

    size_t result_size = std::max(size, other.size);
    unsigned char* result_array = new unsigned char[result_size];

    int borrow = 0;
    size_t i = 0;
    while (i < result_size) {
        int first = (i >= size) ? 0 : charToDigit(nums[i]);
        int second = (i >= other.size) ? 0 : charToDigit(other.nums[i]);

        int diff = first - second - borrow;

        if (diff < 0) {
            diff += base;
            borrow = 1;
        } else {
            borrow = 0;
        }

        result_array[i] = digitToChar(diff);
        i++;
    }

    Twelve result;
    result.size = result_size;
    result.nums = result_array;
    result.normalize();

    return result;
}

bool Twelve::equal(const Twelve& other) const{
    if (size != other.size){
        return false;
    }
    for (size_t i = 0; i < size; i++){
        if (nums[i] != other.nums[i]){
            return false;
        }
    }
    return true;
}

bool Twelve::less(const Twelve& other) const{
    if (size < other.size) {
        return true;
    }
    if (size > other.size) {
        return false;
    }

    for (size_t i = size; i > 0; --i) {
        if (charToDigit(nums[i - 1]) < charToDigit(other.nums[i - 1])) {
            return true;
        }
        if (charToDigit(nums[i - 1]) > charToDigit(other.nums[i - 1])) {
            return false;
        }
    }

    return false;
}

bool Twelve::greater(const Twelve& other) const{
    if (size > other.size) {
        return true;
    }
    if (size < other.size) {
        return false;
    }

    for (size_t i = size; i > 0; --i) {
        if (charToDigit(nums[i - 1]) > charToDigit(other.nums[i - 1])) {
            return true;
        }
        if (charToDigit(nums[i - 1]) < charToDigit(other.nums[i - 1])) {
            return false;
        }
    }

    return false;
}

size_t Twelve::getSize() const{
    return size;
}

unsigned char Twelve::getDigit(size_t index) const{
    if (index >= size){
        throw std::out_of_range("Индекс за границами массива");
    }
    return charToDigit(nums[index]);
}

void Twelve::print() const{
    for (size_t i = size; i > 0; --i) {
        std::cout << nums[i - 1];
    }
}

std::string Twelve::toString() const{
    std::string result;
    for (size_t i = size; i > 0; --i) {
        result += nums[i - 1];
    }
    return result;
}

bool Twelve::isValidDigit(unsigned char digit){
    return digit < base;
}

bool Twelve::isValidChar(unsigned char c){
    return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'B') || (c >= 'a' && c <= 'b');
}

unsigned char Twelve::charToDigit(char c){
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'B') return c - 'A' + 10;
    if (c >= 'a' && c <= 'b') return c - 'a' + 10;
    throw std::invalid_argument("Неприемлимая цифра для СИ с основанием 12");
}

char Twelve::digitToChar(unsigned char digit){
    if (digit < 10) return '0' + digit;
    if (digit < base) return 'A' + (digit - 10);
    throw std::invalid_argument("Неприемлимая цифра для СИ с основанием 12");
}
