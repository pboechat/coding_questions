/* Imagine a robot sitting on the upper left corner of a grid with H rows and W columns.
The robot can only move in two directions, right and down, but certain cells are "off limits"
such that the robot cannot step on them. Design an algorithm to find a path for the robot 
from the top left to the bottom right */

#include <iostream>
#include <array>
#include <cstring>
#include <vector>

#define O true
#define X false

template <size_t W, size_t H>
struct Grid
{
    typedef std::array<bool, H> Col;
    typedef std::array<Col, W> Cols;

    Cols cols;

    Grid(const std::initializer_list<bool> &values)
    {
        size_t i = 0;
        auto* data = values.begin();
        for (size_t y = 0; y < H; y++) {
            for (size_t x = 0; x < W; x++) {
                cols[x][y] = data[i++];
            }
        }
    }

    Col &operator[](size_t i)
    {
        return cols[i];
    }

    const Col &operator[](size_t i) const
    {
        return cols[i];
    }
};


struct Position 
{
    size_t x;
    size_t y;

};

using Path = std::vector<Position>;

template <size_t W, size_t H>
bool findPath(const Grid<W, H> &grid, Path& path, const Position& pos = {0, 0}) 
{
    path.emplace_back(pos);
    auto rights = W - pos.x - 1;
    auto downs = H - pos.y - 1;
    if (rights == downs) {
        if (rights == 0 && downs == 0) {
            return true;
        }

        // fork

        if (rights > 0 && grid[pos.x + 1][pos.y]) {
            Path newPath;
            // go right
            if (findPath(grid, newPath, { pos.x + 1, pos.y })) {
                // merge
                path.insert(path.end(), newPath.begin(), newPath.end());
                return true;
            }
        }
        if (downs > 0 && grid[pos.x][pos.y + 1]) {
            Path newPath;
            // go down
            if (findPath(grid, newPath, { pos.x, pos.y + 1 })) {
                // merge
                path.insert(path.end(), newPath.begin(), newPath.end());
                return true;
            }
        }
    }
    else 
    {
        size_t a, b;
        if (rights > downs) {
            a = 1; b = 0;
        } else {
            a = 0; b = 1;
        }
        Position nextPos{ pos.x + a, pos.y + b};
        for (size_t i = 0; i < 2; ++i)
        {
            if (nextPos.x <= W && nextPos.y <= H && grid[nextPos.x][nextPos.y]) {
                return findPath(grid, path, nextPos); 
            }
            nextPos = { pos.x + b, pos.y + a };
        }
    }

    return false;
}

void printPath(const Path& path) {
    for (auto& pos : path) {
        std::cout << "(" << pos.x + 1 << ", " << pos.y + 1 << ") ";
    }
}

template <size_t W, size_t H>
void test(const char *name, const Grid<W, H> &grid)
{
    std::cout << name << ": " << std::endl;
    Path path;
    if (findPath(grid, path)) {
        printPath(path);
    } else {
        std::cout << "path not found";
    }
    std::cout << std::endl;
}

int main()
{
    test("1x1",
        Grid<1, 1>{{
            O
        }});
    test(
        "3x3, no obstacles",
        Grid<3, 3>{{
            O,O,O,
            O,O,O,
            O,O,O,
        }});
    test(
        "3x3, center obstacle",
        Grid<3, 3>{{
            O,O,O,
            O,X,O,
            O,O,O,
        }});
    test(
        "5x3, full cornering",
        Grid<5, 3>{{
            O,X,O,O,O,
            O,X,O,O,O,
            O,O,O,O,O,
        }});
    test(
        "3x3, no path",
        Grid<3, 3>{{
            O,O,O,
            O,O,O,
            O,O,X,
        }});
    return 0;
}