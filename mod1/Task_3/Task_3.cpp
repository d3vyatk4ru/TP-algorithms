// 3_3. Реализовать очередь с помощью двух стеков. Использовать стек, реализованный с помощью динамического буфера.
// Требования: Очередь должна быть реализована в виде класса. Стек тоже должен быть реализован в виде класса.


#include <iostream>

#define DEFAULT_SIZE 1

class Stack {
public:

    // дефолтная инициализация стека
    Stack() : bufferSize(0), buffer(nullptr), realSize(0), top(0) {}
    ~Stack() {

        delete[] buffer;
    }

    // проверка на пустоту стека
    bool isEmpty() {
        return buffer == nullptr;
    }

    // добавление элемента на верхушку стека
    void push(int val) {
        if (realSize == bufferSize) {
            grow();
        }

        buffer[realSize++] = val;
        top = realSize - 1;
        return;
    }

    // извлечение элемента из верхушки стека
    int pop() {
        if (!isEmpty()) {

            if (!(realSize - 1)) {
                int tmp = buffer[--realSize];
                buffer = nullptr;
                bufferSize = 0;
                return tmp;
            }

            if (realSize < bufferSize / 2) {
                reduction();
            }

            top = --realSize;
            return buffer[top];
        } else {
            return -1;
        }
    }

    size_t size() const {
        return realSize;
    }

private:
    int *buffer;
    size_t bufferSize;
    size_t realSize;
    size_t top;

    void grow() {

        size_t newBufferSize = std::max(2 * bufferSize, size_t(DEFAULT_SIZE));

        int *newBuffer = new int[newBufferSize];
        std::copy(buffer, buffer + bufferSize, newBuffer);
        delete[] buffer;
        buffer = newBuffer;
        bufferSize = newBufferSize;
    }

    void reduction() {

        size_t newBufferSize = std::max(bufferSize / 2, size_t(DEFAULT_SIZE));

        int *newBuffer = new int[newBufferSize];
        std::copy(buffer, buffer + bufferSize, newBuffer);
        delete[] buffer;
        buffer = newBuffer;
        bufferSize = newBufferSize;

    }
};

class Queue {

public:
    // извлечение элемента из начала очереди
    int dequeue() {

        if (second.isEmpty()) {
            for (size_t i = 0; i < first.size() + i; ++i) {
                second.push(first.pop());
            }
        }

        return second.isEmpty() && first.isEmpty() ? -1 : second.pop();
    }

    // добавление элемента в конец очереди
    void enqueue(int val) {

        first.push(val);

        return;
    }

private:
    Stack first;
    Stack second;
};

int main() {

    Stack stack;

    Queue queue;

    // количество команд
    int n = 0;
    // номер команды {2, 3}
    int n_command = 0;
    // ожидаемое число (вводимое или извлекаемое)
    int number = 0;

    std::cin >> n;

    for (size_t i = 0; i < n; ++i) {

        std::cin >> n_command >> number;

        switch (n_command) {

            // извлекаем элемент из очереди
            case 2: {
                int curr = queue.dequeue();

                if (curr != number) {
                    std::cout << "NO" << std::endl;
                    return 0;
                }

                break;
            }

            // добавляем элемент в очередь
            case 3: {
                queue.enqueue(number);
                break;
            }
        }
    }

    std::cout << "YES" << std::endl;

    return 0;
}
