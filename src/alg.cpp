// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);
int main() {
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";
    makeTree(tree, filename);
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::string searchWord = "war";
    int count = tree.search(searchWord);
    if (count > 0) {
        std::cout << "Word '" << searchWord << "' found " << count << " times." << std::endl;
    }
    printFreq(tree);
    return 0;
}
