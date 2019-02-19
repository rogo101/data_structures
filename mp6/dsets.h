/* Your code here! */

#pragma once

#include <vector>
using namespace std;

class DisjointSets
{
	public:
		DisjointSets();
		DisjointSets(int num);
		void addelements(int num);
		int find(int elem);
		void setunion(int a, int b);
		int size(int elem);
	private:
		vector<int> items;
};
