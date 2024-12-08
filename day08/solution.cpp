#include <cctype>
#include <set>

#include "../utils/utils.h"

std::set<std::pair<int, int>> antinodes = std::set<std::pair<int, int>>();

int distance_form(int x1, int y1, int x2, int y2) {
    return std::sqrt(std::pow(x2 - x1, 2) + std::pow(y2 - y1, 2));
}

struct Antenna {
    char freq;
    int x;
    int y;
};

void calc_antinodes_p2(const Antenna a, const Antenna b, int xn, int yn) {
    int x_diff = (a.x - b.x);
    int y_diff = (a.y - b.y);
    antinodes.insert(std::make_pair(a.x, a.y));
    antinodes.insert(std::make_pair(b.x, b.y));

    int a1_x = a.x + x_diff;
    int a1_y = a.y + y_diff;

    int a2_x = b.x - x_diff;
    int a2_y = b.y - y_diff;

    while (a1_x < xn && a1_y < yn && a1_x >= 0 && a1_y >= 0) {
        if (a1_x >= 0 && a1_x < xn) {
            if (a1_y >= 0 && a1_y < yn) {
                antinodes.insert(std::make_pair(a1_x, a1_y));
            }
        }

        a1_x += x_diff;
        a1_y += y_diff;
    }

    while (a2_x < xn && a2_y < yn && a2_x >= 0 && a2_y >= 0) {
        if (a2_x >= 0 && a2_x < xn) {
            if (a2_y >= 0 && a2_y < yn) {
                antinodes.insert(std::make_pair(a2_x, a2_y));
            }
        }
        a2_x -= x_diff;
        a2_y -= y_diff;
    }
}

void calc_antinodes_p1(const Antenna& a, const Antenna& b, int xn, int yn) {
    int x_diff = (a.x - b.x);
    int y_diff = (a.y - b.y);

    int a1_x = a.x + x_diff;
    int a1_y = a.y + y_diff;

    int a2_x = b.x - x_diff;
    int a2_y = b.y - y_diff;

    if (a1_x >= 0 && a1_x < xn) {
        if (a1_y >= 0 && a1_y < yn) {
            antinodes.insert(std::make_pair(a1_x, a1_y));
        }
    }

    if (a2_x >= 0 && a2_x < xn) {
        if (a2_y >= 0 && a2_y < yn) {
            antinodes.insert(std::make_pair(a2_x, a2_y));
        }
    }

    return;
}

int part_one() {
    std::unordered_map<char, std::vector<Antenna>> antennae;
    auto lines = get_input_all_lines("./input");
    int yn = lines.size();
    int xn = lines[0].size();
    for (int y = 0; y < yn; y++) {
        for (int x = 0; x < xn; x++) {
            char c = lines[y][x];
            if (std::isalnum(c)) {
                if (antennae.contains(c)) {
                    antennae.find(c)->second.emplace_back(c, x, y);
                } else {
                    antennae.insert({c, {Antenna(c, x, y)}});
                }
            }
        }
    }

    for (const auto& a : antennae) {
        for (int i = 0; i < a.second.size(); i += 1) {
            for (int j = i + 1; j < a.second.size(); j++) {
                calc_antinodes_p1(a.second[i], a.second[j], xn, yn);
            }
        }
    }

    std::cout << "Unique antinodes: " << antinodes.size() << "\n";
    return 0;
}

int part_two() {
    std::unordered_map<char, std::vector<Antenna>> antennae;
    auto lines = get_input_all_lines("./input");
    int yn = lines.size();
    int xn = lines[0].size();
    for (int y = 0; y < yn; y++) {
        for (int x = 0; x < xn; x++) {
            char c = lines[y][x];
            if (std::isalnum(c)) {
                if (antennae.contains(c)) {
                    antennae.find(c)->second.emplace_back(c, x, y);
                } else {
                    antennae.insert({c, {Antenna(c, x, y)}});
                }
            }
        }
    }

    for (const auto& a : antennae) {
        for (int i = 0; i < a.second.size(); i += 1) {
            for (int j = i + 1; j < a.second.size(); j++) {
                calc_antinodes_p2(a.second[i], a.second[j], xn, yn);
            }
        }
    }

    std::cout << "Unique antinodes: " << antinodes.size() << "\n";
    return 0;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    antinodes.clear();
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
