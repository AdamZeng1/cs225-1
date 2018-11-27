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
	void makeMaze(int width, int height);  // Construct maze w/ no cycles :)
	bool canTravel(int x, int y, int dir) const;  // Checks if there is wall in dir
	void setWall(int x, int y, int dir, bool exists);  // Sets a wall to there or not
	vector<int> solveMaze();  // Solves maze, returning vector of directions
	void solveMazeHelper(vector<vector<pair<int, int>>> * solution, pair<unsigned, unsigned> start);
	PNG * drawMaze() const;  // Makes a png of maze
	PNG * drawMazeWithSolution();  // Makes png of maze with red line solution 
	// For part 3 creative component
	PNG * drawMazeCreative();
	void drawMazeHelperCreative(vector<vector<pair<int, int>>> * solution, pair<unsigned, unsigned> start, PNG * maze, double cur_hue);


private:
	// Data structures
	// Maze is represented as an array of nodes
	class Node {
	public:
		Node(bool down, bool right) {
			_down = down;
			_right = right;
		}
		// Each node only needs to store 2 bits
		bool _down;
		bool _right;
	};
	// Maze representation, 1d vector represents 2d maze
	vector<Node> * _maze;
	// Another maze representation, but keeps track of connectivity
	DisjointSets * _disjointSets;
	int _width;
	int _height;
};