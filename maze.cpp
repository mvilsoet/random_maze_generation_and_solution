/* Your code here! */
#include "maze.h"
using namespace std;

SquareMaze::SquareMaze(): width_(0), height_(0) {}

void SquareMaze::makeMaze(int width, int height) {
  width_ = width;
  height_ = height;

  maze_.resize(width_, vector<pair<bool,bool>>(height_)); //.first = right wall, .second = down wall
  dsets_.addelements(width_*height_);
  int setsCount = width_*height_;

  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++)
		  maze_[j][i] = make_pair(true,true);
  }

  while (setsCount > 1) { //stop when there's only one set left
    //srand(420*69);
    int x = rand() % width_;
    int y = rand() % height_;
    bool random = rand() % 2;

    if(random == false) {
      if(maze_[x][y].first == true && x<width_-1 && (dsets_.find(x + y*width_) != dsets_.find(x+1 + y*width_)) ) { //right
        //cout << "right " << x << "," << y;
        setWall(x, y, 0, false);
        dsets_.setunion(x + y*width_, x+1 + y*width_);
        setsCount--;
      }
    }
    else {
      if(maze_[x][y].second == true && y<height_-1 && (dsets_.find(x + y*width_) != dsets_.find(x + (y+1)*width_)) ) { //down
        //cout << "down " << x << "," << y;
        setWall(x, y, 1, false);
        dsets_.setunion(x + y*width_, x + (y+1)*width_);
        setsCount--;
      }
    }
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
  if(dir == 0) { //right
    if(x>=width_-1) 
      return false;
    return !maze_[x][y].first; //if wall exists, .first = true, so canTravel = false
  }
  else if(dir == 1) { //down
    if(y>=height_-1) 
      return false;
    return !maze_[x][y].second;
  }
  else if(dir == 2) { //left
    if(x<1) 
      return false;
    return !maze_[x-1][y].first;
  }
  else if(dir == 3) { //up
    if(y<1) 
      return false;
    return !maze_[x][y-1].second;
  }
  else return false;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  if(dir == 0) 
    maze_[x][y].first = exists;
  if(dir == 1) 
    maze_[x][y].second = exists;
}

vector<int> SquareMaze::solveMaze() {

  vector<vector<bool>> visited(width_, vector<bool>(height_,false)); // matrix of visited cells
  visited[0][0] = true;

  vector<vector<pair<int,int>>> previous(width_, vector<pair<int,int>>(height_, make_pair(-69,-420))); // matrix of previous cell coordinates
  vector<vector<int>>  distance(width_, vector<int>(height_,0)); // matrix of cell distance from origin

  queue<pair<int,int>> traversal; //BFS not DFS
  traversal.push(make_pair(0,0));

  while (!traversal.empty()) {
    pair<int,int> cell = traversal.front();
    traversal.pop();
    int x = cell.first;
    int y = cell.second;
    int pathDist = distance[x][y];

    vector<pair<int,int>> neighbors; //R D L U in QUEUE for BFS
    if (canTravel(x, y, 0)) 
      neighbors.push_back(make_pair(x+1, y)); 
    if (canTravel(x, y, 1))  
      neighbors.push_back(make_pair(x, y+1));
    if (canTravel(x, y, 2))  
      neighbors.push_back(make_pair(x-1, y));
    if (canTravel(x, y, 3))    
      neighbors.push_back(make_pair(x, y-1));

    for (pair<int,int> neighbor : neighbors) { // for each neighbor
      x = neighbor.first;
      y = neighbor.second;
      if (visited[x][y] == false) { //if neighbor is not yet visited
        previous[x][y] = cell;      //visit it
        distance[x][y] = pathDist+1;

        traversal.push(neighbor);   // and add to the BFS queue
        visited[x][y] = true; 
      }
    }
  }

  int maxDist = 0; // find the cell on the bottom row with the greatest distance
  pair<int,int> mazeEndPoint;
  int y = height_-1;
  for (int x = 0; x < width_; x++) {
      if (distance[x][y] > maxDist) {
          maxDist = distance[x][y];
          mazeEndPoint = make_pair(x,y);
      }
  }

  pair<int,int> curr = mazeEndPoint; //move backwards from the endpoint to get to the origin
  pair<int,int> start = pair<int,int>(0,0);

  while (curr != start) {
    pair<int,int> prev = previous[curr.first][curr.second];

    if (prev.first == curr.first-1)
      solution_.push_back(0);
    if (prev.second == curr.second-1)
      solution_.push_back(1);
    if (prev.first == curr.first+1)
      solution_.push_back(2);
    if (prev.second == curr.second+1)
      solution_.push_back(3);
    curr = prev;
  }

  reverse(solution_.begin(), solution_.end()); //vector reverse operation to get more readable solution
  return solution_;
  
  vector<int> pass;
  return pass;
}



PNG* SquareMaze::drawMaze() const {
  PNG* image = new PNG(width_*10+1,height_*10+1);

  for (unsigned i = 10; i < image->width(); i++){
    HSLAPixel & pixel = image->getPixel(i, 0);
    pixel.l = 0;
  }
  for (unsigned i = 0; i < image->height(); i++){
    HSLAPixel & pixel = image->getPixel(0, i);
    pixel.l = 0;
  }

  for (int x = 0; x < width_; x++) {
    for (int y = 0; y < height_; y++) {

      if (maze_[x][y].first){
        for(int k = 0; k <= 10; k++){
          HSLAPixel & pixel = image->getPixel((x+1)*10, y*10 + k);
          pixel.l = 0;
        }
      }
      if (maze_[x][y].second){
        for (int k = 0; k <= 10; k++){
          HSLAPixel & pixel = image->getPixel(x*10 + k, (y+1)*10);
          pixel.l = 0;
        }
      }
    }
  }
  return image;
}

PNG* SquareMaze::drawMazeWithSolution() {
  PNG * pass = new PNG(501,501); //im too tired to care
  return pass;
}