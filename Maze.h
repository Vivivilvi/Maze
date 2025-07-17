#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <memory>
#include "cell.h"

class Maze {
public:
    Maze(int width, int height);
    Cell& getCell(int x, int y);
    const Cell& getCell(int x, int y) const;

    int getWidth() const;
    int getHeight() const;

    void setEntrance(int x);
    void setExit(int x);

    bool isValidPosition(int x, int y) const;

private:
    int width_;
    int height_;
    std::vector<std::vector<Cell>> grid_;
};
#endif