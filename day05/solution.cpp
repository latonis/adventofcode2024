#include <set>

#include "../utils/utils.h"

int index_of(std::vector<int> v, int i) {
    auto idx = find(v.begin(), v.end(), i);
    if (idx != v.end()) {
        return idx - v.begin();
    }
    return -1;
}

bool valid_layout(std::vector<int> page,
                  std::unordered_map<int, std::set<int>> order_map) {
    for (auto o : order_map) {
        int i1 = index_of(page, o.first);
        for (auto const& s : o.second) {
            int i2 = index_of(page, s);
            if (i1 == -1 || i2 == -1) {
                continue;
            }
            if (i2 > i1) {
                return false;
            }
        }
    }
    return true;
}

int part_one() {
    auto blocks = get_input_blocks("./input");
    auto rules = blocks[0];
    auto pages_s = blocks[1];
    std::vector<std::vector<int>> pages;
    for (const auto& p : pages_s) {
        auto to_push = p | std::views::split(',') |
                       std::views::transform([](auto s) {
                           int i = 0;
                           std::from_chars(s.data(), s.data() + s.size(), i);
                           return i;
                       }) |
                       std::ranges::to<std::vector>();

        pages.push_back(to_push);
    }
    std::unordered_map<int, std::set<int>> order_map;

    for (const auto& r : rules) {
        auto order = r | std::views::split('|') |
                     std::views::transform([](auto v) {
                         int i = 0;
                         std::from_chars(v.data(), v.data() + v.size(), i);
                         return i;
                     }) |
                     std::ranges::to<std::vector>();

        if (order_map.contains(order[1])) {
            order_map.find(order[1])->second.insert(order[0]);

        } else {
            order_map.insert({order[1], {order[0]}});
        }
    }

    int c = 0;
    for (const auto& page : pages) {
        if (valid_layout(page, order_map)) c += page[page.size() / 2];
    }
    std::cout << "Total: " << c << std::endl;
    return 0;
}

int part_two() {
    auto line = get_input_one_line("./test-input");
    auto inp =
        line | std::ranges::views::split(' ') |
        std::views::transform([](auto v) { return std::string_view(v); }) |
        std::ranges::to<std::vector>();

    return 0;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    // auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
