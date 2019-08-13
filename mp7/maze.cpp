/* Your code here! */
#include "maze.h"
#include "./cs225/PNG.h"
#include <queue>
using std::queue;

SquareMaze::SquareMaze(){
    maze = NULL;
}

void SquareMaze::makeMaze (int w, int h){
    // clear existed
    if (maze != NULL){
        delete[] maze;
    }

    // initialize a graph paper
    width = w;
    height = h;
    maze = new Cell[width*height];
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            maze[width*i+j].x_ = j;
            maze[width*i+j].y_ = i;
            maze[width*i+j].r_wall = true;
            maze[width*i+j].b_wall = true;
            maze[width*i+j].visited = false;
            maze[width*i+j].dist = 0;
        }
    }

    // dset tool
    DisjointSets tool;
    tool.addelements(width*height);
    // prepare to break walls
    bool r_b;
    int i, j;
    int this_idx, neib_idx;
    int ct = 0;
    // srand (time(NULL));
    // break walls
    while (true){
        i = rand() % height;
        j = rand() % width;
        this_idx = width*i+j;
        r_b = rand()%2;
        if (r_b){// to break bottom wall
            if (i == height-1){// bottom-most
                continue;
            }
            neib_idx = width*(i+1)+j;
            if (tool.find(this_idx) != tool.find(neib_idx)){// check if already connected
                maze[this_idx].b_wall = false;
                tool.setunion(this_idx, neib_idx);
                ct += 1;
            }
            if (ct == width*height-1){
                break;
            }
        }else{// to break right wall
            if (j == width-1){// right-most
                continue;
            }
            neib_idx = width*i+j+1;
            if (tool.find(this_idx) != tool.find(neib_idx)){// check if already connected
                maze[this_idx].r_wall = false;
                tool.setunion(this_idx, neib_idx);
                ct += 1;
            }
            if (ct == width*height-1){
                break;
            }
        }
    }
}


bool SquareMaze::canTravel (int x, int y, int dir) const{
    if (dir == 0){// right
        return !maze[width*y+x].r_wall;
    }else if (dir == 1){// down
        return !maze[width*y+x].b_wall;
    }else if (dir == 2){// left, watch left
        if (x == 0){
            return false;
        }else{
            return !maze[width*y+x-1].r_wall;
        }
    }else if (dir == 3){// up, watch top
        if (y == 0){
            return false;
        }else{
            return !maze[width*(y-1)+x].b_wall;
        }
    }else{
        return false;
    }
}


void SquareMaze::setWall (int x, int y, int dir, bool exists){
    if (dir == 0){// right
        maze[width*y+x].r_wall = exists;
        return;
    }
    if (dir == 1){// bottom
        maze[width*y+x].b_wall = exists;
        return;
    }
}

vector<int> SquareMaze::solveMaze (){
    vector<int> solution;
    Cell cur;
    int r, b, l, t;
    // implement BFS
    queue<Cell> q;
    q.push(maze[0]);
    while (!q.empty()){
        cur = q.front();
        q.pop();
        // four neighbors
        if (canTravel(cur.x_, cur.y_, 0)){
            r = width*cur.y_ + cur.x_+1;
            if (maze[r].visited == false){
                q.push(maze[r]);
                maze[r].visited = true;
                maze[r].dist = maze[width*cur.y_ + cur.x_].dist + 1;
                maze[r].par_idx = width*cur.y_ + cur.x_;
            }
        }
        if (canTravel(cur.x_, cur.y_, 1)){
            b = width*(cur.y_+1) + cur.x_;
            if (maze[b].visited == false){
                q.push(maze[b]);
                maze[b].visited = true;
                maze[b].dist = maze[width*cur.y_ + cur.x_].dist + 1;
                maze[b].par_idx = width*cur.y_ + cur.x_;
            }
        }
        if (canTravel(cur.x_, cur.y_, 2)){
            l = width*cur.y_ + cur.x_-1;
            if (maze[l].visited == false){
                q.push(maze[l]);
                maze[l].visited = true;
                maze[l].dist = maze[width*cur.y_ + cur.x_].dist + 1;
                maze[l].par_idx = width*cur.y_ + cur.x_;
            }
        }
        if (canTravel(cur.x_, cur.y_, 3)){
            t = width*(cur.y_-1) + cur.x_;
            if (maze[t].visited == false){
                q.push(maze[t]);
                maze[t].visited = true;
                maze[t].dist = maze[width*cur.y_ + cur.x_].dist + 1;
                maze[t].par_idx = width*cur.y_ + cur.x_;
            }
        }
    }
    // last row looking for max dist and corresponding index
    int max_idx = width*(height-1);
    int max = maze[max_idx].dist;
    for (int k=1; k<width; k++){
        if (maze[width*(height-1) + k].dist > max){
            max_idx = width*(height-1) + k;
            max = maze[max_idx].dist;
        }
    }
    // traceback
    int par_pos;
    while (max_idx != 0){
        par_pos = max_idx - maze[max_idx].par_idx;
        if (par_pos == 1){// ->
            solution.insert(solution.begin(),0);
        }
        if (par_pos == width){
            solution.insert(solution.begin(),1);
        }
        if (par_pos == -1){// <-
            solution.insert(solution.begin(),2);
        }
        if (par_pos == -width){
            solution.insert(solution.begin(),3);
        }
        max_idx = maze[max_idx].par_idx;
    };
    return solution;
}


