// 6_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”.
// Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
//

#include <iostream>
#include <cmath>

template <typename T>
bool Comparator(const T &l, const T &r) {
    return l > r;
}

template <typename T>
std::size_t partition(T *arr, std::size_t left, std::size_t right, bool (*cmp)(const T&, const T&)) {

    std::size_t rnd_idx = std::rand() % (right - left + 1) + left ;

    T pivot = arr[rnd_idx];
    std::swap(arr[rnd_idx], arr[right]);

    std::size_t i = 0;
    std::size_t j = 0;

    while (j < right) {

        if (cmp(arr[j], pivot)) {
            j++;
        } else {
            std::swap(arr[i], arr[j]);
            i++;
            j++;
        }
    }

    std::swap(arr[right], arr[i]);

    return i;
}

template <typename T>
T kth_stat(T *arr, std::size_t k, std::size_t left, std::size_t right, bool (*cmp)(const T&, const T&)) {

    if (right != -1) {

        if (right == 0) {
            return arr[0];
        }

        std::size_t pivot_idx = partition(arr, left, right, cmp);

        while (k != pivot_idx) {

            if (k < pivot_idx) {
                right = pivot_idx - 1;
            }

            if (pivot_idx < k) {
                left = pivot_idx + 1;
            }

            pivot_idx = partition(arr, left, right, cmp);
        }

        return arr[pivot_idx];
    }
}

int main() {

//    std::size_t bufferSize = 0;
//    std::cin >> bufferSize;
//    auto buffer = new int[bufferSize];
//
//    for (int i = 0; i < bufferSize; ++i) {
//        std::cin >> buffer[i];
//    }
//
//    std::cout << kth_stat(buffer, floor(0.1 * bufferSize), 0, bufferSize - 1, Comparator) << "\n";
//    std::cout << kth_stat(buffer, floor(0.5 * bufferSize), 0, bufferSize - 1, Comparator) << "\n";
//    std::cout << kth_stat(buffer, floor( 0.9 * bufferSize), 0, bufferSize - 1, Comparator) << "\n";
//
//    delete[] buffer;


    return 0;
}