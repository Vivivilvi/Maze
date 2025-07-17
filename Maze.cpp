#include "maze.h"
#include <stdexcept>

Maze::Maze(int width, int height) : width_(width), height_(height) {
    grid_.resize(height_, std::vector<Cell>(width_));
}

Cell& Maze::getCell(int x, int y) {
    if (!isValidPosition(x, y)) {
        throw std::out_of_range("Invalid maze coordinates");
    }
    return grid_[y][x];
}

const Cell& Maze::getCell(int x, int y) const {
    if (!isValidPosition(x, y)) {
        throw std::out_of_range("Invalid maze coordinates");
    }
    return grid_[y][x];
}

int Maze::getWidth() const { return width_; }
int Maze::getHeight() const { return height_; }

void Maze::setEntrance(int x) {
    if (!isValidPosition(x, 0)) {
        throw std::out_of_range("Invalid entrance position");
    }
    getCell(x, 0).setDisplay('@');
    getCell(x, 1).setDisplay('.');
}

void Maze::setExit(int x) {
    if (!isValidPosition(x, height_ - 1)) {
        throw std::out_of_range("Invalid exit position");
    }
    getCell(x, height_ - 1).setDisplay('0');
    getCell(x, height_ - 2).setDisplay('.');
}

bool Maze::isValidPosition(int x, int y) const {
    return x >= 0 && x < width_ && y >= 0 && y < height_;
}