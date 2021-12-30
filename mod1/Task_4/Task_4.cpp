// Требование для всех вариантов Задачи 4
// Решение всех задач данного раздела предполагает использование кучи, реализованной в виде шаблонного класса.
// Решение должно поддерживать передачу функции сравнения снаружи.
// Куча должна быть динамической.
// Напишите программу, которая использует кучу для слияния K отсортированных массивов суммарной длиной N.
// Требования: время работы O(N * logK). Ограничение на размер кучи O(K).
// Created by d3vyatk4 on 04.11.2021.
//

#include <iostream>

// обертка над массивом
struct arrayWrapper {

    int *arr;
    size_t size;

    arrayWrapper() : arr(nullptr), size(0) {};
};

// куча
template <typename T>
class Heap {

public:
    Heap() {
        bufferSize = 1;
        buffer = new T[bufferSize];
        heapSize = 0;
    }

    ~Heap() {
        delete[] buffer;
    }

    void insert(int *elem, size_t K, size_t i, bool (*cmp)(const T&, const T&)) {
        ++heapSize;
        while (bufferSize < heapSize) {
            bufferExpansion();
        }

        buffer[i].arr = new int[K];
        std::copy(elem, elem + K, buffer[i].arr);
        buffer[i].size = K;
        siftUp(i, cmp);
    }

    void meargeHeap(size_t resultSize, bool (*cmp)(const T&, const T&)) {

        size_t i = 0;

        while (i < resultSize) {
            std::cout << ExtractTop() << " ";
            siftDown(0, cmp);
            ++i;
        }
    }

private:

    size_t bufferSize;
    const short MULTIPLIER = 2;
    T *buffer;
    size_t heapSize;

    // увеличение буффера
    void bufferExpansion() {

        size_t newBufferSize = bufferSize * MULTIPLIER;
        auto *newBuffer = new T[newBufferSize];
        std::copy(buffer, buffer + bufferSize, newBuffer);
        delete[] buffer;
        buffer = newBuffer;
        bufferSize = newBufferSize;
    }

    void siftUp(size_t i, bool (*cmp)(const T&, const T&)) {

        while (i > 0) {
            size_t parent = (i - 1) / 2;

            if (cmp(buffer[i],  buffer[parent])) {
                return;
            }

            std::swap(buffer[i], buffer[parent]);
            i = parent;
        }
    }

    // просеивание вниз
    void siftDown(size_t i, bool (*cmp)(const T&, const T&)) {

        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        size_t smallest = i;

        if (left < heapSize && !cmp(buffer[left], buffer[i])) {
            smallest = left;
        }

        if (right < heapSize && !cmp(buffer[right],  buffer[smallest])) {
            smallest = right;
        }

        if (smallest != i) {
            std::swap(buffer[i], buffer[smallest]);
            siftDown(smallest, cmp);
        }
    }
    int ExtractTop() {

        int result = buffer[0].arr[0];
        --buffer[0].size;

        if (buffer[0].size != 0) {
            ++buffer[0].arr;
        } else {
            std::swap(buffer[0], buffer[heapSize - 1]);
            --heapSize;
        }

        return result;
    }

};

bool Comparator(const arrayWrapper& l, const arrayWrapper& r) {
    return l.arr[0] > r.arr[0];
}

int main() {

    size_t N = 0;
    std::cin >> N;

    size_t resultSize = 0;
    Heap<arrayWrapper> heap;
    size_t K = 0;

    for (size_t i = 0; i < N; ++i) {
        std::cin >> K;
        resultSize += K;
        auto *temp = new int[K];
        for (size_t j = 0; j < K; ++j) {
            std::cin >> temp[j];
        }
        heap.insert(temp, K, i, Comparator);
        delete[] temp;
    }
    heap.meargeHeap(resultSize, Comparator);

    return 0;
}
