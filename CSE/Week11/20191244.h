#include <iostream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <ctime>

using namespace std;

enum Direction {NORTH, SOUTH, EAST, WEST };

struct Cell {
    bool visited;
    bool topWall;
    bool bottomWall;
    bool leftWall;
    bool rightWall;

    Cell() : visited(false), topWall(true), bottomWall(true), leftWall(true), rightWall(true) {}
};

