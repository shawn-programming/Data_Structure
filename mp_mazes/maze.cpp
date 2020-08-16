/* Your code here! */

#include "maze.h"


void SquareMaze::makeMaze(int width, int height){

    this->width = width;
    this->height = height;

    maze = new Square*[height];
    for(int i=0; i<height; i++){
        maze[i] = new Square[width];
    }
    
    dset = new DisjointSets(width*height);

    reMakeMaze(0,0);
    // maze[exit[1]][exit[0]].downWall = false;
    
}

void SquareMaze::makePath(int fromX, int fromY, int toX, int toY){
    if(fromX < toX){
        setWall(fromX, fromY, 0, false);
    }
    else if(fromY < toY){
        setWall(fromX, fromY, 1, false);
    }
    else if(fromX > toX){
        setWall(toX, toY, 0, false);
    }
    else if(fromY > toY){
        setWall(toX, toY, 1, false);
    }
}

int SquareMaze::pick_dir(int x, int y){
    vector<int> dir;
    // right
    if(x+1 < width && maze[y][x+1].visited == false) dir.push_back(0);
    // down
    if(y+1 < height && maze[y+1][x].visited == false) dir.push_back(1);
    // left
    if(x-1 >= 0 && maze[y][x-1].visited == false) dir.push_back(2);
    // up
    if(y-1 >= 0 && maze[y-1][x].visited == false) dir.push_back(3);

    if(dir.size() == 0) return -1;
    
    return dir[rand() % dir.size()];
}



void SquareMaze::reMakeMaze(int x, int y){
    // int root = dset->find(width*y + x);
    
    maze[y][x].visited = true;

    while(1){
        int dir = pick_dir(x,y);
        if(dir == -1) return;
        else if(dir == 0){ //right
            // cout << "right" << endl;
            makePath(x, y, x+1, y);
            reMakeMaze(x+1, y);
        }
        else if(dir == 1){ //down
            // cout << "down" << endl;
            makePath(x, y, x, y+1);
            reMakeMaze(x, y+1);
        }
        else if(dir == 2){ // left
            // cout << "left" << endl;
            makePath(x, y, x-1, y);
            reMakeMaze(x-1, y);
        }
        else if(dir == 3){ // up
            // cout << "up" << endl;
            makePath(x, y, x, y-1);
            reMakeMaze(x, y-1);
        }
    }   
}


bool SquareMaze::canTravel(int x, int y, int dir)const{
    if(dir == 0){
        // right
        return x+1 < width && !(maze[y][x].rightWall);
    }
    else if(dir == 1){
        // down
        return y+1 < height && !(maze[y][x].downWall);
    }
    else if(dir == 2){
        // left
        return x-1 >= 0 && !(maze[y][x-1].rightWall); 
    }   
    else if(dir == 3){
        // up
        return y-1 >= 0 && !(maze[y-1][x].downWall); 
    }
    else{
        cout << "invalid direction" << endl;
        return false;
    }

}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    if(dir == 0){
        // cout<<"rightWall: "<<exists<<endl;
        maze[y][x].rightWall = exists;
        // if(!exists)
        //     dset->setunion(y*width+x, y*width+x+1);
    }
    else if(dir == 1){
        // cout<<"downWall: "<<exists<<endl;
        maze[y][x].downWall = exists;
        // if(!exists)
        //     dset->setunion(y*width+x, y*width+x+y);
    }
    else{
        cout << "invalid setWall" << endl;
    }
}

vector<int> SquareMaze::solveMaze(){
    vector<int> path;
    vector<int> check;
    int max = 0;
    setExit(0,0,check,0,max);
    // cout << "exit x: " << exit[1] << " y: " << exit[0] << endl;
    maze[exit[1]][exit[0]].downWall = false;
    solveMaze(0,0,path);

    return path;
}

void SquareMaze::setExit(int x, int y, vector<int>& vec, int length, int& max){
    // cout << "x: " << exit[0] << " y: " << exit[1] << " length: " << length << " max: " << max << endl;

    if(length > max && y == height-1){
        exit[0] = x;
        exit[1] = y;
        max = length;
    }

    // visit left;
    if(canTravel(x, y, 2) && (vec.empty() || vec.back() != 0)){
        vec.push_back(2);
        setExit(x-1, y, vec, length+1, max);
        vec.pop_back();
    }
    // visit right;
    if(canTravel(x, y, 0) && (vec.empty() || vec.back() != 2)){
        vec.push_back(0);
        setExit(x+1, y, vec, length+1, max);
        vec.pop_back();
    }
    // visit down;
    if(canTravel(x, y, 1) && (vec.empty() || vec.back() != 3)){
        vec.push_back(1);
        setExit(x, y+1, vec, length+1, max);
        vec.pop_back();
    }
    // visit up;
    if(canTravel(x, y, 3) && (vec.empty() || vec.back() != 1)){
        vec.push_back(3);
        setExit(x, y-1, vec, length+1, max);
        vec.pop_back();
    }

}

