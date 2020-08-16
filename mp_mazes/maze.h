/* Your code here! */
#pragma once

#include <iostream>
#include <vector>
#include "cs225/PNG.h"
#include "dsets.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;
using namespace cs225;

class Square{
public:
    bool rightWall;
    bool downWall;
    bool visited;
    bool path;
    bool exit;
    Square(){
        rightWall = true;
        downWall = true;
        visited = false;
        exit = false;
    }
};

class SquareMaze {
public:
    ~SquareMaze(){
        for(int i=0; i<height; i++){
            delete[] maze[i];
        }
        // delete[] dset;
    }
    SquareMaze(){}
    void reMakeMaze(int x, int y);
    void makeMaze(int width, int height);
    bool canTravel(int x, int y, int dir) const;
    void setWall(int x, int y, int dir, bool exists);
    void makePath(int fromX, int fromY, int toX, int toY);
    int pick_dir(int x, int y);
    vector<int> solveMaze();
    bool solveMaze(int x, int y, vector<int>& vec);
    void setExit(int x, int y, vector<int>& vec, int length, int& max);
    PNG* drawMaze()const;
    PNG* drawCreativeMaze() const;
    PNG* drawCreativeMazeWithSolution();
    PNG* drawMazeWithSolution();
    

    int exit[2];
     

private:
    int height;
    int width;
    
    vector<int> elem;
    vector<int> parentVec;
    Square** maze = NULL;
    DisjointSets* dset = NULL;
};
