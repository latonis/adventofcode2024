#include "../utils/utils.h"

void part_one() {
    for (std::string line : get_input_all_lines("./test-input")) {
        auto inp =
            line | std::ranges::views::split(' ') |
            std::views::transform([](auto v) { return std::string_view(v); }) |
            std::ranges::to<std::vector>();

        auto input_ints = get_input_one_line("./test-input") |
                          std::views::split('\t') |
                          std::views::transform([](auto v) {
                              int i = 0;
                              std::from_chars(v.data(), v.data() + v.size(), i);
                              return i;
                          }) |
                          std::ranges::to<std::vector>();
    }
}

void part_two() {
    auto line = get_input_one_line("./test-input");
    auto inp =
        line | std::ranges::views::split(' ') |
        std::views::transform([](auto v) { return std::string_view(v); }) |
        std::ranges::to<std::vector>();
}

int main() {
    part_one();
    part_two();
    return 0;
}
