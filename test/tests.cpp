// Copyright 2021 NNTU-CS
#include "../include/bst.h"

#include <gtest/gtest.h>
#include <string>

TEST(BSTTest, InsertAndSearch) {
    BST<std::string> tree;
    tree.insert("hello");
    tree.insert("world");
    tree.insert("hello");
    auto result = tree.search("hello");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->count, 2);
    result = tree.search("world");
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->count, 1);
    result = tree.search("nonexistent");
    EXPECT_EQ(result, nullptr);
}

TEST(BSTTest, Depth) {
    BST<int> tree;
    EXPECT_EQ(tree.depth(), 0);
    tree.insert(5);
    EXPECT_EQ(tree.depth(), 1);
    tree.insert(3);
    tree.insert(7);
    EXPECT_EQ(tree.depth(), 2);
    tree.insert(1);
    tree.insert(9);
    EXPECT_EQ(tree.depth(), 3);
}

TEST(BSTTest, EmptyTree) {
    BST<double> tree;
    EXPECT_TRUE(tree.isEmpty());
    tree.insert(3.14);
    EXPECT_FALSE(tree.isEmpty());
}

TEST(BSTTest, GetNodesSorted) {
    BST<int> tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);
    auto nodes = tree.getNodesSortedByValue();
    EXPECT_EQ(nodes.size(), 5);
    EXPECT_EQ(nodes[0].first, 1);
    EXPECT_EQ(nodes[1].first, 2);
    EXPECT_EQ(nodes[2].first, 3);
    EXPECT_EQ(nodes[3].first, 5);
    EXPECT_EQ(nodes[4].first, 8);
}

TEST(BSTTest, DuplicateCounts) {
    BST<std::string> tree;
    tree.insert("apple");
    tree.insert("banana");
    tree.insert("apple");
    tree.insert("apple");
    tree.insert("banana");
    auto nodes = tree.getNodesSortedByValue();
    EXPECT_EQ(nodes.size(), 2);
    for (const auto& pair : nodes) {
        if (pair.first == "apple") {
            EXPECT_EQ(pair.second, 3);
        } else if (pair.first == "banana") {
            EXPECT_EQ(pair.second, 2);
        }
    }
}

TEST(BSTTest, CaseSensitivity) {
    BST<std::string> tree;
    tree.insert("Hello");
    tree.insert("hello");
    tree.insert("HELLO");
    auto nodes = tree.getNodesSortedByValue();
    EXPECT_EQ(nodes.size(), 3);
}

TEST(BSTTest, SearchReturnsCorrectNode) {
    BST<int> tree;
    for (int i = 0; i < 100; ++i) {
        tree.insert(i);
    }
    for (int i = 0; i < 100; ++i) {
        auto result = tree.search(i);
        ASSERT_NE(result, nullptr);
        EXPECT_EQ(result->key, i);
        EXPECT_EQ(result->count, 1);
    }
}
