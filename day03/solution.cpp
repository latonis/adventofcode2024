#include <regex>

#include "../utils/utils.h"

void part_one() {
    auto line = get_input_one_line("./input");
    std::regex w_regex("mul\\((\\d{1,3}),(\\d{1,3})\\)",
                       std::regex_constants::icase);

    auto words_begin = std::sregex_iterator(line.begin(), line.end(), w_regex);

    auto words_end = std::sregex_iterator();

    int total = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        int first = std::stoi(match[1].str());
        int second = std::stoi(match[2].str());

        total += first * second;
    }
    std::cout << "Total: " << total << std::endl;
}

void part_two() {
    auto line = get_input_one_line("./input");
    std::regex w_regex(
        "mul\\((\\d{1,3}),(\\d{1,3})\\)|(do\\(\\))|(don't\\(\\))",
        std::regex_constants::icase);

    auto words_begin = std::sregex_iterator(line.begin(), line.end(), w_regex);

    auto words_end = std::sregex_iterator();

    int total = 0;
    bool enabled = true;
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string cur_match = match.str();
        if (cur_match == "don't()") {
            enabled = false;
        } else if (cur_match == "do()") {
            enabled = true;
        }

        if (cur_match.find("mul") != std::string::npos) {
            int first = std::stoi(match[1].str());
            int second = std::stoi(match[2].str());

            if (enabled) {
                total += first * second;
            }
        }
    }
    std::cout << "Total: " << total << std::endl;
}

int main() {
    part_one();
    part_two();
    return 0;
}
