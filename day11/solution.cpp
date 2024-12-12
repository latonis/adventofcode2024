#include <cmath>
#include <string>
#include <unordered_map>
#include <utility>

#include "../utils/utils.h"
int count_digits(unsigned long long i) {
    if (i == 0) return 1;

    int count = 0;
    while (i != 0) {
        i /= (unsigned long long)10;
        count++;
    }
    return count;
}

std::vector<unsigned long long> pebble(unsigned long long p) {
    // If the stone is engraved with the number 0, it is replaced by a stone
    // engraved with the number 1.
    if (p == 0) {
        return {1};
    }

    // If the stone is engraved with a number that has an even number of digits,
    // it is replaced by two stones. The left half of the digits are engraved on
    // the new left stone, and the right half of the digits are engraved on the
    // new right stone. (The new numbers don't keep extra leading zeroes: 1000
    // would become stones 10 and 0.)
    int digits = count_digits(p);
    if (not(count_digits(p) % 2)) {
        auto s = std::to_string(p);
        int n = s.length();
        // std::cout << "digits: " << digits << "\n";
        // std::cout << s << "\n";
        auto fhs = s.substr(0, n / 2);
        auto shs = s.substr(n / 2, n - n / 2);
        // std::cout << fhs << " " << shs << "\n";
        auto fh = std::stoull(fhs);
        auto sh = std::stoull(shs);
        return {fh, sh};
    }

    return {p * (unsigned long long)2024};
};

int part_one() {
    auto inp = get_input_one_line("./input") | std::ranges::views::split(' ') |
               std::views::transform([](auto v) {
                   unsigned long long i = 0;
                   std::from_chars(v.data(), v.data() + v.size(), i);
                   return i;
               }) |
               std::ranges::to<std::vector>();

    std::unordered_map<unsigned long long, unsigned long long> s;
    long long total = 0;

    for (const auto& i : inp) {
        s.insert({i, 1});
    }

    for (int _ = 0; _ < 25; _++) {
        std::unordered_map<unsigned long long, unsigned long long> c;
        for (const auto& e : s) {
            auto p = pebble(e.first);
            for (const auto& stone : p) {
                if (c.contains(stone)) {
                    c.find(stone)->second += e.second;
                } else {
                    c.insert({stone, e.second});
                }
            }
        }

        s = c;
    }

    for (const auto& p : s) {
        total += p.second;
    }

    std::cout << "Pebble totals: " << total << "\n";

    return 0;
}

int part_two() {
    auto inp = get_input_one_line("./input") | std::ranges::views::split(' ') |
               std::views::transform([](auto v) {
                   unsigned long long i = 0;
                   std::from_chars(v.data(), v.data() + v.size(), i);
                   return i;
               }) |
               std::ranges::to<std::vector>();

    std::unordered_map<unsigned long long, unsigned long long> s;
    long long total = 0;

    for (const auto& i : inp) {
        s.insert({i, 1});
    }

    for (int _ = 0; _ < 75; _++) {
        std::unordered_map<unsigned long long, unsigned long long> c;
        for (const auto& e : s) {
            auto p = pebble(e.first);
            for (const auto& stone : p) {
                if (c.contains(stone)) {
                    c.find(stone)->second += e.second;
                } else {
                    c.insert({stone, e.second});
                }
            }
        }

        s = c;
    }

    for (const auto& p : s) {
        total += p.second;
    }

    std::cout << "Pebble totals: " << total << "\n";

    return 0;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
