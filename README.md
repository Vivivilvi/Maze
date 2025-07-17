# Maze

A simple C++ console application that generates a randomly constructed maze of arbitrary size (e.g., 20×20, 50×50, etc.) using only standard libraries. The maze is fully enclosed and guaranteed to be solvable, with a clear path from the entrance (top-left) to the exit (bottom-right).

## What it does

* Accepts user-defined dimensions (`width` and `height`);
* Dynamically allocates and fills a 2D grid;
* Uses randomized backtracking (depth-first search) to carve out a maze;
* Displays the resulting maze in the console using ASCII characters (`#`, ` `);
* Ensures the generated maze is solvable.

## Why

This project was created as a practical exercise in:

* Dynamic memory management in C++;
* Depth-first search algorithm with randomization;
* Procedural content generation;
* Efficient output to console with visual clarity.

The task was structured to simulate a real-world scenario where a basic maze generator was needed, such as for prototyping level design in a text-based game or teaching algorithms interactively.

## What it avoids

* External libraries (no SFML, SDL, Qt, ncurses);
* GUI or graphical output (ASCII only);
* Saving to file or loading mazes;
* Path-solving algorithm (generation only, not solving).

## How it works
1. A grid is initialized with all walls;
2. A recursive backtracking algorithm begins from (0, 0);
3. It randomly visits unvisited neighbors and knocks down walls between them;
4. When no unvisited neighbors remain, the algorithm backtracks;
5. The result is a connected, solvable maze without isolated cells.

## Requirements
* C++17;
* Windows / Linux;
* Compiler: MSVC / GCC / Clang;
* Terminal capable of displaying ASCII characters.

## 🚀 Sample usage
```
Enter maze width and height (minimum 5): 20 20

#@###################
#.............#...#.#
#.###########.#.#.#.#
#.#.........#.#.#...#
#.#.#######.#.#.###.#
#.#.#.$...#.#.#.#.#.#
#.#.#.###.#.#.#.#.#.#
#...#...#...#...#.#.#
#.#####.#.#######.#.#
#...#...#.#.#.......#
#####.###.#.#####.###
#.....#...#.....#.._#
#.#####.#######.#####
#.#...#.......#.....#
#.#.#.#.#####.#####.#
#...#.#_#...#.#.._#.#
#.###.###.#.#.#.###.#
#.#.#.....#.#...#...#
#.#.#######.#####.###
#.........#.........#
#0###################
```

## 🧩 Possible improvements
* Add maze-solving visualization (A\*, BFS);
* Export maze to `.txt` or image format;
* Colorized output in console (platform-dependent);
* Option to generate multiple exits or "rooms".
