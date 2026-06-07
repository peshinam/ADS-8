// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>

template <typename T>
class BST {
 public:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(T value) : key(value), count(1), left(nullptr), right(nullptr) {}
    };

 private:
    Node* root;

    void clear(Node* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    int getDepth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(getDepth(node->left), getDepth(node->right));
    }

    Node* searchNode(Node* node, const T& value) const {
        if (node == nullptr || node->key == value) return node;
        if (value < node->key) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }

    Node* insertNode(Node* node, const T& value) {
        if (node == nullptr) return new Node(value);
        if (value == node->key) {
            node->count++;
        } else if (value < node->key) {
            node->left = insertNode(node->left, value);
        } else {
            node->right = insertNode(node->right, value);
        }
        return node;
    }

    void collectNodes(Node* node, std::vector<Node*>& nodes) const {
        if (node == nullptr) return;
        collectNodes(node->left, nodes);
        nodes.push_back(node);
        collectNodes(node->right, nodes);
    }

    void getNodesSortedByValue(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node == nullptr) return;
        getNodesSortedByValue(node->left, result);
        result.push_back({node->key, node->count});
        getNodesSortedByValue(node->right, result);
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        root = insertNode(root, value);
    }

    int depth() const {
        return getDepth(root);
    }

    // Возвращает указатель на узел (для тестов)
    Node* search(const T& value) const {
        return searchNode(root, value);
    }

    // Возвращает количество вхождений (для alg.cpp)
    int getCount(const T& value) const {
        Node* node = searchNode(root, value);
        return node != nullptr ? node->count : 0;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    std::vector<std::pair<T, int>> getNodesSortedByValue() const {
        std::vector<std::pair<T, int>> result;
        getNodesSortedByValue(root, result);
        return result;
    }

    std::vector<Node*> getAllNodes() const {
        std::vector<Node*> nodes;
        collectNodes(root, nodes);
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
