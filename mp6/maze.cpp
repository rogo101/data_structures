/* Your code here! */

#include "maze.h"
#include <stdio.h>

using namespace std;

SquareMaze::SquareMaze () {
  return;
}

//Function that checks if move is valid

bool SquareMaze::canTravel ( int x, int y, int angle ) const {
	if (checkValidity(x,y) == false) {
    return false;
  }
	if ((angle==2 && checkValidity(x-1,y) && wallVector[x-1][y][0]==false) || (angle==3 && checkValidity(x,y-1) && wallVector[x][y-1][1]==false) || (angle==1 && checkValidity(x,y+1) && wallVector[x][y][1]==false) || (angle==0 && checkValidity(x+1,y) && wallVector[x][y][0]==false)) {
    return true;
  }
	return false;
}
//Functiion that makes the maze
void SquareMaze::makeMaze(int width, int height) {
  height_ = height;
	width_ = width;
	wallVector = vector<vector<vector<bool>>>(width_);
	for (int i=0; i < width_; i++) {
		wallVector[i] = vector<vector<bool>>(height_);
		for (int j=0; j < height_; j++) {
			wallVector[i][j] = vector<bool>(2);
      wallVector[i][j][1] = true;
			wallVector[i][j][0] = true;
		}
	}

  //Initial Setup

	DisjointSets initializedDisjointSet;
  int size = width_ * height_;
	initializedDisjointSet.addelements(size);
	int maxSize = size;

	while (maxSize > 1) {
		int x = rand() % (width_),  y = rand() % (height_), theta = rand() % 2;
		if (wallVector[x][y][theta] == true) {
			int one = resetPosition(x, y);
			if (theta==1 && y<height_-1) {
				int two = resetPosition(x, y+1);
				if (initializedDisjointSet.find(one)==initializedDisjointSet.find(two)==false) {
          wallVector[x][y][theta] = false;
          maxSize--;
					initializedDisjointSet.setunion(one, two);
				}
			}
			if (theta==0) {
        if (x<width_-1) {
          int two = resetPosition(x+1, y);\
  				if (initializedDisjointSet.find(one)!=initializedDisjointSet.find(two)) {
            wallVector[x][y][theta] = false;
            maxSize--;
  					initializedDisjointSet.setunion(one, two);
  				}
        }
			}
		}
	}

}

//Changes the position  of the pair

pair<int,int> SquareMaze::changePosition(int position) const {
	return pair<int,int>(position/height_, position % height_ );
}

//This function physically draws the solved maze onto the image

PNG * SquareMaze::drawMazeWithSolution () {
  HSLAPixel red(0,1,0.5,1);
	PNG* outputImage = drawMaze();
	vector<int> solution = solveMaze();
	int x = 5, y = 5, i;
	for (int count = 0; count < (int)solution.size(); count++) {
		if (solution[count]==0) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = outputImage -> getPixel(x+i, y);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			x = x + 10;
		}
		else if (solution[count]==1) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = outputImage -> getPixel(x, y+i);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			y  = y + 10;
		}
		else if (solution[count]==2) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = outputImage -> getPixel(x-i, y);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			x = x - 10;
		}
		else if (solution[count]==3) {
			for (i = 0; i <= 10; i++) {
				HSLAPixel & pixel = outputImage -> getPixel(x, y-i);
				pixel.s = red.s;
				pixel.h = red.h;
				pixel.l = red.l;
			}
			y = y - 10;
		}
	}
  if (y < 0){
    return outputImage;
  }
  else {
    y = y + 5;
    x = x - 5;
  }
	for (i = 0; i < 9; i++) {
		HSLAPixel & pixel = outputImage -> getPixel(x + i + 1, y);
		pixel.l = 1;
	}
	return outputImage;
}

//setWall modifies the wallVector based off the validity of the move

void SquareMaze::setWall(int x, int y, int angle, bool true_Holder ) {
  if (checkValidity(x,y) == true) {
    wallVector[x][y][angle] = true_Holder;
  }
  else {
    if (checkValidity(x,y) == true) {
      wallVector[x][y][angle] = true_Holder;
    }
    else {
      return;
    }
  }
}

//Function that calls helpers to solve the maze

vector<int> SquareMaze::solveMaze () {
	vector<int> smallest = smallestDistance();
	reverse(smallest.begin(),smallest.end());
	return smallest;
}

//Draws the maze using HSLAPizel class

