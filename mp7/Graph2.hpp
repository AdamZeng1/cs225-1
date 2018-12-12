#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include <iostream>

using namespace std;

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 * 
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 * 
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
list<string> Graph<V,E>::shortestPath(const string start, const string end) {
	// Used to keep track of every vertex's predecessor, so that a path list can be made
	unordered_map<string, string> predecessor;
	// Used to keep track of distances from start 
	unordered_map<string, int> distances;

	// For every pair in the vertexmap, initialize pair in predecessor and distances
	for (pair<string, V &> elem: vertexMap) {
		predecessor.insert(pair<string, string>(elem.first, ""));
		distances.insert(pair<string, int>(elem.first, INT_MAX));
	}

	// Set up a queue for BFS with only start vertex in it
	queue<string> q;
	q.push(start);
	distances[start] = 0;

	// While the queue isn't empty, check if there is new shorter path to any given node
	// If so, push it to queue and update predecessor and distance
	while (!q.empty()) {
		string cur = q.front();
		q.pop();
		for (E_byRef ebr: incidentEdges(cur)) {
			string cur_next = ebr.get().dest().key() == cur ? ebr.get().source().key() : ebr.get().dest().key();
			if (distances[cur_next] > (distances[cur] + 1)) {
				q.push(cur_next);
				predecessor[cur_next] = cur;
				distances[cur_next] = distances[cur] + 1;
			}
		}
	}
  	list<string> path;
  	string cur = end;
  	// Convert predecessor map to list
  	while (cur != "") {
  		path.push_front(cur);
  		cur = predecessor[cur];
  	}
  	return path;
}

