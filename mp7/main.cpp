#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    // Write your own main here
    SquareMaze maze;
    maze.makeMaze(100,200);
    PNG* p = maze.drawMaze();
    p->writeToFile("Creative" + string(".png"));
    PNG* q = maze.drawMazeWithSolution();
    q->writeToFile("CreativeSol" + string(".png"));

    return 0;
}
