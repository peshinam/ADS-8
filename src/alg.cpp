#include "../include/bst.h"
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error! Cannot open " << filename << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        // Проверяем, является ли символ латинской буквой
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            // Преобразуем в нижний регистр и добавляем к текущему слову
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else {
            // Если встретили не букву и слово не пустое, добавляем его в дерево
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    // Проверяем последнее слово, если файл заканчивается на букву
    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    if (tree.isEmpty()) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }

    // Получаем все узлы дерева
    std::vector<std::pair<std::string, int>> nodes = tree.getNodesSortedByValue();

    // Сортируем по убыванию частоты
    std::sort(nodes.begin(), nodes.end(), 
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    // Открываем файл для записи результатов
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cout << "Cannot create result/freq.txt" << std::endl;
        return;
    }

    // Выводим на экран и в файл
    std::cout << "\n=== Frequency Analysis Results ===" << std::endl;
    std::cout << "Total unique words: " << nodes.size() << std::endl;
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "\nWords sorted by frequency (descending):" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    outFile << "Word Frequency Report\n";
    outFile << "=====================\n";
    outFile << "Total unique words: " << nodes.size() << "\n";
    outFile << "Tree depth: " << tree.depth() << "\n\n";
    outFile << "Word\t\tFrequency\n";
    outFile << "----\t\t---------\n";

    int rank = 1;
    for (const auto& pair : nodes) {
        std::cout << rank++ << ". " << pair.first << " : " << pair.second << std::endl;
        outFile << pair.first << "\t\t" << pair.second << "\n";
    }

    outFile.close();
    std::cout << "\nResults saved to result/freq.txt" << std::endl;
}
