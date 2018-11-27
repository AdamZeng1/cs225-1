#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main() {
    SquareMaze maze;
    maze.makeMaze(100, 100);
    PNG * main_pic = maze.drawMazeCreative();
    main_pic->writeToFile("creative.png");

    delete main_pic;
    return 0;
}
