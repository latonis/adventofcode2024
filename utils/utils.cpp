#include "utils.h"

void print_vec_int(std::vector<int> v) {
    for (auto val : v) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void print_vec(std::vector<std::string> v) {
    for (const auto& val : v) {
        std::cout << val << " ";
    }
    std::cout << "\n";
}

void print_vec_hex(std::vector<int> v) {
    for (auto i : v) {
        std::cout << std::hex << i;
    }
    std::cout << "\n";
}

std::string get_input_one_line(std::string filepath) {
    std::ifstream inputFile(filepath);
    std::string line;
    if (inputFile.is_open()) {
        std::getline(inputFile, line);
    }
    return line;
}

std::vector<std::vector<std::string>> get_input_blocks(std::string filepath) {
    std::ifstream inputFile(filepath);
    std::vector<std::string> v1;
    std::vector<std::string> v2;

    bool break_encountered = false;

    if (inputFile.is_open()) {
        for (std::string line; std::getline(inputFile, line);) {
            if (line == "") {
                break_encountered = true;
                continue;
            }

            if (not break_encountered) {
                v1.push_back(line);
            } else {
                v2.push_back(line);
            }
        }
    }

    return {v1, v2};
}

std::vector<std::string> get_input_all_lines(std::string filepath) {
    std::ifstream inputFile(filepath);
    std::vector<std::string> v;
    if (inputFile.is_open()) {
        for (std::string line; std::getline(inputFile, line);) {
            v.push_back(line);
        }
    }
    return v;
}

int sv_to_int(std::string_view r) {
    int i = 0;
    std::from_chars(r.data(), r.data() + r.size(), i);
    return i;
}