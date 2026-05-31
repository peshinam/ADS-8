#include "../include/bst.h"
#include <iostream>
#include <string>
#include <chrono>

// Declaration of functions from alg.cpp
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    std::cout << "=== Binary Search Tree for Word Frequency Analysis ===" << std::endl;
    std::cout << "Analyzing 'War and Peace' by Leo Tolstoy" << std::endl;
    std::cout << "======================================================" << std::endl;

    BST<std::string> tree;

    // Измеряем время построения дерева
    auto start = std::chrono::high_resolution_clock::now();

    // Загружаем и анализируем файл
    makeTree(tree, "src/war_peace.txt");

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "\nTree built successfully!" << std::endl;
    std::cout << "Time taken: " << duration.count() << " ms" << std::endl;

    // Выводим частотный анализ
    printFreq(tree);

    // Демонстрация работы метода поиска
    std::cout << "\n=== Search Test ===" << std::endl;
    std::string testWords[] = {"the", "and", "to", "war", "peace", "nonexistent"};

    for (const auto& word : testWords) {
        auto result = tree.search(word);
        if (result != nullptr) {
            std::cout << "Word '" << word << "' found! Frequency: " << result->count << std::endl;
        } else {
            std::cout << "Word '" << word << "' not found!" << std::endl;
        }
    }

    std::cout << "\n=== Program completed successfully ===" << std::endl;

    return 0;
}
