#include <iostream>
#include "client.h"

int main() {
    Client c1(1, "Ali", 5);
    Client c2(2, "Fatou", 12);
    Client c3(3, "Moussa", 8);

    std::cout << c1.toString() << std::endl;
    std::cout << c2.toString() << std::endl;
    std::cout << c3.toString() << std::endl;

    return 0;
}