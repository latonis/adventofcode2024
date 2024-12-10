#include <set>
#include <stack>

#include "../utils/utils.h"

struct Trailhead {
    int x;
    int y;
    int xn;
    int yn;

    bool in_bounds(int x, int y) {
        return (x >= 0 and x < xn and y >= 0 and y < yn);
    }

    int navigate(char current_char, std::vector<std::string> trail) {
        std::set<std::pair<int, int>> visited_trailheads;
        std::stack<std::tuple<char, int, int>> s;
        s.push({current_char, x, y});
        while (not s.empty()) {
            auto cur = s.top();
            x = std::get<1>(cur);
            y = std::get<2>(cur);
            current_char = std::get<0>(cur);
            s.pop();
            std::vector<std::pair<int, int>> possible_states = {
                {x - 1, y}, {x + 1, y}, {x, y - 1}, {x, y + 1}};
            for (const auto& p : possible_states) {
                if (in_bounds(p.first, p.second)) {
                    if (trail[p.second][p.first] == current_char + 1) {
                        x = p.first;
                        y = p.second;

                        if (current_char + 1 == '9') {
                            visited_trailheads.insert({x, y});
                        }
                        s.push({current_char + 1, x, y});
                    }
                }
            }
        }
        return visited_trailheads.size();
    }
};

int part_one() {
    std::vector<std::string> lines = get_input_all_lines("./input");
    auto yn = lines.size();
    auto xn = lines[0].size();
    std::vector<Trailhead> trailheads;
    for (int y = 0; y < yn; y++) {
        for (int x = 0; x < xn; x++) {
            if (lines[y][x] == '0') {
                trailheads.emplace_back(x, y, xn, yn);
            }
        }
    }

    int total = 0;
    for (Trailhead& t : trailheads) {
        total += t.navigate('0', lines);
        // total += t.std::cout << std::format("Trailhead at {},{}\n", t.x,
        // t.y);
    }

    std::cout << "Total: " << total << "\n";
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
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
