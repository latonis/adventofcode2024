#include <format>
#include <numeric>

#include "../utils/utils.h"

std::vector<std::string> ops_list;

void recurse(std::vector<char> alphabet, std::string prefix, int n, int k) {
    if (k == 0) {
        ops_list.push_back(prefix);
        return;
    }

    for (int i = 0; i < n; i++) {
        recurse(alphabet, prefix + alphabet[i], n, k - 1);
    }
}

void gen_perms(std::vector<char> set, int k, int n) {
    ops_list.clear();
    recurse(set, "", n, k);
}

bool is_solvable(std::vector<int> inputs, unsigned long long desired,
                 bool concat) {
    // check addition
    if (desired == std::reduce(inputs.begin(), inputs.end())) {
        return true;
    }

    // check mult
    unsigned long long total = 1;
    for (int i = 0; i < inputs.size(); i++) {
        total *= inputs[i];
    }

    if (total == desired) {
        return true;
    }
    std::vector<char> set_chars = {'*', '+'};
    if (concat) {
        set_chars.push_back('|');
    }

    gen_perms(set_chars, inputs.size(), set_chars.size());

    total = 0;

    // handle combinations of operators
    for (int o = 0; o < ops_list.size(); o++) {
        auto ops = ops_list[o];
        total = inputs[0];
        for (int i = 1; i < inputs.size(); i++) {
            long val_1 = inputs[i];
            if (ops[i - 1] == '*') {
                total *= (val_1);
            } else if (ops[i - 1] == '+') {
                total += (val_1);
            } else if (ops[i - 1] == '|') {
                total = stoll(std::format("{}{}", total, val_1));
            }
        }
        if (total == desired) {
            return true;
        }
    }
    return false;
}

int part_one() {
    long long total = 0;
    for (std::string line : get_input_all_lines("./test-input")) {
        auto res = stoull(line.substr(0, line.find(": ")));

        auto input_ints = line.substr(line.find(": ") + 2) |
                          std::views::split(' ') |
                          std::views::transform([](auto v) {
                              int i = 0;
                              std::from_chars(v.data(), v.data() + v.size(), i);
                              return i;
                          }) |
                          std::ranges::to<std::vector>();

        if (is_solvable(input_ints, res, false)) {
            total += res;
        }
    }

    std::cout << "Total for solvable: " << total << "\n";
    return total;
}

int part_two() {
    long long total = 0;
    for (std::string line : get_input_all_lines("./input")) {
        auto res = stoull(line.substr(0, line.find(": ")));

        auto input_ints = line.substr(line.find(": ") + 2) |
                          std::views::split(' ') |
                          std::views::transform([](auto v) {
                              int i = 0;
                              std::from_chars(v.data(), v.data() + v.size(), i);
                              return i;
                          }) |
                          std::ranges::to<std::vector>();

        if (is_solvable(input_ints, res, true)) {
            total += res;
        }
    }

    std::cout << "Total for solvable: " << total << "\n";
    return total;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
