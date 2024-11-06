#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <string>
#include <utility>
#include <exception>
#include <vector>

template <class TKey, class TVal>
class HashTable {
public:
    HashTable() : capacity_(256), size_(0), table_(new Bucket[capacity_]) {}

    ~HashTable() { delete[] table_; }

    void insertItem(const TKey& data, const TVal& value) {
        if ((static_cast<double>(size_) / capacity_) >= REHASH_FACTOR) {
            rehash();
        }
        size_t i = getIndex(data);
        Item newItem{ data, value };
        table_[i].list.push_back(newItem);
        table_[i].state = true;
        size_++;
    }

    bool search(const TKey& data) const {
        size_t i = getIndex(data);
        Item tempItem{ data, TVal{} };
        return table_[i].list.size() > 0 && table_[i].list.front().key == tempItem.key;
    }

    TVal retrieve(const TKey& key) const {
        size_t i = getIndex(key);
        for (const auto& item : table_[i].list) {
            if (item.key == key) {
                return item.value;
            }
        }
        return TVal{};
    }

    void print(std::ostream& out) const {
        for (size_t i = 0; i < capacity_; ++i) {
            if (table_[i].state) {
                out << "[" << i << "] ";
                for (const auto& item : table_[i].list) {
                    out << item.key << " -> ";
                    for (const auto& line : item.value) {
                        out << line << ' ';
                    }
                    out << "; ";
                }
                out << '\n';
            }
        }
    }

private:
    const double REHASH_FACTOR = 0.75;

    struct Item {
        TKey key;
        TVal value;

        bool operator==(const Item& other) const {
            return key == other.key;
        }
    };

    struct Bucket {
        std::vector<Item> list;
        bool state = false;
    };

    size_t size_;
    size_t capacity_;
    Bucket* table_;

    size_t getIndex(const TKey& data) const {
        return (std::hash<TKey>()(data) % capacity_);
    }

    void rehash() {
        size_t newCapacity = capacity_ * 2;
        Bucket* newTable = new Bucket[newCapacity];

        for (size_t i = 0; i < capacity_; ++i) {
            for (auto& item : table_[i].list) {
                size_t j = std::hash<TKey>()(item.key) % newCapacity;
                newTable[j].list.push_back(item);
                newTable[j].state = true;
            }
        }
        delete[] table_;
        table_ = newTable;
        capacity_ = newCapacity;
    }
};

#endif