#include <map>
#include <tuple>

#include "../utils/utils.h"

std::unordered_map<char, char> next_letters = {
    {'X', 'M'}, {'M', 'A'}, {'A', 'S'}};
auto lines = get_input_all_lines("./input");
enum direction { NONE, N, S, E, W, NW, NE, SW, SE };

std::map<std::pair<int, int>, direction> pos_to_dir = {
    {{-1, -1}, SW}, {{-1, 0}, W},  {{-1, 1}, SE}, {{0, -1}, S},
    {{0, 1}, N},    {{1, -1}, NW}, {{1, 0}, E},   {{1, 1}, NE}};

std::unordered_map<direction, std::pair<int, int>> dir_to_pos = {
    {SW, {-1, -1}}, {W, {-1, 0}},  {SE, {-1, 1}}, {S, {0, -1}},
    {N, {0, 1}},    {NW, {1, -1}}, {E, {1, 0}},   {NE, {1, 1}}};

int recurse(int x, int y, int nx, int ny, direction dir) {
    char cur = lines[y][x];
    if (cur == 'S') {
        return 1;
    }

    int new_y = y + std::get<1>(dir_to_pos.find(dir)->second);
    int new_x = x + std::get<0>(dir_to_pos.find(dir)->second);

    char next = next_letters.find(cur)->second;

    if ((0 <= new_y < ny) and (0 <= new_x < nx)) {
        if (lines[new_y][new_x] == next) {
            return recurse(new_x, new_y, nx, ny, dir);
        }
    }

    return 0;
}

int part_one() {
    int total = 0;
    int ny = lines.size();
    int nx = lines[0].size();
    for (int y = 0; y < lines.size(); y++) {
        for (int x = 0; x < lines[y].size(); x++) {
            auto c = lines[y][x];

            if (c == 'X') {
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        if (i == 0 and j == 0) {
                            continue;
                        }
                        int new_y = y + i;
                        int new_x = x + j;
                        char next = next_letters.find(c)->second;
                        if ((0 <= new_y < ny) and (0 <= new_x < nx)) {
                            if (lines[new_y][new_x] == next) {
                                total +=
                                    recurse(new_x, new_y, nx, ny,
                                            pos_to_dir.find({j, i})->second);
                            }
                        }
                    }
                }
            }
        }
    }

    std::cout << "XMAS times: " << total << "\n";
    return 0;
}

int part_two() {
    int total = 0;
    for (int y = 1; y < lines.size() - 1; y++) {
        for (int x = 1; x < lines[y].size() - 1; x++) {
            auto c = lines[y][x];
            std::vector<char> chars = {lines[y - 1][x - 1], lines[y - 1][x + 1],
                                       lines[y + 1][x - 1],
                                       lines[y + 1][x + 1]};

            if (c == 'A') {
                int m_count = 0;
                int s_count = 0;
                for (auto c : chars) {
                    if (c == 'M') {
                        m_count += 1;
                    } else if (c == 'S') {
                        s_count += 1;
                    }
                }
                if (m_count == 2 and s_count == 2) {
                    if ((lines[y - 1][x - 1] != lines[y + 1][x + 1]) and
                        (lines[y - 1][x + 1] != lines[y + 1][x - 1])) {
                        total += 1;
                    }
                }
            }
        }
    }
    std::cout << "X-MAS times: " << total << "\n";
    return 0;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
