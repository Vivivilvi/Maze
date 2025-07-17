#include "Maze_generator.h"
#include <iostream>

int main() {
    try {
        int width, height;
        std::cout << "Enter maze width and height (minimum 5): ";
        std::cin >> width >> height;

        MazeGenerator generator;
        auto maze = generator.generate(width, height);

        generator.placeTreasure(*maze);
        generator.placeTraps(*maze);

        for (int y = 0; y < maze->getHeight(); ++y) {
            for (int x = 0; x < maze->getWidth(); ++x) {
                std::cout << maze->getCell(x, y).getDisplay();
            }
            std::cout << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}