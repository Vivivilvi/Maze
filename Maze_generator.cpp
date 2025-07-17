#include "Maze_generator.h"
#include "Cell.h"
#include <random>
#include <queue>
#include <utility>
#include <algorithm>

const int MazeGenerator::dx[4] = { 0, 0, -1, 1 };
const int MazeGenerator::dy[4] = { -1, 1, 0, 0 };

MazeGenerator::MazeGenerator() {
    std::random_device rd;
    rng_.seed(rd());
}

std::unique_ptr<Maze> MazeGenerator::generate(int width, int height) {
    if (width % 2 == 0) width++;
    if (height % 2 == 0) height++;
    width = std::max(width, 5);
    height = std::max(height, 5);

    auto maze = std::make_unique<Maze>(width, height);

    std::uniform_int_distribution<int> distX(1, (width - 2) / 2);
    std::uniform_int_distribution<int> distY(1, (height - 2) / 2);
    int startX = distX(rng_) * 2 - 1;
    int startY = distY(rng_) * 2 - 1;

    carvePath(startX, startY, *maze);

    int entranceX = -1;
    for (int x = 1; x < width - 1; ++x) {
        if (maze->getCell(x, 1).getDisplay() == '.') {
            entranceX = x;
            maze->setEntrance(x);
            break;
        }
    }

    if (entranceX == -1) {
        entranceX = width / 2;
        if (entranceX % 2 == 0) entranceX++;
        maze->setEntrance(entranceX);
    }

    ensureExitPath(*maze, entranceX);

    return maze;
}

void MazeGenerator::carvePath(int x, int y, Maze& maze) {
    maze.getCell(x, y).setVisited(true);
    maze.getCell(x, y).setDisplay('.');

    std::vector<int> dirs = { 0, 1, 2, 3 };
    std::shuffle(dirs.begin(), dirs.end(), rng_);

    for (int dir : dirs) {
        int nx = x + dx[dir] * 2;
        int ny = y + dy[dir] * 2;

        if (maze.isValidPosition(nx, ny) && !maze.getCell(nx, ny).isVisited()) {
            maze.getCell(x + dx[dir], y + dy[dir]).setDisplay('.');
            carvePath(nx, ny, maze);
        }
    }
}

void MazeGenerator::ensureExitPath(Maze& maze, int entranceX) {
    int width = maze.getWidth();
    int height = maze.getHeight();

    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));
    std::vector<std::vector<std::pair<int, int>>> parent(height,
        std::vector<std::pair<int, int>>(width, { -1, -1 }));
    std::queue<std::pair<int, int>> q;

    q.push({ entranceX, 1 });
    visited[1][entranceX] = true;
    parent[1][entranceX] = { entranceX, 0 };

    bool found = false;
    int exitX = -1;

    while (!q.empty() && !found) {
        auto [x, y] = q.front();
        q.pop();

        if (y == height - 2) {
            exitX = x;
            found = true;
            break;
        }

        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d];
            int ny = y + dy[d];

            if (maze.isValidPosition(nx, ny)) {
                Cell& cell = maze.getCell(nx, ny);
                if (cell.getDisplay() == '.' && !visited[ny][nx]) {
                    visited[ny][nx] = true;
                    parent[ny][nx] = { x, y };
                    q.push({ nx, ny });
                }
            }
        }
    }

    if (!found) {
        int x = entranceX;
        int y = 1;

        while (y < height - 2) {
            if (maze.isValidPosition(x, y + 1) && maze.getCell(x, y + 1).getDisplay() == '#') {
                maze.getCell(x, y + 1).setDisplay('.');
            }
            y++;

            if (std::uniform_int_distribution<int>(0, 2)(rng_) == 0 &&
                x > 1 && x < width - 2) {
                int dir = std::uniform_int_distribution<int>(0, 1)(rng_) ? 1 : -1;
                if (maze.getCell(x + dir, y).getDisplay() == '#') {
                    maze.getCell(x + dir, y).setDisplay('.');
                    x += dir;
                }
            }
        }

        exitX = x;
    }

    maze.setExit(exitX);

    int x = exitX;
    int y = height - 2;
    while (y != 0) {
        maze.getCell(x, y).setOnPath(true);
        auto [px, py] = parent[y][x];
        if (px == -1 && py == -1) break;
        x = px;
        y = py;
    }
}

void MazeGenerator::placeTreasure(Maze& maze) {
    int width = maze.getWidth();
    int height = maze.getHeight();

    std::uniform_int_distribution<int> distX(1, width - 2);
    std::uniform_int_distribution<int> distY(1, height - 2);

    for (int tries = 0; tries < 1000; ++tries) {
        int x = distX(rng_);
        int y = distY(rng_);

        Cell& cell = maze.getCell(x, y);
        if (cell.isOnPath() && cell.getDisplay() == '.') {
            cell.setDisplay('$');
            return;
        }
    }

    int x = width / 2;
    int y = height / 2;
    if (maze.getCell(x, y).getDisplay() == '.') {
        maze.getCell(x, y).setDisplay('$');
    }
}

void MazeGenerator::placeTraps(Maze& maze) {
    int width = maze.getWidth();
    int height = maze.getHeight();

    std::uniform_int_distribution<int> dist(0, 2);

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            Cell& cell = maze.getCell(x, y);
            if (cell.getDisplay() == '.' && !cell.isOnPath()) {
                int passages = 0;
                for (int d = 0; d < 4; ++d) {
                    if (maze.isValidPosition(x + dx[d], y + dy[d]) &&
                        maze.getCell(x + dx[d], y + dy[d]).getDisplay() == '.') {
                        passages++;
                    }
                }

                if (passages == 1 && dist(rng_) == 0) {
                    cell.setDisplay('_');
                }
            }
        }
    }
}