#pragma once

#include <vector>

class DisjointSets {
public:
	void addelements(int num);  // add num amount of elements to _elems array
	int find(int elem);  // Find root index of ds that elem is part of
	void setunion(int a, int b);  // Combine two sets into one
	int size(int elem);  // Find height of root index

private:
	std::vector<int> _elems; 
};