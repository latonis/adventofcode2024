#include <set>

#include "../utils/utils.h"
struct Obstacle {
    int x;
    int y;
};

enum Direction { Up, Down, Left, Right };
std::set<std::pair<int, int>> scored = std::set<std::pair<int, int>>();

struct Cursor {
    int x;
    int y;
    Direction direction;

    void move() {
        switch (direction) {
            case Direction::Up:
                y -= 1;
                break;
            case Direction::Down:
                y += 1;
                break;
            case Direction::Left:
                x -= 1;
                break;
            case Direction::Right:
                x += 1;
                break;
            default:;
        }
    }

    void turn_right() {
        switch (direction) {
            case Direction::Up:
                direction = Direction::Right;
                break;
            case Direction::Down:
                direction = Direction::Left;
                break;
            case Direction::Left:
                direction = Direction::Up;
                break;
            case Direction::Right:
                direction = Direction::Down;
                break;
            default:;
        }
    }
};

int find_loops(Cursor sp, std::set<std::pair<int, int>> obstacles, int xn,
               int yn, std::set<std::pair<int, int>> positions_visited) {
    int loops = 0;
    std::set<std::tuple<int, int, Direction>> positions_visited_l;
    auto sp_og = sp;

    for (const auto& p : positions_visited) {
        if (p.first == sp_og.x and p.second == sp_og.y) {
            continue;
        }

        obstacles.insert({p.first, p.second});

        while (sp.x >= 0 && sp.x < xn && sp.y < yn && sp.y >= 0) {
            if (positions_visited_l.contains({sp.x, sp.y, sp.direction})) {
                loops += 1;
                break;
            }

            positions_visited_l.insert({sp.x, sp.y, sp.direction});

            // back_to_loop:
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
                sp.turn_right();
                // goto back_to_loop;
            } else {
                sp.move();
            }
        }

        obstacles.erase({p.first, p.second});
        positions_visited_l.clear();
        sp = sp_og;
    }
    return loops;
}

std::set<std::pair<int, int>> travel(Cursor sp,
                                     std::set<std::pair<int, int>> obstacles,
                                     int xn, int yn, bool check_loop) {
    std::set<std::pair<int, int>> positions_visited;
    std::set<std::tuple<int, int, Direction>> loops_pls;

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
            sp.turn_right();
        }

        sp.move();
    }

    return positions_visited;
}

int part_one() {
    std::set<std::pair<int, int>> obstacles;
    auto lines = get_input_all_lines("./test-input");
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

    std::cout << "Traveled positions: "
              << travel(sp, obstacles, xn, yn, false).size() << "\n";

    return 0;
}

int part_two() {
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

    auto pos_visited = travel(sp, obstacles, xn, yn, false);

    std::cout << "Traveled positions: "
              << find_loops(sp, obstacles, xn, yn, pos_visited) << "\n";

    return 0;
}

int main() {
    auto part1 = timer<decltype(&part_one)>::time(part_one);
    auto part2 = timer<decltype(&part_two)>::time(part_two);
    return 0;
}
