#pragma once

#include <algorithm>
#include <array>
#include <charconv>
#include <fstream>
#include <iostream>
#include <list>
#include <ranges>
#include <regex>
#include <string>
#include <unordered_map>
#include <vector>

#include "node.h"
#include "timer.h"

std::string get_input_one_line(std::string filepath);
std::vector<std::string> get_input_all_lines(std::string filepath);
std::vector<std::vector<std::string>> get_input_blocks(std::string filepath);
void print_vec_int(std::vector<int>);
void print_vec_hex(std::vector<int>);
int sv_to_int(std::string_view);

template <typename T>
void print_vec(std::vector<T> v, bool spaces) {
    for (const auto& val : v) {
        std::cout << std::format("{}", val);
        if (spaces) {
            std::cout << " ";
        }
    }
    std::cout << "\n";
}