PNG* SquareMaze::drawMaze () const{
    PNG* ret = new PNG(width*10+1, height*10+1);
    // top bound with opening
    for (int j = 10; j < width*10+1; j++ ){
        ret->getPixel(j,0).h = 0;
        ret->getPixel(j,0).s = 0;
        ret->getPixel(j,0).l = 0;
        ret->getPixel(j,0).a = 1;
    }
    // left bound
    for (int i = 0; i < height*10+1; i++ ){
        ret->getPixel(0,i).h = 0;
        ret->getPixel(0,i).s = 0;
        ret->getPixel(0,i).l = 0;
        ret->getPixel(0,i).a = 1;
    }
    // walls
    for (int j = 0; j < width; j++){
        for (int i = 0; i < height; i++){
            if(maze[width*i + j].r_wall){
                for (int k = 0; k< 11; k++){
                    ret->getPixel((j+1)*10, i*10+k).h = 0;
                    ret->getPixel((j+1)*10, i*10+k).s = 0;
                    ret->getPixel((j+1)*10, i*10+k).l = 0;
                    ret->getPixel((j+1)*10, i*10+k).a = 1;
                }
            }
            if (maze[width*i + j].b_wall){
                for (int k = 0; k< 11; k++){
                    ret->getPixel(j*10+k, (i+1)*10).h = 0;
                    ret->getPixel(j*10+k, (i+1)*10).s = 0;
                    ret->getPixel(j*10+k, (i+1)*10).l = 0;
                    ret->getPixel(j*10+k, (i+1)*10).a = 1;
                }
            }
        }
    }
    return ret;
}

PNG* SquareMaze::drawMazeWithSolution (){
    PNG* ret = drawMaze();
    vector<int> dirs = solveMaze();
    int x = 5;
    int y = 5;
    // decision trace one by one
    for (size_t i = 0; i < dirs.size(); i++){
        if (dirs[i] == 0){
            for (int j = 0; j < 11; j++){
                ret->getPixel(x+j, y).h = 0;
                ret->getPixel(x+j, y).s = 1;
                ret->getPixel(x+j, y).l = 0.5;
                ret->getPixel(x+j, y).a = 1;
            }
            x = x + 10;
        }
        if (dirs[i] == 1){
            for (int j = 0; j < 11; j++){
                ret->getPixel(x, y+j).h = 0;
                ret->getPixel(x, y+j).s = 1;
                ret->getPixel(x, y+j).l = 0.5;
                ret->getPixel(x, y+j).a = 1;
            }
            y = y + 10;
        }
        if (dirs[i] == 2){
            for (int j = 0; j < 11; j++){
                ret->getPixel(x-j, y).h = 0;
                ret->getPixel(x-j, y).s = 1;
                ret->getPixel(x-j, y).l = 0.5;
                ret->getPixel(x-j, y).a = 1;
            }
            x = x - 10;
        }
        if (dirs[i] == 3){
            for (int j = 0; j < 11; j++){
                ret->getPixel(x, y-j).h = 0;
                ret->getPixel(x, y-j).s = 1;
                ret->getPixel(x, y-j).l = 0.5;
                ret->getPixel(x, y-j).a = 1;
            }
            y = y - 10;
        }
    }
    // last opening
    for (int k = 0; k < 9; k++){
        ret->getPixel(x-4+k, y+5).h = 0;
        ret->getPixel(x-4+k, y+5).s = 0;
        ret->getPixel(x-4+k, y+5).l = 1;
        ret->getPixel(x-4+k, y+5).a = 1;
    }
    return ret;
}

