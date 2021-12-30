//
// Created by d3vyatk4 on 05.11.2021.
//

#include <iostream>
#include <cstring>

struct Point {
    int point;
    int value;
};

template <typename T>
bool defaultComparator(const T &l, const T &r) {
    return l > r;
}

bool ComparatorLine(const Point &l, const Point &r) {
    return l.point > r.point;
}

template <typename T>
void merge(T *leftArr, std::size_t l_size, T *rightArr, std::size_t r_size, T *ret, bool (*cmp)(const T&, const T&)=defaultComparator) {

    std::size_t iter = 0;

    // Проходим по 2-м массивам и сравниваем элементы, добавляем в новый массив наименьший
    while (l_size && r_size) {
        if (cmp(*leftArr, *rightArr)) {
            ret[iter] = *rightArr;
            rightArr++;
            --r_size;
        } else {
            ret[iter] = *leftArr;
            leftArr++;
            --l_size;
        }
        iter++;
    }

    // если один из массивов закончился, второя просто переписываем в исходный
    if (!l_size) {
        for (std::size_t i = 0; i < r_size; ++i) {
            ret[iter++] = *rightArr++;
        }
    } else {
        for (std::size_t i = 0; i < l_size; ++i) {
            ret[iter++] = *leftArr++;
        }
    }
}

template <typename T>
void mergeSort(T *arr, std::size_t size, bool (*cmp)(const T&, const T&)=defaultComparator) {

    if (size < 2) {
        return;
    }

    T* sortedArr = new T[size];

    std::size_t leftSize = size / 2;
    std::size_t rightSize = size - leftSize;

    mergeSort(arr, leftSize, cmp);
    mergeSort(arr + leftSize, rightSize, cmp);
    merge(arr, leftSize, arr + leftSize, rightSize, sortedArr, cmp);
    std::memcpy(arr, sortedArr, sizeof(T) * size);

    delete[] sortedArr;

}

int calculate_dist(Point *point, std::size_t size) {
    int cum = 0;
    int res = 0;
    for (std::size_t i = 0; i < size - 1; ++i) {
        cum += point[i].value;
        if (cum == 1) {
            res += point[i + 1].point - point[i].point;
        }
    }

    return res;
}

int main() {

    int n = 0;
    std::cin >> n;
    
    auto A = new Point[2*n];

    for (std::size_t i = 0; i < 2*n; ++i) {
        if (!(i % 2)) {
            std::cin >> A[i].point;
            A[i].value = 1;
        } else {
            std::cin >> A[i].point;
            A[i].value = -1;
        }
    }
    
    mergeSort(A, 2*n, ComparatorLine);

    std::cout << calculate_dist(A, 2*n);

    delete[] A;

    return 0;
}