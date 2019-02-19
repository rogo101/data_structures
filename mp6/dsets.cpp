/* Your code here! */

#include "dsets.h"
//Constructor for Disjoint sets object.
DisjointSets::DisjointSets() {
  items = vector<int>(1);
	for (unsigned i = 0; i < items.size(); i++) {
    items[i] = -1;
  }
}
//Constructor with parameter size
DisjointSets::DisjointSets(int num) {
	items = vector<int>(num);
	for (unsigned i = 0; i < items.size(); i++) {
    items[i] = -1;
  }
}
//function to add elements to vector
void DisjointSets::addelements(int num) {
	for (int i=0; i<num; i++)
	{
		items.push_back(-1);
	}
}
//function to find an element
int DisjointSets::find(int elem) {
  int root;
  if (items[elem] >= 0) {
    root = find(items[elem]);
		items[elem] = root;
		return root;
  }
	return elem;
}
//function to setunion between two Disjoint sets.
void DisjointSets::setunion(int a, int b) {
	int first = items[find(a)], second = items[find(b)], sum;
  first = first * -1;
  second = second * -1;
	sum = first + second;
	if (first <= second)
	{
    items[find(a)] = find(b);
    items[find(b)] = sum * -1;
	}
	if (first > second)
	{
    items[find(b)] = find(a);
		items[find(a)] = sum * -1;
	}
}

int DisjointSets::size(int elem) {
	return items[find(elem)] * -1;
}
