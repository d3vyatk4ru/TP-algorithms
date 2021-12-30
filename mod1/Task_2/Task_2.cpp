//
// Created by d3vyatk4 on 17.10.2021.
//

#include <cmath>
#include <iostream>

void input_data(int *arr, unsigned int size) {

    for (size_t i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }
}

unsigned int get_right_bound(int *const arr, unsigned int size, int val) {

    if (val < arr[0]) {
        return 0;
    }

    unsigned int right_bound = 1;
    while (val >= arr[right_bound] && right_bound < size) {
        right_bound *= 2;
    }

    return right_bound > size ? size : right_bound;
}

unsigned int binary_search(int *const arr, int val, unsigned int left, unsigned int right, unsigned size) {

    if (right == 0) {
        return 0;
    }

    if (val > arr[size - 1]) {
        return size;
    }

    while (left < right) {
        int middle = (left + right) / 2;
        if (arr[middle] < val) {
            left = middle + 1;
        } else {
            right = middle;
        }
    }
    return left;
}

int main() {

    // Размер первого массива
    unsigned int N;
    // Размер второго массива
    unsigned int M;
    std::cin >> N >> M;

    int *arrA = new int[N];
    input_data(arrA, N);

    int *arrB = new int[M];
    input_data(arrB, M);

    for (size_t i = 0; i < M; ++i) {
        unsigned int right_bound = get_right_bound(arrA, N, arrB[i]);
        unsigned int idx = binary_search(arrA, arrB[i], right_bound / 2, right_bound, N);
        std::cout << idx << " ";
    }

    delete[] arrA;
    delete[] arrB;

    return 0;
}