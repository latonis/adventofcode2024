#include "../utils/utils.h"

bool check_inc_dec(std::vector<int> input_ints) {
    // inc check
    int count = 0;

    for (int i = 0; i < input_ints.size() - 1; i = i + 1) {
        int diff = input_ints[i + 1] - input_ints[i];
        if (diff >= 1 && diff <= 3) {
            count += 1;
        }
    }

    if (count >= input_ints.size() - 1) {
        return true;
    }

    // dec check
    count = 0;

    for (int i = 0; i < input_ints.size() - 1; i = i + 1) {
        int diff = input_ints[i] - input_ints[i + 1];
        if (diff >= 1 && diff <= 3) {
            count += 1;
        }
    }

    if (count >= input_ints.size() - 1) {
        return true;
    }
    return false;
}

bool check_vec(std::vector<int> input_ints) {
    if (check_inc_dec(input_ints)) {
        return true;
    }

    for (int i = 0; i < input_ints.size(); i = i + 1) {
        std::vector<int> tmp = input_ints;
        tmp.erase(tmp.begin() + i);
        if (check_inc_dec(tmp)) {
            return true;
        }
    }

    return false;
}

void part_one() {
    int total = 0;
    for (std::string line : get_input_all_lines("./input")) {
        auto input_ints = line | std::views::split(' ') |
                          std::views::transform([](auto v) {
                              int i = 0;
                              std::from_chars(v.data(), v.data() + v.size(), i);
                              return i;
                          }) |
                          std::ranges::to<std::vector>();

        if (check_inc_dec(input_ints)) {
            total += 1;
        }
    }

    std::cout << "Total: " << total << "\n";
}

void part_two() {
    int total = 0;
    for (std::string line : get_input_all_lines("./input")) {
        auto input_ints = line | std::views::split(' ') |
                          std::views::transform([](auto v) {
                              int i = 0;
                              std::from_chars(v.data(), v.data() + v.size(), i);
                              return i;
                          }) |
                          std::ranges::to<std::vector>();

        if (check_vec(input_ints)) {
            total += 1;
        }
    }

    std::cout << "Total: " << total << "\n";
}

int main() {
    part_one();
    part_two();
    return 0;
}
