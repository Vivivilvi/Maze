#ifndef CELL_H
#define CELL_H

class Cell {
public:
    Cell();

    void setDisplay(char display);
    char getDisplay() const;
    void setVisited(bool visited);
    bool isVisited() const;
    void setOnPath(bool onPath);
    bool isOnPath() const;
    void setIsExitPath(bool isExitPath);
    bool isExitPath() const;

private:
    char display_;
    bool visited_;
    bool on_path_;
    bool is_exit_path_;
};

#endif