#include "../include/alg.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <string>

int main() {
  std::cout << "=== Binary Search Tree for Word Frequency Analysis ===" << std::endl;
  std::cout << "Analyzing 'War and Peace' by Leo Tolstoy" << std::endl;
  std::cout << "======================================================" << std::endl;
  BST<std::string> tree;
  std::ifstream testFile("src/war_peace.txt");
  if (!testFile) {
    std::cout << "\nERROR: File 'src/war_peace.txt' not found!" << std::endl;
    std::cout << "Please place the War and Peace text file at: src/war_peace.txt" << std::endl;
    return 1;
  }
  testFile.close();
  auto start = std::chrono::high_resolution_clock::now();
  makeTree(tree, "src/war_peace.txt");
  auto end = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
  std::cout << "\nTree built successfully!" << std::endl;
  std::cout << "Time taken: " << duration.count() << " ms" << std::endl;
  printFreq(tree);
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
