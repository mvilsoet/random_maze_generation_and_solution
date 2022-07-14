#include "dsets.h"

void DisjointSets::addelements(int num) {
	for (int i = 0; i < num; i++)
		sets_.push_back(-1);
}

int DisjointSets::find(int elem) {
  if (sets_[elem] < 0) 
    return elem;
  else 
    return find(sets_[elem]);
}

void DisjointSets::setunion(int a, int b) {
  int root1 = find(a);
	int root2 = find(b);
  int newSize = sets_[root1] + sets_[root2];

  if (sets_[root1] < sets_[root2]) {
    sets_[root2] = a;
    sets_[root1] = newSize; 
  }
  else {
    sets_[root1] = b;
    sets_[root2] = newSize; 
  }
}

int DisjointSets::size(int elem) {
  int abSize = find(elem);
  return -sets_[abSize];
}
