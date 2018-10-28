#include <iterator>
#include <cmath>

#include <queue>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "BFS.h"

using namespace std;
using namespace cs225;

/**
 * Initializes a breadth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * @param png The image this BFS is going to traverse
 * @param start The start point of this BFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this BFS
 */
BFS::BFS(const PNG & png, const Point & start, double tolerance) {  
    tolerance_ = tolerance; 
    png_ = png; 
    start_ = start;
    traversal.push(start);
    //visited = vector<vector<bool>>;
    visited.resize(png_.width());
    for (unsigned i = 0; i < visited.size(); i++) {
        visited[i].resize(png_.height());
        for (unsigned j = 0; j < visited[i].size(); j++) {
            visited[i][j] = false;
        }
    }
    visited[start.x][start.y] = true;
}

BFS::~BFS() {
    
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator BFS::begin() {
    BFS * bfs = new BFS(png_, start_, tolerance_);
    return ImageTraversal::Iterator(*bfs, start_);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator BFS::end() {
    return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void BFS::add(const Point & point) {
    traversal.push(point);
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point BFS::pop() {
    Point temp = traversal.front();
    traversal.pop();
    return temp;
}

/**
 * Returns the current Point in the traversal.
 */
Point BFS::peek() const {
    return traversal.front();
}

/**
 * Returns true if the traversal is empty.
 */
bool BFS::empty() const {
    return traversal.empty();
}

bool BFS::getVisited(unsigned x, unsigned y) {
    return visited[x][y];
}
void BFS::setVisit(unsigned x, unsigned y) {
    visited[x][y] = true;
}
PNG * BFS::passPng() {
    return &png_;
}
double BFS::getTolerance() {
    return tolerance_;
}
