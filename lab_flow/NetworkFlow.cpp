/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

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

  // YOUR CODE HERE
  residual_.insertVertex(source);
  flow_.insertVertex(source);
  Recurse(source, sink);
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
  // YOUR CODE HERE
  Vertex vertex1, vertex2;
  if (path.size() <= 0){
    return 0;
  }
  int pathCapacityValue = 0;
  for(size_t i = 0; i < path.size() - 1; i++){
    vertex1 = path[i];
    vertex2 = path[i + 1];
    if (residual_.vertexExists(vertex1) == true) {
      if (residual_.vertexExists(vertex2)){
      pathCapacityValue = pathCapacityValue + residual_.getEdgeWeight(vertex1, vertex2);
      }
    }
    else {
      return pathCapacityValue;
    }
  }
  return pathCapacityValue;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @@outputs: The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE
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

void NetworkFlow::Recurse(Vertex a, Vertex b) {
  Vertex vertex1;
  vector<Vertex> vertex2 = g_.getAdjacent(a);
  if(a == b){
    return;
  }
  if(vertex2.size() <= 0){
    return;
  }
  for(size_t i = 0; i < vertex2.size(); i++){
    vertex1 = vertex2[i];

    if(residual_.vertexExists(vertex1) == false){
      residual_.insertVertex(vertex1);
      residual_.insertEdge(a, vertex1);
      residual_.setEdgeWeight(a, vertex1, g_.getEdgeWeight(a, vertex1));
      residual_.insertEdge(vertex1, a);
      residual_.setEdgeWeight(vertex1, a, 0);
    }
    else {
      residual_.insertEdge(a, vertex1);
      residual_.setEdgeWeight(a, vertex1, g_.getEdgeWeight(a, vertex1));
      residual_.insertEdge(vertex1, a);
      residual_.setEdgeWeight(vertex1, a, 0);
    }

    if(flow_.vertexExists(vertex1) == false){
      flow_.insertVertex(vertex1);
      flow_.insertEdge(a, vertex1);
      flow_.setEdgeWeight(a, vertex1, 0);
    }
    else {
      flow_.insertEdge(a, vertex1);
      flow_.setEdgeWeight(a, vertex1, 0);
    }

    Recurse(vertex1, b);
  }
}
