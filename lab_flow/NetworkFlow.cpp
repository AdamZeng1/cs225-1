/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>
#include <climits>
#include <iostream>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {
    maxFlow_ = 0;
    flow_ = g_;
    residual_ = g_;
    // set all edge weights in flow to 0
    for (Vertex cur1: flow_.getVertices()) {
      for (Vertex cur2: flow_.getAdjacent(cur1)) {
        flow_.setEdgeWeight(cur1, cur2, 0);
        flow_.setEdgeLabel(cur1, cur2, cur1+cur2);
      }
    }
    // add back edges to residual and set their weights to 0
    for (Vertex cur1: g_.getVertices()) {
      for (Vertex cur2: g_.getAdjacent(cur1)) {
        residual_.insertEdge(cur2, cur1);
        residual_.setEdgeWeight(cur2, cur1, 0);
        residual_.setEdgeLabel(cur1, cur2, cur1+cur2);
        residual_.setEdgeLabel(cur2, cur1, cur2+cur1);
      }
    }
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   * @@params: visited -- A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, 
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @@params: source -- The starting (current) vertex
   * @@params: sink   -- The destination vertex
   * @@params: path   -- The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @@params: path   -- The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  if (path.size() <= 1) return 0;
  int smallest_value = residual_.getEdgeWeight(path[0], path[1]);
  for (unsigned i = 1; i < path.size() - 1; i++) {
    int curedge = residual_.getEdgeWeight(path[i], path[i+1]);
    if (curedge < smallest_value) 
      smallest_value = curedge;
  }
  return smallest_value;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  vector<Vertex> path;
  // While a path is found with any capacity
  while (findAugmentingPath(source_, sink_, path)) {
    // Find capacity using function
    int cap = pathCapacity(path);
    // Add to max flow
    maxFlow_ += cap;
    // Change edge weights
    for (unsigned i = 0; i < path.size() - 1; i++) {
      if (flow_.edgeExists(path[i], path[i+1]))
        flow_.setEdgeWeight(path[i], path[i+1], flow_.getEdgeWeight(path[i], path[i+1]) + cap);
      else 
        flow_.setEdgeWeight(path[i+1], path[i], flow_.getEdgeWeight(path[i+1], path[i]) - cap);
      residual_.setEdgeWeight(path[i], path[i+1], residual_.getEdgeWeight(path[i], path[i+1]) - cap);
      residual_.setEdgeWeight(path[i+1], path[i], residual_.getEdgeWeight(path[i+1], path[i]) + cap);
    }
  }
  return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}
