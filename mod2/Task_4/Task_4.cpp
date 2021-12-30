
#include <iostream>
#include <vector>
#include <stack>

template<typename T>
struct Node {

    Node(const size_t &key) : key(key), height(1), left(0), right(0), count(1) {}

    T key;
    size_t height;
    size_t count;
    Node<T> *left;
    Node<T> *right;
};

bool Comparator(const Node<size_t> &first, const Node<size_t> &second) {
    return first.key < second.key;
}

template<typename T>
class AVLTree {

public:

    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        destroyTree(root);
    }

    void Add(const size_t &key, size_t &pos, bool (*cmp)(const Node<T>&, const Node<T>&)= Comparator) {
        root = addInternal(root, key, pos);
    }

    void Remove(size_t &pos) {
        root = removeInternal(root, pos);
    }

private:
    Node<T> *root;

    void destroyTree(Node<T> *node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }


    Node<T>* addInternal(Node<T>* node, const size_t &data, size_t &position)
    {
        if(node == nullptr) {
            return new Node<T>(data);
        }
        ++(node->count);
        if(data < node->key ) {
            position += ((node->right == nullptr) ? 0 : node->right->count) + 1;
            node->left = addInternal(node->left, data, position);
        }
        else{
            node->right = addInternal(node->right, data, position);
        }
        return doBalance(node);
    }

    Node<T> *removeInternal(Node<T> *node, size_t pos, bool (*cmp) (const Node<T>&, const Node<T>&) = Comparator) {

        if (!node) {
            return 0;
        }

        if (pos >= node->count) {
            return node;
        }

        std::stack<Node<T> *> Stack;
        size_t sum = 0;

        while (true) {

            size_t n_right = 0;
            if (node->right) {
                n_right = node->right->count;
            }

            if (n_right < pos - sum) {
                Stack.push(node);
                node = node->left;
                sum += n_right + 1;

            } else if (n_right > pos - sum) {

                if (!node->right) {
                    Stack.push(node);
                    node = node->right;
                } else {
                    break;
                }

            } else {

                Node<T> *node_right = node->right;
                Node<T> *node_left = node->left;
                size_t node_key = node->key;

                delete node;
                if (!node_right) {
                    if (!node_left) {
                        if (!Stack.empty()) {

                            node = Stack.top();
                            Stack.pop();

                            if (node_key < node->key) {
                                node->left = nullptr;
                            }
                            else {
                                node->right = nullptr;
                            }

                            node->count = node->count - 1;
                        } else
                            return nullptr;
                    } else
                        node = node_left;
                } else {

                    Node<T> *newRoot = nullptr;
                    if (getHeight(node_right) > getHeight(node_left)) {
                        Node<T> *newRight = nullptr;
                        newRight = findAndRemoveMin(node_right, newRoot);
                        newRoot->right = newRight;
                        newRoot->left = node_left;
                    } else {
                        Node<T> *newLeft = nullptr;
                        newLeft = findAndRemoveMax(node_left, newRoot);
                        newRoot->left = newLeft;
                        newRoot->right = node_right;
                    }

                    fixCount(newRoot);
                    node = doBalance(newRoot);
                }
                break;
            }
        }

        Node<T> *new_node;
        while (!Stack.empty()) {

            new_node = Stack.top();
            new_node->count = new_node->count - 1;

            if ( new_node->key > node->key) {
                new_node->left = node;
            }
            else {
                new_node->right = node;
            }

            node = doBalance(new_node);
            Stack.pop();
        }

        return node;
    }

    // ищем и вставляем минимум
    Node<T> *findAndRemoveMin(Node<T> *node, Node<T> *&min) {

        if (!node->left) {
            min = node;
            return node->right;
        }

        node->left = findAndRemoveMin(node->left, min);
        node->count = node->count - 1;

        return doBalance(node);
    }

    Node<T> *findAndRemoveMax(Node<T> *node, Node<T> *&max) {

        if (!node->right) {
            max = node;
            return node->left;
        }

        node->right = findAndRemoveMax(node->right, max);
        node->count = node->count - 1;
        return doBalance(node);
    }

    size_t getHeight(Node<T> *node) {
        return node ? node->height : 0;
    }

    void fixHeight(Node<T> *node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }

    void fixCount(Node<T> *node) {

        // у вершины есть оба потомка
        if (node->right && node->left) {
            node->count = node->right->count + node->left->count + 1;
        }

        // нет правого потомка
        if (node->right == nullptr && node->left) {
            node->count = node->left->count + 1;
        }

        // нет левого потомка
        if (node->right && node->left == nullptr) {
            node->count = node->right->count + 1;
        }
    }

    int getBalance(Node<T> *node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node<T> *doBalance(Node<T> *node)
    {
        fixHeight(node);

        switch (getBalance(node))
        {
            case 2:
            {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2:
            {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }

    Node<T> *rotateLeft(Node<T> *node) {
        Node<T> *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixCount(node);
        fixCount(tmp);
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    Node<T> *rotateRight(Node<T> *node) {
        Node<T> *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixCount(node);
        fixCount(tmp);
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

};

int main() {

    AVLTree<size_t> avlTree;

    int N;
    std::cin >> N;

    size_t key;
    size_t pos;
    char op;

    for (size_t i = 0; i < N; ++i) {

        std::cin >> op >> key;

        switch (op) {

            case '1':
                pos = 0;
                avlTree.Add(key, pos, Comparator);
                std::cout << pos << "\n";
                break;

            case '2':
                // здесь это не ключ, а позиция удаления
                avlTree.Remove(key);
                break;
        }
    }
    return 0;
}
