/**
 * @file BFS.h
 */

#pragma once

#include <iterator>
#include <cmath>
#include <queue>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace std;
using namespace cs225;

/**
 * A breadth-first ImageTraversal.
 * Derived from base class ImageTraversal
 */
class BFS : public ImageTraversal {
public:
  	BFS(const PNG & png, const Point & start, double tolerance);

  	ImageTraversal::Iterator begin();
  	ImageTraversal::Iterator end();
  
  	void add(const Point & point);
  	Point pop();
  	Point peek() const;
  	bool empty() const;
  	bool getVisited(unsigned x, unsigned y);
  	void setVisit(unsigned x, unsigned y);
  	PNG * passPng();
  	double getTolerance();

private:
  	double tolerance_;
  	vector<vector<bool>> * visited;
	PNG png_;
	Point start_;
	queue<Point> traversal;
};
