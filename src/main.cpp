#include "Twelve.h"

int main(){
        Twelve a(23);
        Twelve b(20);

        Twelve c = a + b;
        std::cout << c.print(); << std::endl;

        return 0;
}
