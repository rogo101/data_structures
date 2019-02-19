/* Your code here! */

#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"

#include <cstdlib>
#include <queue>
#include <vector>

using namespace std;
using namespace cs225;

class SquareMaze
{
	public:
    vector<int> solveMaze ();
		SquareMaze();
		bool canTravel (int x, int y, int angle) const;
    PNG * drawMazeWithSolution ();
    PNG * drawMaze () const;
    void makeMaze (int width, int height);
		void setWall (int x, int y, int angle, bool true_Holder);
	private:
		int width_, height_;
    pair<int,int> changePosition(int position) const;
		bool checkValidity (int x, int y) const;
    vector<vector<vector<bool>>> wallVector;
		int resetPosition(int x, int y) const;
		vector<int> smallestDistance();
		int largestDistance(vector<int>& dist);
    vector<int> nextDoor(int index);
		int thetaSolver(int top, int index);

};
