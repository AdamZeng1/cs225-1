#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze maze;
    maze.makeMaze(1000, 1000);
    PNG * maze_pic = maze.drawMazeWithSolution();
    maze_pic->writeToFile("mymaze.png");
    delete maze_pic;
    return 0;
}
