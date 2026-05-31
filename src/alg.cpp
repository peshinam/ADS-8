// Copyright 2024 <Copyright Owner>
#include "../include/alg.h"

#include <cctype>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

void ensureResultDirectory() {
#ifdef _WIN32
  static_cast<void>(system("mkdir result 2>nul"));
#else
  static_cast<void>(system("mkdir -p result"));
#endif
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error! Cannot open " << filename << std::endl;
    return;
  }
  std::string word;
  char ch;
  while (file.get(ch)) {
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
      if (ch >= 'A' && ch <= 'Z') {
        ch = ch - 'A' + 'a';
      }
      word += ch;
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
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
  std::vector<std::pair<std::string, int>> nodes = tree.getNodesSortedByValue();
  std::sort(nodes.begin(), nodes.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      return a.second > b.second;
    });
  ensureResultDirectory();
  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Cannot create result/freq.txt" << std::endl;
    return;
  }
  std::cout << "\n=== Frequency Analysis Results ===" << std::endl;
  std::cout << "Total unique words: " << nodes.size() << std::endl;
  std::cout << "Tree depth: " << tree.depth() << std::endl;
  std::cout << "\nTop 50 words by frequency:" << std::endl;
  std::cout << "----------------------------------------" << std::endl;
  outFile << "Word Frequency Report\n";
  outFile << "=====================\n";
  outFile << "Total unique words: " << nodes.size() << "\n";
  outFile << "Tree depth: " << tree.depth() << "\n\n";
  outFile << "Rank\tWord\t\tFrequency\n";
  outFile << "----\t----\t\t---------\n";
  int rank = 1;
  int topCount = std::min(50, static_cast<int>(nodes.size()));
  for (int i = 0; i < topCount; ++i) {
    const auto& pair = nodes[i];
    std::cout << rank << ". " << pair.first << " : " << pair.second << std::endl;
    outFile << rank << "\t" << pair.first << "\t\t" << pair.second << "\n";
    ++rank;
  }
  if (nodes.size() > 50) {
    std::cout << "... and " << (nodes.size() - 50) << " more words" << std::endl;
    outFile << "... and " << (nodes.size() - 50) << " more words\n";
  }
  outFile.close();
  std::cout << "\nResults saved to result/freq.txt" << std::endl;
}
