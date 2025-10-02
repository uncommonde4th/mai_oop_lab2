#include "Twelve.h"

class Twelve{
        unsigned char* nums;
        size_t size;
        int base = 12;
public:
        Twelve() : size(1){
                nums = new unsigned char[1];
                nums[0] = 0;
        }

        Twelve(unsigned int value){
                if (value == 0){
                        size = 1;
                        nums = new unsigned char[1];
                        nums[0] = 0;
                }
                else{
                        size = 0;
                        unsigned int n = value;
                        while (n > 0){
                                n /= base;
                                size++;
                        }
                        nums = new unsigned char[size];
                        n = value;
                        for (size_t i = 0; i < size; i++){
                                nums[i] = n % base;
                                n /= base;
                        }
                }
        }

        Twelve(const Twelve& other){
                size = other.size;
                nums = new unsigned char[size];
                for (size_t i = 0; i < size; i++){
                        nums[i] = other.nums[i];
                }
        }
        
        ~Twelve(){
                delete[] nums;
        }

        Twelve& operator=(const Twelve& other){
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

        Twelve operator+(const Twelve& other) const{
                size_t max_size = (size > other.size ? size : other.size) + 1;
                Twelve result;
                delete[] result.nums;
                result.size = max_size;
                result.digits = new unsigned char[max_size];

                unsigned c = 0;
                for (size_t i = 0; i < max_size; i++){
                        unsigned a = (i < size) ? nums[i] : 0;
                        unsigned b = (i < other.size) ? other.nums[i] : 0;
                        unsigned sum = a + b + c;
                        result nums[i] = sum % base;
                        c = sum / base;
                }
                while (result.nums[result.size - 1] == 0 && result.size > 1){
                        result.size--;
                }
                
                return result;
        }

        Twelve operator-(const Twelve& other) const{
                if (*this < other){
                        throw std::logic_error("Отрицательный результат");
                }

                Twelve result;
                delete[] result.nums;
                result.size = size;
                result.nums = new unsigned char[result.size];

                int c = 0;
                for (size_t i = 0; i < size; i++){
                        int a = nums[i];
                        int b = (i < other.size) ? other.nums[i] : 0;
                        int diff = a - b - c;
                        if (if diff < 0){
                                diff += base;
                                c = 1;
                        }
                        else{
                                c = 0;
                        }
                        result.nums[i] = diff;
                }
                while (result.size > 1 && result.nums[result.size - 1] == 0){
                        result.size--;
                }
                return result;
        }

        bool operator==(const Twelve& other) const{
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
        
        bool operator<(const Twelve& other) const{
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

        bool operator>(const Twelve& other) const{
                return other < *this; 
        }

        void print() const{
                for(int i = (int)size - 1; i >= 0; i--){
                        if (nums[i] < 10) std::cout << int(nums[i]);
                        else std::cout << char('A' + (digits[i] - 10));
                }
        }
};
        

                        


