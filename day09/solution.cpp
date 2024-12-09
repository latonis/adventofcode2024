#include <string>
#include <utility>

#include "../utils/utils.h"

unsigned long long calculate_checksum(std::vector<int> disk_map) {
    unsigned long long total = 0;
    for (int i = 0; i < disk_map.size(); i++) {
        if (disk_map[i] != -1) {
            total += (long long)(i * (disk_map[i]));
        };
    }
    return total;
}

std::vector<int> shift_left(std::vector<int> disk_map) {
    int l = 0;
    int r = disk_map.size() - 1;

    while (l < r) {
        if (disk_map[r] != -1 and disk_map[l] == -1)
            std::swap(disk_map[l], disk_map[r]);

        while (disk_map[l] != -1) {
            l += 1;
        }

        while (disk_map[r] == -1) {
            r -= 1;
        }
    }
    return disk_map;
}

int part_one() {
    auto input = get_input_one_line("./input");
    std::vector<int> disk_map;
    int num = 0;
    int id = 0;
    for (int i = 0; i < input.size(); i++) {
        int chr = input[i] - '0';
        if (num % 2) {
            chr = -1;
        } else {
            chr = id;
        }

        for (int x = 0; x < (input[i] - '0'); x++) {
            disk_map.push_back(chr);
        }

        if (not(num % 2)) {
            id += 1;
        }

        num += 1;
    }

    disk_map = shift_left(disk_map);
    std::cout << "Checksum: " << calculate_checksum(disk_map) << "\n";
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
