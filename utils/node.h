#pragma once

#include <iostream>
#include <string>
#include <vector>

struct Node {
    std::string id;
    Node* left;
    Node* center;
    Node* right;
};

struct TernaryTree {
    Node* root;
};