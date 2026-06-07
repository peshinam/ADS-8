// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
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
        if (node == nullptr) return -1;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }
    Node* searchNode(Node* node, const T& value) const {
        if (node == nullptr || node->key == value) return node;
        if (value < node->key) return searchNode(node->left, value);
        return searchNode(node->right, value);
    }
    Node* insertNode(Node* node, const T& value) {
        if (node == nullptr) return new Node(value);
        if (value == node->key) node->count++;
        else if (value < node->key) node->left = insertNode(node->left, value);
        else node->right = insertNode(node->right, value);
        return node;
    }
    void collectNodes(Node* node, std::vector<Node*>& nodes) const {
        if (node == nullptr) return;
        collectNodes(node->left, nodes);
        nodes.push_back(node);
        collectNodes(node->right, nodes);
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }
    void insert(const T& value) { root = insertNode(root, value); }
    int depth() const { return getDepth(root); }
    int search(T value) const {
        Node* res = searchNode(root, value);
        return res != nullptr ? res->count : 0;
    }
    std::vector<Node*> getAllNodes() const {
        std::vector<Node*> nodes;
        collectNodes(root, nodes);
        return nodes;
    }
};
#endif  // INCLUDE_BST_H_
