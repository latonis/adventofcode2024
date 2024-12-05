#include "../utils/utils.h"

int part_one() {
    int total = 0;
    std::vector<int> fs;
    std::vector<int> ss;
    for (std::string line : get_input_all_lines("./input")) {
        auto input_ints = line | std::views::split(std::string("   ")) |
                          std::ranges::views::transform([](auto v) {
                              int i = 0;
                              std::from_chars(v.data(), v.data() + v.size(), i);
                              return i;
                          }) |
                          std::ranges::to<std::vector>();
        fs.push_back(input_ints[0]);
        ss.push_back(input_ints[1]);
    }
    std::sort(fs.begin(), fs.end());
    std::sort(ss.begin(), ss.end());

    for (int i = 0; i < ss.size(); i++) {
        total += std::abs(fs[i] - ss[i]);
    }

    std::cout << "Total calculation: " << total << "\n";
    return total;
}

int part_two() {
    int total = 0;
    std::vector<int> fs;
    std::unordered_map<int, int> ss;
    for (std::string line : get_input_all_lines("./input")) {
        auto input_ints = line | std::views::split(std::string("   ")) |
                          std::ranges::views::transform([](auto v) {
                              int i = 0;
                              std::from_chars(v.data(), v.data() + v.size(), i);
                              return i;
                          }) |
                          std::ranges::to<std::vector>();
        fs.push_back(input_ints[0]);
        if (ss.contains(input_ints[1])) {
            ss.find(input_ints[1])->second++;
        } else {
            ss.insert({input_ints[1], 1});
        }
    }

    for (int i = 0; i < fs.size(); i++) {
        if (ss.contains(fs[i])) {
            total += fs[i] * ss.find(fs[i])->second;
        }
    }

    std::cout << "Total calculation similarity: " << total << "\n";
    return total;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
