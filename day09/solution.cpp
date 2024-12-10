#include <any>
#include <string>
#include <utility>

#include "../utils/utils.h"

struct File {
    // -1 is free space
    long long id;
    int length;
};

std::vector<File> consolidate(std::vector<File> disk_map) {
    int n = disk_map.size();
    for (int i = 0; i < n - 1; i++) {
        if (disk_map[i].id == -1 and disk_map[i + 1].id == -1) {
            disk_map[i].length += disk_map[i + 1].length;
            disk_map.erase(disk_map.begin() + i + 1);
            n = disk_map.size();
            i -= 1;
        }
    }
    return disk_map;
}

long long calculate_checksum_p1(std::vector<int> disk_map) {
    unsigned long long total = 0;
    for (int i = 0; i < disk_map.size(); i++) {
        if (disk_map[i] != -1) {
            total += (long long)(i * (disk_map[i]));
        };
    }
    return total;
}

long long calculate_checksum_p2(std::vector<File> disk_map) {
    long long total = 0;
    long long id = 0;
    for (int i = 0; i < disk_map.size(); i++) {
        for (int x = 0; x < disk_map[i].length; x++) {
            if (disk_map[i].id != -1) {
                // std::cout << id << " * " << disk_map[i].id << "\n";
                total += (long long)(id * (disk_map[i].id));
            }
            id += 1;
        }
    }
    return total;
}

std::vector<int> shift_left_p1(std::vector<int> disk_map) {
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

void print_map(std::vector<File> disk_map) {
    for (const auto f : disk_map) {
        for (int i = 0; i < f.length; i++) {
            if (f.id != -1) {
                std::cout << f.id;
            } else {
                std::cout << '.';
            }
            std::cout << " ";
        }
        std::cout << "|";
    }
    std::cout << "\n";
}

std::vector<File> move_left(std::vector<File> disk_map) {
    int l = 0;
    int r = disk_map.size() - 1;

    while (l < r and l < disk_map.size()) {
        if (disk_map[l].id == -1 and disk_map[r].id != -1 and
            disk_map[l].length >= disk_map[r].length) {
            int free_space_left = disk_map[l].length - disk_map[r].length;
            disk_map[l].length = disk_map[r].length;

            std::swap(disk_map[l], disk_map[r]);
            if (free_space_left > 0) {
                disk_map.insert(disk_map.begin() + l + 1,
                                File(-1, free_space_left));
            }

            r -= 1;
            l = 0;
            disk_map = consolidate(disk_map);
        }

        while (disk_map[l].id != -1) {
            l += 1;
        }

        while (disk_map[r].id == -1) {
            r -= 1;
        }

        if (disk_map[l].length < disk_map[r].length) {
            l += 1;
        }

        if (l >= r) {
            l = 0;
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

    disk_map = shift_left_p1(disk_map);
    std::cout << "Checksum: " << calculate_checksum_p1(disk_map) << "\n";
    return 0;
}

int part_two() {
    auto input = get_input_one_line("./input");
    std::vector<File> disk_map;
    unsigned long long num = 0;
    unsigned long long id = 0;

    for (int i = 0; i < input.size(); i++) {
        int chr = input[i] - '0';

        if (chr != 0) {
            disk_map.push_back(File((num % 2) ? -1 : id, chr));
        }

        if (not(num % 2)) {
            id += 1;
        }

        num += 1;
    }
    // disk_map = consolidate(disk_map);
    disk_map = move_left(disk_map);
    std::cout << "Checksum: " << calculate_checksum_p2(disk_map) << "\n";
    // print_map(disk_map);

    return 0;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
