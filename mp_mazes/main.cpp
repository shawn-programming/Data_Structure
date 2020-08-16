#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

using namespace std;

int main()
{
    SquareMaze m;
    m.makeMaze(50, 50);
    std::cout << "MakeMaze complete" << std::endl;

    cs225::PNG* unsolved = m.drawCreativeMaze();

    // unsolved->writeToFile("creative.png");

    delete unsolved;
    
    std::cout << "drawMaze complete" << std::endl;

    std::vector<int> sol = m.solveMaze();
    std::cout << "solveMaze complete" << std::endl;

    cs225::PNG* solved = m.drawCreativeMazeWithSolution();
    solved->writeToFile("creative.png");
    delete solved;
    std::cout << "drawMazeWithSolution complete" << std::endl;

    return 0;
}