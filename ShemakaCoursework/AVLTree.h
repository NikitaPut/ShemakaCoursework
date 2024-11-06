#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <vector>
#include "HashTable.h"

class AVLTree {
public:
    struct Node {
        std::string key;
        std::vector<int> value;
        int height;
        Node* left;
        Node* right;

        Node(const std::string& k, const std::vector<int>& v) : key(k), value(v), height(1), left(nullptr), right(nullptr) {}
    };

    AVLTree() : root(nullptr) {}
    ~AVLTree() { deleteTree(root); }

    void insert(const std::string& key, const std::vector<int>& value);
    std::vector<int>* find(const std::string& key);
    void remove(const std::string& key);

    Node* balance(Node* node); // Убрано полное имя класса

private:
    Node* root;

    Node* insert(Node* node, const std::string& key, const std::vector<int>& value);
    Node* find(Node* node, const std::string& key) const;
    int getHeight(Node* node) const;
    int getBalance(Node* node) const;
    Node* rotateRight(Node* y);
    Node* rotateLeft(Node* x);
    void deleteTree(Node* node);
};

void AVLTree::insert(const std::string& key, const std::vector<int>& value) {
    root = insert(root, key, value);
}

std::vector<int>* AVLTree::find(const std::string& key) {
    Node* node = find(root, key);
    return node ? &node->value : nullptr;
}

inline void AVLTree::remove(const std::string& key) {}

AVLTree::Node* AVLTree::insert(Node* node, const std::string& key, const std::vector<int>& value) {
    if (!node) return new Node(key, value);
    // Insert recursively
    if (key < node->key) {
        node->left = insert(node->left, key, value);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key, value);
    }
    else {
        node->value = value;
        return node;
    }
    // Balance the tree
    return balance(node);
}

AVLTree::Node* AVLTree::find(Node* node, const std::string& key) const {
    if (!node) return nullptr;
    if (key == node->key) return node;
    return key < node->key ? find(node->left, key) : find(node->right, key);
}

int AVLTree::getHeight(Node* node) const {
    return node ? node->height : 0;
}

int AVLTree::getBalance(Node* node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

AVLTree::Node* AVLTree::rotateRight(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    x->height = std::max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = std::max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

void AVLTree::deleteTree(Node* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

#endif // AVL_TREE_H