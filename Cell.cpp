#include "Cell.h"

Cell::Cell() : display_('#'), visited_(false), on_path_(false), is_exit_path_(false) {}

void Cell::setDisplay(char display) { display_ = display; }
char Cell::getDisplay() const { return display_; }

void Cell::setVisited(bool visited) { visited_ = visited; }
bool Cell::isVisited() const { return visited_; }

void Cell::setOnPath(bool onPath) { on_path_ = onPath; }
bool Cell::isOnPath() const { return on_path_; }

void Cell::setIsExitPath(bool isExitPath) { is_exit_path_ = isExitPath; }
bool Cell::isExitPath() const { return is_exit_path_; }