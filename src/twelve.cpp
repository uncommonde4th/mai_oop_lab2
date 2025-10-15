#include "../include/Twelve.h"

void Twelve::initString(const std::string& str){
        if (str.empty()){
                size = 1;
                nums = new unsigned char[1];
                nums[0] = 0;
                return;
        }
        size = str.length();
        nums = new unsigned char[size];

        for (size_t i = 0; i < size; i++){
                char c = str[size - 1 - i];
                nums[i] = charToDigit(c);
                if (nums[i] >= base) {
                        delete[] nums;
                        throw std::invalid_argument("Неприемлимая цифра для СИ с основанием 12");
                }
        }
        normalize();
}

void Twelve::initNumber(unsigned int value){
        if (value == 0){
                size = 1;
                nums = new unsigned char[1];
                nums[0] = 0;
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
                nums[i] = temp % base;
                temp /= base;
        }
}

void Twelve::normalize(){
        while (size > 1 && nums[size - 1] == 0){
                size--;
        }
}   

Twelve::Twelve() : size(1){
        nums = new unsigned char[1];
        nums[0] = 0;
}

Twelve::Twelve(const size_t& n, unsigned char t) : size(n){
        if (t >= base){
                throw std::invalid_argument("Слишком большая цифра для СИ с основанием 12");
        }
        nums = new unsigned char[size];
        for (size_t i = 0; i < size; i++){
                nums[i] = t;
        }
        normalize();
}

Twelve::Twelve(const std::initializer_list<unsigned char>& t) : size(t.size()){
        nums = new unsigned char[size];
        size_t i = 0;
        for (std::initializer_list<unsigned char>::const_iterator it = t.begin(); it != t.end(); ++it, ++i){
                if (*it >= base){
                        delete[] nums;
                        throw std::invalid_argument("Неприемлимая цифра для СИ с основанием 12");
                }
                nums[i] = *it;
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

Twelve& Twelve::operator=(const Twelve& other){
        if (this == &other){
                return *this;
        }
        delete[] nums;
        size = other.size;
        nums = new unsigned char[size];
        for (size_t i = 0; i < size; i++){
                nums[i] = other.nums[i];
        }
        return *this;
}

Twelve& Twelve::operator=(Twelve&& other) noexcept{
        if (this != &other){
                delete[] nums;
                nums = other.nums;
                size = other.size;
                other.nums = nullptr;
                other.size = 0;
        }
        return *this;
}

Twelve Twelve::plus(const Twelve& other) const{
        size_t max_size = (size >  other.size ? size : other.size) + 1;
        Twelve result;
        delete[] result.nums;

        result.size = max_size;
        result.nums = new unsigned char[max_size]();
        
        unsigned int c = 0;
        for (size_t i = 0; i < max_size; i++){
                unsigned int a = (i < size) ? nums[i] : 0;
                unsigned int b = (i < other.size) ? other.nums[i] : 0;
                unsigned int sum = a + b + c;
                result.nums[i] = sum % base;
                c = sum / base;
        }
        result.normalize();
        return result;
}

Twelve Twelve::minus(const Twelve& other) const{
        if (this->less(other)){
                throw std::logic_error("Отрицательный результат при вычитании");
        }
        Twelve result(size, 0);
        int c = 0;
        for (size_t i = 0; i < size; i++){
                int a = nums[i];
                int b = (i < other.size) ? other.nums[i] : 0;
                int diff = a - b - c;
                if (diff < 0){
                        diff += base;
                        c = 1;
                } else{
                        c = 0;
                }
                result.nums[i] = diff;
        }
        result.normalize();
        return result;
}

Twelve Twelve::copy() const{
        return Twelve(*this);
}

Twelve& Twelve::plusAssign(const Twelve& other){
        *this = this->plus(other);
        return *this;
}

Twelve& Twelve::minusAssign(const Twelve& other){
        *this = this->minus(other);
        return *this;
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
        if (size != other.size){
                return size < other.size;
        }
        for (int i = (int)size - 1; i >= 0; i--){
                if (nums[i] != other.nums[i]){
                        return nums[i] < other.nums[i];
                }
        }
        return false;
}

bool Twelve::greater(const Twelve& other) const{
        return other.less(*this);
}

size_t Twelve::getSize() const{
        return size;
}

unsigned char Twelve::getDigit(size_t index) const{
        if (index >= size){
                throw std::out_of_range("Индекс за границами массива");
        }
        return nums[index];
}

void Twelve::print() const{
        for(int i = (int)size - 1; i >= 0; i--){
                if (nums[i] < 10) std::cout << int(nums[i]);
                else std::cout << char('A' + (nums[i] - 10));
        }
}

std::string Twelve::toString() const{
        std::string result;
        for (int i = (int)size - 1; i >= 0; i--){
                result += digitToChar(nums[i]);
        }
        return result;
}

bool Twelve::isValidDigit(unsigned char digit){
        return digit < base;
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

        

                        


