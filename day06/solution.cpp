#include <set>

#include "../utils/utils.h"
struct Obstacle {
    int x;
    int y;
};

enum Direction { Up, Down, Left, Right };

struct Cursor {
    int x;
    int y;
    Direction direction;
};

int travel(Cursor sp, std::set<std::pair<int, int>> obstacles, int xn, int yn) {
    std::set<std::pair<int, int>> positions_visited;
    while (sp.x >= 0 && sp.x < xn && sp.y < yn && sp.y >= 0) {
        positions_visited.insert({sp.x, sp.y});

        int p_x = sp.x;
        int p_y = sp.y;

        switch (sp.direction) {
            case Direction::Down:
                p_y += 1;
                break;
            case Direction::Up:
                p_y -= 1;
                break;
            case Direction::Left:
                p_x -= 1;
                break;
            case Direction::Right:
                p_x += 1;
                break;
            default:;
        }

        if (obstacles.contains({p_x, p_y})) {
            switch (sp.direction) {
                case Direction::Up:
                    sp.direction = Direction::Right;
                    break;
                case Direction::Down:
                    sp.direction = Direction::Left;
                    break;
                case Direction::Left:
                    sp.direction = Direction::Up;
                    break;
                case Direction::Right:
                    sp.direction = Direction::Down;
                    break;
                default:;
            }
        }
        switch (sp.direction) {
            case Direction::Up:
                sp.y -= 1;
                break;
            case Direction::Down:
                sp.y += 1;
                break;
            case Direction::Left:
                sp.x -= 1;
                break;
            case Direction::Right:
                sp.x += 1;
                break;
            default:;
        }
    }

    return positions_visited.size();
}

int part_one() {
    std::set<std::pair<int, int>> obstacles;
    auto lines = get_input_all_lines("./input");
    int yn = lines.size();
    int xn = lines[0].size();
    Cursor sp;

    for (int y = 0; y < yn; y++) {
        for (int x = 0; x < xn; x++) {
            char c = lines[y][x];
            if (c == '#') {
                obstacles.insert({x, y});
            } else if (c == '^') {
                sp = Cursor(x, y, Direction::Up);
            }
        }
    }

    std::cout << "Traveled positions: " << travel(sp, obstacles, xn, yn)
              << "\n";

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
