#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"
#include <random>

class MazeGenerator {
public:
    MazeGenerator();
    std::unique_ptr<Maze> generate(int width, int height);

    void placeTreasure(Maze& maze);
    void placeTraps(Maze& maze);

private:
    void carvePath(int x, int y, Maze& maze);
    void ensureExitPath(Maze& maze, int entranceX);
    std::mt19937 rng_;
    static const int dx[4];
    static const int dy[4];
};
#endif