bool SquareMaze::solveMaze(int x, int y, vector<int>& vec){
    if(!(maze[y][x].downWall) && y == height-1) return true;

    // visit left;
    if(canTravel(x, y, 2) && (vec.empty() || vec.back() != 0)){
        vec.push_back(2);
        if(solveMaze(x-1, y, vec)) return true;
        vec.pop_back();
    }
    // visit right;
    if(canTravel(x, y, 0) && (vec.empty() || vec.back() != 2)){
        vec.push_back(0);
        if(solveMaze(x+1, y, vec)) return true;
        vec.pop_back();
    }
    // visit down;
    if(canTravel(x, y, 1) && (vec.empty() || vec.back() != 3)){
        vec.push_back(1);
        if(solveMaze(x, y+1, vec)) return true;
        vec.pop_back();
    }
    // visit up;
    if(canTravel(x, y, 3) && (vec.empty() || vec.back() != 1)){
        vec.push_back(3);
        if(solveMaze(x, y-1, vec)) return true;
        vec.pop_back();
    }

    return false;
}

PNG* SquareMaze::drawMaze() const{
    PNG* mazePic = new PNG(width*10+1, height*10+1);

    // make the top most row walls with an entrance
    for(int i=0; i<width*10+1; i++){
        if(i>0 && i<10) continue;
        mazePic->getPixel(i, 0).l = 0;
    }

    // make the left most row walls.
    for(int i=0; i<height*10+1; i++){
        mazePic->getPixel(0, i).l = 0;
    }
    
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            if(maze[y][x].rightWall) 
                for(int i=0; i<=10; i++)
                    mazePic->getPixel((x+1)*10, y*10+i).l = 0;
            if(maze[y][x].downWall)
                for(int i=0; i<=10; i++)
                    mazePic->getPixel(x*10+i, (y+1)*10).l = 0;
        }
    }

    // for(int x=0; x<=width; x++){
    //     for(int y=0; y<=height; y++){
    //         mazePic->getPixel((x+1)*10+1, (y+1)*10+1).l = 0;
    //     }
    // }

    return mazePic;
}

PNG* SquareMaze::drawCreativeMaze() const{
    PNG* mazePic = new PNG(width*10+1, height*10+1);
    
    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){
            for(int i=0; i<=10; i++){
                if(i<5) {
                    mazePic->getPixel(x*10+i, y*10+5-i).l = 0;
                    mazePic->getPixel(x*10+i, y*10+5+i).l = 0;
                }
                else {
                    mazePic->getPixel(x*10+i, y*10-5+i).l = 0;
                    mazePic->getPixel(x*10+i, y*10+15-i).l = 0;
                }
            }
        }
    }

    for(int x=0; x<width; x++){
        for(int y=0; y<height; y++){  
            if(!maze[y][x].rightWall){
                for(int i=9; i<=11; i++){
                    mazePic->getPixel(x*10+i, y*10-5+i).l = 1;
                    mazePic->getPixel(x*10+i, y*10+15-i).l = 1;
                }
            }
            if(!maze[y][x].downWall){
                if(y == height-1)
                    for(int i=4; i<=6; i++){
                        if(i<5)
                            mazePic->getPixel(x*10+i, y*10+5+i).l = 1;
                        else
                            mazePic->getPixel(x*10+i, y*10+15-i).l = 1;                 
                    }
                else
                    for(int i=4; i<=6; i++){
                        mazePic->getPixel(x*10+i, y*10+5+i).l = 1;
                        mazePic->getPixel(x*10+i, y*10+15-i).l = 1;                 
                    }
            }
        }
    }

    return mazePic;
}

PNG* SquareMaze::drawMazeWithSolution() {
    PNG* maze = drawMaze();
    vector<int> solution = solveMaze();

    int x = 5;
    int y = 5;

    maze->getPixel(x, y) = HSLAPixel(0, 1, 0.5, 1);

    for(int dir : solution){
        for(int i=0; i<10;i++){
            if(dir == 0){
                x++;
            }
            else if(dir == 1){
                y++;
            }
            else if(dir == 2){
                x--;
            }
            else if(dir == 3){
                y--;
            }
            maze->getPixel(x, y) = HSLAPixel(0, 1, 0.5, 1);
        }
    }

    return maze;
}

PNG* SquareMaze::drawCreativeMazeWithSolution() {
    PNG* maze = drawCreativeMaze();
    cout << "done"<<endl;
    vector<int> solution = solveMaze();

    int x = 5;
    int y = 5;

    maze->getPixel(x, y) = HSLAPixel(0, 1, 0.5, 1);

    for(int dir : solution){
        for(int i=0; i<10;i++){
            if(dir == 0){
                x++;
            }
            else if(dir == 1){
                y++;
            }
            else if(dir == 2){
                x--;
            }
            else if(dir == 3){
                y--;
            }
            maze->getPixel(x, y) = HSLAPixel(0, 1, 0.5, 1);
        }
    }

    return maze;
}
