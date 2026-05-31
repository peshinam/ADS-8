#ifndef BST_H
#define BST_H

#include <iostream>
#include <algorithm>

template <typename T>
class BST {
private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& value) {
        if (node == nullptr) {
            node = new Node(value);
            return;
        }

        if (value < node->data) {
            insert(node->left, value);
        } else if (value > node->data) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    Node* search(Node* node, const T& value) const {
        if (node == nullptr || node->data == value) {
            return node;
        }

        if (value < node->data) {
            return search(node->left, value);
        } else {
            return search(node->right, value);
        }
    }

    void inorderCollect(Node* node, std::vector<std::pair<T, int>>& nodes) const {
        if (node == nullptr) return;
        inorderCollect(node->left, nodes);
        nodes.push_back({node->data, node->count});
        inorderCollect(node->right, nodes);
    }

    void clear(Node* node) {
        if (node == nullptr) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(const T& value) {
        insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    Node* search(const T& value) const {
        return search(root, value);
    }

    std::vector<std::pair<T, int>> getNodesSortedByValue() const {
        std::vector<std::pair<T, int>> nodes;
        inorderCollect(root, nodes);
        return nodes;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};

#endif
