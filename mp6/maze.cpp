#include "maze.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <queue>
#include <utility>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze() {
	_maze = new vector<Node>;
	_disjointSets = new DisjointSets(); 
	_width = 0;
	_height = 0;
}

SquareMaze::~SquareMaze() {
	delete _maze;
	_maze = NULL;
	delete _disjointSets;
	_disjointSets = NULL;
}

// 1 is down, 0 is right
void SquareMaze::makeMaze(int width, int height) {
	// Set up made with full walls
	_width = width;
	_height = height;
	_disjointSets->addelements(width * height);
	for (int box_count = 0; box_count < width * height; box_count++)
		_maze->push_back(Node(true, true));
	// Randomly remove walls such that no cycles exist
	for (int i = 0; i < width * height - 1; i++) {
		vector<int> possible_directions;
		if ( ((i + 1) % _width != 0) &&
			 (_disjointSets->find(i) != _disjointSets->find(i+1)) ) {
			possible_directions.push_back(0);
		}
		if ( !(i >= (_width * (_height - 1))) &&
			 (_disjointSets->find(i) != _disjointSets->find(i+_width)) ) {
			possible_directions.push_back(1);
		}
		if ( !(i % _width == 0) &&
			 (_disjointSets->find(i) != _disjointSets->find(i-1)) ) {
			possible_directions.push_back(2);
		}
		if ( !(i < _width) &&
			 (_disjointSets->find(i) != _disjointSets->find(i-_width)) ) {
			possible_directions.push_back(3);
		}

		int direction = possible_directions[rand() % possible_directions.size()];

		// If we decided to commit rightwards and we can commit rightwards
		if (direction == 0) {
			_disjointSets->setunion(i, i+1);
			(*_maze)[i]._right = false;  // would use setwall but it is stupid lol
		}
		// If we decided to commit downwards and we can commit downwards
		else if (direction == 1) {
			_disjointSets->setunion(i, i+_width);
			(*_maze)[i]._down = false;  // would use setwall but it is stupid lol
		}
		// If we decided to commit leftwards
		else if (direction == 2) {
			_disjointSets->setunion(i, i-1);
			(*_maze)[i-1]._right = false;  // would use setwall but it is stupid lol
		}
		// If we decided to commit upwards
		else if (direction == 3) {
			_disjointSets->setunion(i, i-_width);
			(*_maze)[i-_width]._down = false;  // would use setwall but it is stupid lol
		}
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
	if (dir == 0) {
		if (x >= _width - 1) return false;
		return !(*_maze)[x + y * _width]._right;
	}
	else if (dir == 1) {
		if (y >= _height - 1) return false;
		return !(*_maze)[x + y * _width]._down;
	}
	else if (dir == 2) {
		if (x <= 0) return false;
		return !(*_maze)[x  - 1 + y * _width]._right;
	}
	else if (dir == 3) {
		if (y <= 0) return false;
		return !(*_maze)[x + (y - 1) * _width]._down;
	}
	else return false;
}

// Redundant, I would say in this case 1d arrays are better
void SquareMaze::setWall(int x, int y, int dir, bool exists) {
	if (dir) 
		(*_maze)[_width * y + x]._down = exists;
	else 
		(*_maze)[_width * y + x]._right = exists;
}

vector<int> SquareMaze::solveMaze() {
	vector<vector<pair<int, int>>> solution;  // distance, parent direction
	// make all distances -1 to signify they havent been visited yet
	for (int x = 0; x < _width; x++) {
		solution.push_back(vector<pair<int, int>>());
		for (int y = 0; y < _height; y++) {
			solution.back().push_back(pair<int, int>(-1,-1));
		}
	}
	solveMazeHelper(&solution, pair<int, int>(0,0));
	pair<int, int> cur_pair(0, _height- 1);
	int cur_largest_distance = solution[0][_height-1].first;
	for (int x = 0; x < _width; x++) {
		if (solution[x][_height-1].first > cur_largest_distance) {
			cur_largest_distance = solution[x][_height-1].first;
			cur_pair = pair<int, int>(x, _height-1);
		}
	}
	vector<int> answer;
	while (cur_pair != pair<int, int>(0,0)) {
		int x = cur_pair.first;
		int y = cur_pair.second;
		int parent_dir = solution[x][y].second;
		int dir = -1;
		dir = parent_dir == 0 ? 2 : dir;
		dir = parent_dir == 1 ? 3 : dir;
		dir = parent_dir == 2 ? 0 : dir;
		dir = parent_dir == 3 ? 1 : dir;
		answer.push_back(dir);
		cur_pair = (parent_dir == 0) ? pair<int, int>(x+1,y) : cur_pair;
		cur_pair = (parent_dir == 1) ? pair<int, int>(x,y+1) : cur_pair;
		cur_pair = (parent_dir == 2) ? pair<int, int>(x-1,y) : cur_pair;
		cur_pair = (parent_dir == 3) ? pair<int, int>(x,y-1) : cur_pair;
	}
	reverse(answer.begin(), answer.end());
	return answer;
}

void SquareMaze::solveMazeHelper(vector<vector<pair<int, int>>> * solution, pair<unsigned, unsigned> start) {
	
	int x = start.first;
	int y = start.second;
	if ((!canTravel(x, y, 0) || (*solution)[x + 1][y].second == 0) && 
		(!canTravel(x, y, 1) || (*solution)[x][y + 1].second == 1) && 
		(!canTravel(x, y, 2) || (*solution)[x - 1][y].second == 2) && 
		(!canTravel(x, y, 3) || (*solution)[x][y - 1].second == 3) ) {
		return;
	}
	pair<int, int> cur_pair = (*solution)[x][y];
	if (canTravel(x, y, 0) && (*solution)[x+1][y].first == -1) {
		(*solution)[x+1][y] = pair<int, int>(cur_pair.first + 1, 2);
		solveMazeHelper(solution, pair<int, int>(x+1,y));
	}
	if (canTravel(x, y, 1) && (*solution)[x][y+1].first == -1) {
		(*solution)[x][y+1] = pair<int, int>(cur_pair.first + 1, 3);
		solveMazeHelper(solution, pair<int, int>(x,y+1));
	}
	if (canTravel(x, y, 2) && (*solution)[x-1][y].first == -1) {
		(*solution)[x-1][y] = pair<int, int>(cur_pair.first + 1, 0);
		solveMazeHelper(solution, pair<int, int>(x-1,y));
	}
	if (canTravel(x, y, 3) && (*solution)[x][y-1].first == -1) {
		(*solution)[x][y-1] = pair<int, int>(cur_pair.first + 1, 1);
		solveMazeHelper(solution, pair<int, int>(x,y-1));
	}
}

PNG * SquareMaze::drawMaze() const {
	PNG * result = new PNG(_width * 10 + 1, _height * 10 + 1);
	for (int x = 0; x < _width; x++) {
		for (int y = 0; y < _height; y++) {
			if (y == 0) {
				for (unsigned p = 0; p < 10; p++) {
					if ((x*10+p < 1) || (x*10+p > 9)) {
						HSLAPixel & cur_pixel = result->getPixel(x*10+p, 0);
						cur_pixel.l = 0;
					}
				}
			}
			if (x == 0) {
				for (unsigned p = 0; p < 10; p++) {
					HSLAPixel & cur_pixel = result->getPixel(0, y*10+p);
					cur_pixel.l = 0;
				}
			}
			if (!canTravel(x, y, 0)) {
				for (unsigned p = 0; p <= 10; p++) {
					HSLAPixel & cur_pixel = result->getPixel((x+1)*10, y*10+p);
					cur_pixel.l = 0;
				}
			}
			if (!canTravel(x, y, 1)) {
				for (unsigned p = 0; p <= 10; p++) {
					HSLAPixel & cur_pixel = result->getPixel(x*10+p, (y+1)*10);
					cur_pixel.l = 0;
				}
			}
		}
	}
	return result;
}

PNG * SquareMaze::drawMazeWithSolution() {
	PNG * maze = drawMaze();
	vector<int> solution = solveMaze();
	pair<int, int> cur_point(5, 5);
	for (auto i: solution) {
		if (i == 0) {
			for (int p = 0; p < 10; p++) {
				HSLAPixel & cur_pixel = maze->getPixel(cur_point.first, cur_point.second);
				cur_pixel.h = 0;
				cur_pixel.s = 1.0;
				cur_pixel.l = 0.5;
				cur_point.first++;
			}
		}
		else if (i == 1) {
			for (int p = 0; p < 10; p++) {
				HSLAPixel & cur_pixel = maze->getPixel(cur_point.first, cur_point.second);
				cur_pixel.h = 0;
				cur_pixel.s = 1.0;
				cur_pixel.l = 0.5;
				cur_point.second++;
			}
		}
		else if (i == 2) {
			for (int p = 0; p < 10; p++) {
				HSLAPixel & cur_pixel = maze->getPixel(cur_point.first, cur_point.second);
				cur_pixel.h = 0;
				cur_pixel.s = 1.0;
				cur_pixel.l = 0.5;
				cur_point.first--;
			}
		}
		else if (i == 3) {
			for (int p = 0; p < 10; p++) {
				HSLAPixel & cur_pixel = maze->getPixel(cur_point.first, cur_point.second);
				cur_pixel.h = 0;
				cur_pixel.s = 1.0;
				cur_pixel.l = 0.5;
				cur_point.second--;
			}
		}
	}
	HSLAPixel & cur_pixel = maze->getPixel(cur_point.first, cur_point.second);
	cur_pixel.h = 0;
	cur_pixel.s = 1.0;
	cur_pixel.l = 0.5;

	cur_point.first -= 4;
	cur_point.second += 5;
	for (int x = cur_point.first; x < cur_point.first + 9; x++) {
		HSLAPixel & cur_pixel = maze->getPixel(x, _height * 10);
		cur_pixel.l = 1.0;
	}
	return maze;
}