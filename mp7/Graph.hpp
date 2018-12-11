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
	// Remove edges going to vertex
	list<E_byRef> incidentEdges = incidentEdges(key);
	for (E_byRef e: incidentEdges) {
		if (e.get().dest() == key) {
			for (typename list<edgeListIter>::iterator it = adjList.at(key).begin(); it != adjList.at(key).end(); it++) {
				if ( (*it).get() == e ) {
					adjList.at(e.get().source()).erase(it);
					edgeList.erase(*it);
				}
			}
		}
	}
	// Remove edges coming from vertex
	for (edgeListIter eli: adjList.at(key)) {
		edgeList.erase(eli);
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
  adjList.at(v1.key()).push_front(edgeList.begin());
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {  
  // TODO: Part 2
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>  
const list<reference_wrapper<E>> Graph<V,E>::incidentEdges(const string key) const {
  	list<reference_wrapper<E>> edges;
  	for (E_byRef e: edgeList) {
  		if (e.get().source().key() == key || e.get().dest().key() == key) {
  			edges.push_back(e);
  		}
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
	for (edgeListIter eli: adjList.at(key1)) {
		if ((*eli).get().dest().key() == key2) return true;
	}
	return false;
}
