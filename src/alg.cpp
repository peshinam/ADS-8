// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return;
    }

    std::string currentWord = "";
    int ch;

    while ((ch = file.get()) != EOF) {
        if (std::isalpha(ch)) {
            currentWord += std::tolower(ch);
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord = "";
            }
        }
    }

    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }

    file.close();
}

bool compareNodes(const BST<std::string>::Node* a, const BST<std::string>::Node* b) {
    if (a->count != b->count) return a->count > b->count;
    return a->key < b->key;
}

void printFreq(BST<std::string>& tree) {
    std::vector<BST<std::string>::Node*> wordList = tree.getAllNodes();
    std::sort(wordList.begin(), wordList.end(), compareNodes);

    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Error: Cannot create result/freq.txt" << std::endl;
        return;
    }

    for (size_t i = 0; i < wordList.size(); ++i) {
        std::cout << wordList[i]->key << " : " << wordList[i]->count << std::endl;
        outFile << wordList[i]->key << " : " << wordList[i]->count << "\n";
    }

    outFile.close();
}
