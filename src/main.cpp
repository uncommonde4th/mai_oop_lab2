#include "../include/Twelve.h"

void displayMenu() {
        std::cout << "\n=== Twelve Calculator ===" << std::endl;
        std::cout << "1. Создать число из строки" << std::endl;
        std::cout << "2. Создать число из десятичного числа" << std::endl;
        std::cout << "3. Найти сумму чисел" << std::endl;
        std::cout << "4. Найти разность чисел" << std::endl;
        std::cout << "5. Сравнить два числа" << std::endl;
        std::cout << "0. Выход" << std::endl;
        std::cout << "Выберите действие: ";
}


Twelve inputNumberFromString() {
        std::string input;
        std::cout << "Введите число в СИ с основанием 12 (цифры 0-9, A, B): ";
        std::cin >> input;
        return Twelve(input);
}

Twelve inputNumberFromDecimal() {
        unsigned int value;
        std::cout << "Введите десятичное число: ";
        std::cin >> value;
        return Twelve(value);
}

void demoPlus() {
        Twelve a = inputNumberFromString();
        Twelve b = inputNumberFromString();
        Twelve result = a.plus(b);
    
        std::cout << "Результат: ";
        a.print();
        std::cout << " + ";
        b.print();
        std::cout << " = ";
        result.print();
        std::cout << std::endl;
}

void demoMinus() {
    Twelve a = inputNumberFromString();
    Twelve b = inputNumberFromString();
    
    try {
        Twelve result = a.minus(b);
        
        std::cout << "Результат: ";
        a.print();
        std::cout << " - ";
        b.print();
        std::cout << " = ";
        result.print();
        std::cout << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void demoComparison() {
        Twelve a = inputNumberFromString();
        Twelve b = inputNumberFromString();
    
        std::cout << "a = ";
        a.print();
        std::cout << ", b = ";
        b.print();
        std::cout << std::endl;
    
        if (a.equal(b)) {
                std::cout << "a равно b" << std::endl;
        } else {
                std::cout << "a не равно b" << std::endl;
        }
    
        if (a.less(b)) {
                std::cout << "a меньше чем b" << std::endl;
        }
    
        if (a.greater(b)) {
                std::cout << "a больше чем b" << std::endl;
        }
}

int main() {
        int choice;
        do {
                displayMenu();
                std::cin >> choice;
                try {
                        switch (choice) {
                                case 1: {

                                                Twelve num = inputNumberFromString();
                                                std::cout << "Число создано: ";
                                                num.print();
                                                std::cout << std::endl;
                                                break;
                                        }
                                case 2: {
                                                Twelve num = inputNumberFromDecimal();
                                                std::cout << "Число создано: ";
                                                num.print();
                                                std::cout << std::endl;
                                                break;
                                        }
                
                                case 3:
                                                demoPlus();
                                                break;
                                case 4:
                                                demoMinus();
                                                break;
                                case 5:
                                                demoComparison();
                                                break;
                                case 0:
                                                break;
                                default:
                                                std::cout << "Такого действия нет" << std::endl;
                        }
                } catch (const std::exception& e) {
                        std::cout << "Error: " << e.what() << std::endl;
                }
        
        } while (choice != 0);
        return 0;
}
