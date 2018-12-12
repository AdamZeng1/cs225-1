#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include <string>
#include <iostream>

using namespace std;

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  return adjList.at().size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  	V & v = *(new V(key));
  	vertexMap.insert(pair<string, V&>(key, v));
  	adjList.insert(pair<string, list<edgeListIter>>(key, list<edgeListIter>()));
  	return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
	// Remove all edges
	list<E_byRef> incidentEdgeList = incidentEdges(key);
	for (E_byRef ebr: incidentEdgeList) {
		removeEdge(ebr.get().source(), ebr.get().dest());
	}
	// Remove vertex from map
	vertexMap.erase(key);
	// Remove vertex from adjList
	adjList.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  	E & e = *(new E(v1, v2));
  	edgeList.push_front(e);
  	// Add edge to v1's adjacency list
  	adjList.at(v1.key()).push_front(edgeList.begin());
  	// If edge is not directed then add it to v2's adjacency list as well
  	if (!e.directed()) adjList.at(v2.key()).push_front(edgeList.begin());
  	return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const string key1, const string key2) {  
	edgeListIter eli = edgeList.end();
	bool directedFlag = false;
	// Remove edge from v1's adjacency list
	for (typename list<edgeListIter>::iterator it = adjList.at(key1).begin(); it != adjList.at(key1).end(); it++) {
		E e = (*(*it)).get();
		if ( e.source().key() == key1 && e.dest().key() == key2 ) {
			adjList.at(key1).erase(it);
			eli = *it;
			break;
		}
		if (!directedFlag && e.directed()) directedFlag = true;
	}
	// Remove edge from v2's adjacency list if not directed
	if (!directedFlag) {
		for (typename list<edgeListIter>::iterator it = adjList.at(key2).begin(); it != adjList.at(key2).end(); it++) {
			E e = (*(*it)).get();
			if ( e.source().key() == key1 && e.dest().key() == key2 ) {
				adjList.at(key2).erase(it);
				eli = *it;
				break;
			}
		}
	}
	// If edge list iterator was found, delete from edgeList
	if (eli != edgeList.end()) edgeList.erase(eli);
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
	V vertex1 = (*it).get().source();
	V vertex2 = (*it).get().dest();
	bool directedFlag = false;
	for (typename list<edgeListIter>::iterator it = adjList.at(vertex1.key()).begin(); it != adjList.at(vertex1.key()).end(); it++) {
		if ( (*it) == it) {
			adjList.at(vertex1.key()).erase(it);
			break;
		}
		if (!directedFlag && (*it).get().directed()) directedFlag = true;
	}
	if (!directedFlag) {
		for (typename list<edgeListIter>::iterator it = adjList.at(vertex2.key()).begin(); it != adjList.at(vertex2.key()).end(); it++) {
			if ( (*it) == it) {
				adjList.at(vertex2.key()).erase(it);
				break;
			}
		}
	}
	edgeList.erase(it);
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>  
const list<reference_wrapper<E>> Graph<V,E>::incidentEdges(const string key) const {
  	list<reference_wrapper<E>> edges;
  	// Basically return the adjacency list for vertex with given key
  	for (edgeListIter eli: adjList.at(key)) {
  		edges.push_back(*eli);
  	}
  	return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const string key1, const string key2) const {
	// Iterate through adjacency list. Return true if find edge bewteen the vertices
	for (edgeListIter eli: adjList.at(key1)) {
		E cur_edge = (*eli).get();
		if (cur_edge.source().key() == key2 || cur_edge.dest().key() == key2)
		 	return true;
	}
	return false;
}
