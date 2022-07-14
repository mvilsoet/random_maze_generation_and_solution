/* Your code here! */
#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"

#include <vector>
#include <map>
#include <utility>
#include <stack>
#include <queue>

using namespace std;
using namespace cs225;

class SquareMaze {
  public: 

    SquareMaze(); 
    //~SquareMaze(); 
    
    void makeMaze (int width, int height); //Makes a new SquareMaze of the given height and width. 
    bool canTravel (int x, int y, int dir) const; //This uses your representation of the maze to determine whether it is possible to travel in the given direction from the square at coordinates (x,y). 
    void setWall (int x, int y, int dir, bool exists); //Sets whether or not the specified wall exists. 
    vector<int> solveMaze (); //Solves this SquareMaze. 
    PNG* drawMaze () const; //Draws the maze without the solution. 
    PNG* drawMazeWithSolution (); //This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze to show the solution vector and the exit.

  private:

    vector<vector<pair<bool,bool>>> maze_; //2D vector of cells that only have down and right
    vector<int> solution_; //array of ints(directions) to move in

    DisjointSets dsets_;
    int width_;
    int height_;

};
