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
  // TODO: Part 2
  unsigned size = vertexMap.size();
  return size;
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  string keys = v.key();
  unsigned size = adjList[keys].size();
  return size;
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  list<edgeListIter> graphIterator;
  // std::pair<string, V &> hashPair(key, v);
  // vertexMap.insert(hashPair);
  pair<string, V &> pair1 (key, v);
  pair<string, list<edgeListIter>> pair2 (key, graphIterator);
  adjList.insert(pair2);
  vertexMap.insert(pair1);
  // //create new pair and insert into adjacent List
  // std::list<edgeListIter> it;
  // std::pair<string, std::list<edgeListIter>> hashPair2(key, it);
  // adjList.insert(hashPair2);
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  vertexMap.eraseKey(); //utilizes earseKey function
  adjList.eraseKey();
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  //
  // string key1 = v1.key();
  // string key2 = v2.key();
  // edgeListIter it = edgeList.begin();
  //
  edgeList.push_front(e);
  edgeListIter graphIterator = edgeList.begin();
  string v1Key = v1.key();
  string v2Key = v2.key();

  adjList[v1Key].push_front(graphIterator);
  adjList[v2Key].push_front(graphIterator);
  //
  // edgeList.push_front(e);
  // adjList[key1].push_front(it);
  // adjList[key2].push_front(it);
  ///
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
  return;
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  return;
}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  list<reference_wrapper<E>> returnEdge;
  for(reference_wrapper<E> curr : edgeList) {
    if(curr.get().source().key() == key) {
      returnEdge.push_back(curr);
    }
    if (curr.get().dest().key() == key) {
      returnEdge.push_back(curr);
    }
  }
  return returnEdge;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  list<edgeListIter> prev = adjList.at(key1),  curr = adjList.at(key2),  flag;

  flag = (prev.size() > curr.size()) ? curr : prev;
  for (edgeListIter iterator3 : flag) {
    if(((Edge&)*iterator3).source().key() == key1) {
      if (((Edge&)*iterator3).dest().key() == key2) {
        return true;
      }
    }
  }
  return false;
}
