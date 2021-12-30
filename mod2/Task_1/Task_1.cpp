//
// Created by d3vyatk4 on 30.11.2021.
//

#include <iostream>
#include <vector>

#define DEFAULT_SIZE 8


// то что содержится в массиве хэш таблицы
template<typename T>
class HashNode {
public:
    T key;

    HashNode() : key("NIL") {}

    HashNode(const T &key_) : key(key_) {}
};

// функция хэширования
class StringHasher {
private:
    size_t prime;

public:
    StringHasher() : prime(31) {}

    StringHasher(const size_t &prime_) : prime(prime_) {}

    size_t operator()(const std::string &key_) {

        size_t hash = 0;
        for (int i = 0; i < key_.size(); ++i) {
            hash += hash * prime + key_[i];
        }

        return hash;
    }
};

template<typename T, typename Hasher>
class HashTable {
public:
    HashTable(size_t initial_capacity = DEFAULT_SIZE) : table(initial_capacity), real_size(0) {}

    ~HashTable() {}

    bool add(const T &key_) {

        if (static_cast<float>(real_size) / static_cast<float>(table.size()) >= 0.75) {
            reHash();
        }

        size_t h = hasher(key_) % table.size();
        long first_deleted = -1;
        for (size_t i = 0; i < table.size(); ++i) {

            if (table[h].key == "DEL" && first_deleted == -1) {
                first_deleted = h;
            } else if (table[h].key == "NIL") {

                if (first_deleted == -1) {
                    table[h].key = key_;
                } else {
                    table[first_deleted].key = key_;
                }

                real_size++;
                return true;

            } else {
                if (table[h].key == key_) {
                    return false;
                }
            }

            h = (h + i + 1) % table.size();
        }

        table[first_deleted].key = key_;
        real_size++;
        return true;
    }

    bool isHas(const T &key_) {

        size_t h = hasher(key_) % table.size();

        for (size_t i = 0; i < table.size(); ++i) {

            if (table[h].key == "NIL") {
                return false;
            } else if (table[h].key == key_) {
                return true;
            }

            h = (h + i + 1) % table.size();
        }

        return false;
    }

    bool delete_(const T &key_) {

        size_t h = hasher(key_) % table.size();

        for (int i = 0; i < table.size(); ++i) {

            if (table[h].key == "NIL") {
                return false;
            } else if (table[h].key == key_) {
                table[h].key = "DEL";
                real_size--;
                return true;
            }

            h = (h + i + 1) % table.size();
        }

        return false;
    }

    void reHash() {

        size_t newSize = table.size() * 2;
        std::vector<HashNode<T>> newTable(newSize);

        for (size_t i = 0; i < table.size(); ++i) {

            size_t h = hasher(table[i].key ) % newTable.size();

            if (table[i].key != "NIL" && table[i].key != "DEL") {
                for (size_t j = 0; j < newTable.size(); ++j) {
                    if (newTable[h].key == "NIL") {
                        newTable[h].key = table[i].key;
                        break;
                    }

                    h = (h + j + 1) % newTable.size();
                }
            }
        }

        table = newTable;
    }

private:
    std::vector<HashNode<T>> table;
    size_t real_size;
    Hasher hasher;
};


int main() {

    HashTable<std::string, StringHasher> hashtable;

    char op;
    std::string key;

    while (std::cin >> op >> key) {
        switch (op) {
            case '+': {
                std::cout << (hashtable.add(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '-': {
                std::cout << (hashtable.delete_(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
            case '?': {
                std::cout << (hashtable.isHas(key) ? "OK" : "FAIL") << std::endl;
                break;
            }
        }
    }
    return 0;
}
