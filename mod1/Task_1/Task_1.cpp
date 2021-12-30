//
// Created by d3vyatk4 on 14.10.2021.
//

#include <iostream>

#define BIT 1

unsigned int count_bit(unsigned int number) {

    unsigned int res = 0;
    size_t i = 0;

    while (number) {
        if (!(i & 1) && (number >> 0) & BIT) {
            res++;
        }
        i++;
        number >>= BIT;
    }

    return res;
}

int main() {

    unsigned int number;
    std::cin >> number;
    std::cout << count_bit(number);

    return 0;
}