PNG * SquareMaze::drawMaze () const {
	int w = width_*10+1, h = height_*10+1;
	PNG* outputImage = new PNG(w, h);

	HSLAPixel dark(0, 0, 0);

	for (int i = 0; i<w; i++) {
		if (i<1 || i>9) {
			HSLAPixel & pixel = outputImage -> getPixel(i, 0);
      pixel.l = dark.l;
      pixel.s = dark.s;
			pixel.h = dark.h;
		}
	}
	for (int i = 0; i<h; i++) {
		HSLAPixel & pixel = outputImage -> getPixel(0, i);
    pixel.l = dark.l;
    pixel.s = dark.s;
    pixel.h = dark.h;
	}
	for (int x=0; x<width_; x++) {
		for (int y=0; y<height_; y++) {
			if (wallVector[x][y][0]) {
				for (int k=0; k<=10; k++) {
					HSLAPixel & pixel = outputImage -> getPixel((x+1)*10, y*10+k);
          pixel.l = dark.l;
          pixel.s = dark.s;
    			pixel.h = dark.h;
				}
			}
			if (wallVector[x][y][1]) {
				for (int i=0; i<=10; i++) {
					HSLAPixel & pixel = outputImage -> getPixel(x*10+i, (y+1)*10);
          pixel.l = dark.l;
          pixel.s = dark.s;
    			pixel.h = dark.h;
				}
			}
		}
	}

	return outputImage;
}

//Unrolls so to speak resets the position of the object

int SquareMaze::resetPosition(int x, int y) const {
	return x * height_ + y;
}

//This function determines the largest distance for an imput vector

int SquareMaze::largestDistance(vector<int>& dist) {
	int y = height_ - 1, highest = resetPosition(0, y);
	for (int x=0; x<width_; x++) {
		int spot = resetPosition(x, y);
		if (dist[spot] > dist[highest]) {
			highest = spot;
		}
    else {
      continue;
    }
	}
	return highest;
}

//A helper function to check the validity of a move

bool SquareMaze::checkValidity (int x, int y) const {
  bool first = y >= 0;
  bool second = x < width_;
  bool third = x >= 0;
  bool fourth = y < height_;
  return first && second && third && fourth;
}

//This function determines the smallest distance for an imput vector

vector<int> SquareMaze::smallestDistance() {
	vector<int> map1 = vector<int>(width_*height_, 0), map2 = vector<int>(width_*height_, 0);
	vector<bool> map3 = vector<bool>(width_*height_, false);
	queue<int> queue1;
	map3[0] = true;
	queue1.push(0);
	while (queue1.empty() == false)
	{
    if (queue1.empty() == true) {
      break;
    }
		int point = queue1.front();
		queue1.pop();
		for (auto & iterator : nextDoor(point)) {
			if (map3[iterator] == false)
			{
				map3[iterator] = true;
				queue1.push(iterator);
        map2[iterator] = point;
				map1[iterator] = map1[point] + 1;
			}
      else {
        continue;
      }
		}
	}
  if (queue1.empty() == true) {
    int angle, endPoint = largestDistance(map1);
  	vector<int> solution;
  	while (map2[endPoint]!=endPoint)
  	{
  		angle = thetaSolver(map2[endPoint], endPoint);
  		solution.push_back(angle);
  		endPoint = map2[endPoint];
  	}
  	return solution;
  }
  else {
    vector<int> solution;
    return solution;
  }

}

//This function gets the direction

int SquareMaze::thetaSolver(int top, int index) {
	pair<int,int> first = changePosition(top);
	int location_X = first.first, location_Y = first.second;
	pair<int,int> spot = changePosition(index);
	int x_vertex = spot.first, y_vertex = spot.second;
  if (location_X == x_vertex+1)
		return 2;
  if (location_X == x_vertex-1)
		return 0;
  if (location_Y == y_vertex+1)
  	return 3;
  if (location_Y == y_vertex-1)
		return 1;
	return int();
}

//Gets adjacent value based off index

vector<int> SquareMaze::nextDoor(int index) {
  vector<int> adjacent;
  pair<int,int> coord = changePosition(index);
  int x = coord.first;
  int y = coord.second;
  if ((checkValidity(x-1, y)) && (!wallVector[x-1][y][0])) {
    adjacent.push_back(resetPosition(x-1,y));
  }
  if ((checkValidity(x, y-1)) && (!wallVector[x][y-1][1])) {
    adjacent.push_back(resetPosition(x,y-1));
  }
  if ((checkValidity(x, y+1)) && (!wallVector[x][y][1])) {
    adjacent.push_back(resetPosition(x,y+1));
  }
  if ((checkValidity(x+1, y)) && (!wallVector[x][y][0])) {
    adjacent.push_back(resetPosition(x+1,y));
  }
  return adjacent;
}
