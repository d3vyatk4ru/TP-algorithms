// Дано число N < 106 и последовательность целых чисел из [-2^31..2^31] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Требования: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.
//
// 2_3. Выведите элементы в порядке post-order (снизу вверх).
//
// Created by d3vyatk4 on 04.12.2021.
//

#include <iostream>
#include <stack>

template<typename T>
struct Node {

    T key;
    Node *left;
    Node *right;

    Node(const T &key_) : key(key_), left(nullptr), right(nullptr) {}
};

bool Comparator(const Node<int> &first, const Node<int> &second) {
    return first.key >= second.key;
}

bool ComparatorNotEqual(const Node<int> &first, const Node<int> &second) {
    return first.key > second.key;
}

template<typename T>
class BinaryTree {

public:

    BinaryTree() : tree(nullptr) {}

    BinaryTree(const T &key_) {
        tree = new Node<T>(key_);
    }

    ~BinaryTree() {

    }

    bool add(const T &key_, bool (*cmp)(const Node<T>&, const Node<T>&)= Comparator) {

        Node<T> **tmp = &tree;

        while (*tmp) {

            Node<T>& node = **tmp;

            if (cmp(Node<T>(key_), node)) {
                tmp = &node.right;
            } else {
                tmp = &node.left;
            }
        }

        *tmp = new Node<T>(key_);

        return true;
    }

    bool isHas(const T &key_, bool (*cmp)(const Node<T>&, const Node<T>&) = ComparatorNotEqual) {

        Node<T> **tmp = &tree;
        Node<T>& node = **tmp;

        while (*tmp) {

            Node<T>& node = **tmp;

            if (!cmp(Node<T>(key_), node)) {
                tmp = &node.right;

            } else if (cmp(Node<T>(key_), node)){
                tmp = &node.left;

            } else {
                return true;
            }
        }

        return false;
    }

    void post_order_display() {

        std::stack<Node<T>*> Stack;                 // Создаем стек
        Node<int> *other = 0;
        Node<int> *peek = 0;

        Node<T> *tmp = tree;

        while (Stack.size() || tmp) {

            // пока не упремся в нуль идем в левое поддерево и добавляем узлы в стек
            if (tmp) {
                Stack.push(tmp);
                tmp = tmp->left;
            } else {

                // когда уперлись в нуль, берем последний узел и смотрим
                peek = Stack.top();

                // если там есть правая вершина, то смотрим его
                if (peek->right && other != peek->right) {
                    tmp = peek->right;

                 // иначе извлекаем из стека последнюю вершину
                } else {
                    Stack.pop();
                    std::cout << peek->key << " ";
                    other = peek;
                }
            }
        }
    }

    void deleteAll() {
        std::stack<Node<T>*> Stack;                 // Создаем стек
        Node<int> *other = 0;
        Node<int> *peek = 0;

        while (Stack.size() || tree) {

            // пока не упремся в нуль идем в левое поддерево и добавляем узлы в стек
            if (tree) {
                Stack.push(tree);
                tree = tree->left;
            } else {

                // когда уперлись в нуль, берем последний узел и смотрим
                peek = Stack.top();

                // если там есть правая вершина, то смотрим его
                if (peek->right && other != peek->right) {
                    tree = peek->right;
                    // иначе извлекаем из стека последнюю вершину
                } else {
                    Stack.pop();
                    delete peek;
                    other = peek;
                }
            }
        }
    }

private:

    Node<T> *tree;
};

int main(int argc, char *argv[]) {

    BinaryTree<int> tree;

    size_t N;

    std::cin >> N;
    int num;

    for (size_t i = 0; i < N; ++i) {
        std::cin >> num;
        tree.add(num);
    }

    tree.post_order_display();

    tree.deleteAll();

    return 0;
}
