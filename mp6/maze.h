#pragma once

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"
#include <vector>
#include <utility>

using namespace std;
using namespace cs225;

class SquareMaze {
public:
	SquareMaze();
	~SquareMaze();
	void makeMaze(int width, int height);
	bool canTravel(int x, int y, int dir) const;
	void setWall(int x, int y, int dir, bool exists);
	std::vector<int> solveMaze();
	void solveMazeHelper(vector<vector<pair<int, int>>> * solution, pair<unsigned, unsigned> start);
	PNG * drawMaze() const;
	PNG * drawMazeWithSolution();

private:
	class Node {
	public:
		Node(bool down, bool right) {
			_down = down;
			_right = right;
		}
		bool _down;
		bool _right;
	};
	vector<Node> * _maze;
	DisjointSets * _disjointSets;
	int _width;
	int _height;
};