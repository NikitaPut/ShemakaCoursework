#ifndef CROSS_REFS_H
#define CROSS_REFS_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "HashTable.h"
#include "AVLTree.h"

class CrossRefs {
public:
    CrossRefs() : table_() {}
    ~CrossRefs() = default;

    CrossRefs(const CrossRefs& other) : table_(other.table_) {}
    CrossRefs(CrossRefs&& moved) noexcept : table_(std::move(moved.table_)) {}

    void insert(const std::string& word, const size_t& lineNumber) {
        if (!table_.search(word)) {
            std::vector<size_t> list;
            list.push_back(lineNumber);
            table_.insertItem(word, list);
        }
        else {
            std::vector<size_t> list = table_.retrieve(word);
            list.push_back(lineNumber);
            table_.insertItem(word, list);
        }
    }

    void createTable(const std::string& name) {
        std::ifstream in(name);
        if (!in.is_open())
            throw std::runtime_error("Could not open file: " + name);
        std::string line;
        size_t lineNumber = 1;
        while (std::getline(in, line)) {
            std::istringstream stream(line);
            std::string word;
            while (stream >> word) {
                word = reformat(word);
                insert(word, lineNumber);
            }
            lineNumber++;
        }
    }

    void print(std::ostream& out) {
        table_.print(out);
    }

    std::string reformat(const std::string& word) {
        std::string result;
        for (char ch : word) {
            if (isalpha(ch)) {
                result += std::tolower(ch);
            }
        }
        return result;
    }

    void readFile(std::ostream& out, const std::string& name) {
        std::ifstream in(name);
        if (!in.is_open())
            throw std::runtime_error("Could not open file: " + name);

        size_t num = 0;
        std::string line;
        while (std::getline(in, line)) {
            num++;
            out << num << '\t' << line << '\n';
        }
    }

private:
    HashTable<std::string, std::vector<size_t>> table_;
    AVLTree tree;
};

#endif