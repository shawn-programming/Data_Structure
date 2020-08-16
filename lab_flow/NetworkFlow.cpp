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
  residual_ = g_;
  flow_ = g_;

  // set all edge's weight 0
  for(Edge e : g_.getEdges()){
    flow_.setEdgeWeight(e.source, e.dest, 0);
    // cout << e.dest << endl;
  }

  // set all
  for(Edge e : g_.getEdges()){
    if(!(residual_.edgeExists(e.dest, e.source))){
      residual_.insertEdge(e.dest, e.source);
      residual_.setEdgeLabel(e.dest, e.source, "dotted");
      residual_.setEdgeWeight(e.dest, e.source, 0);
      // cout << e.dest << endl;
    }
  }

  // cout << "here" << endl;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
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
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
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
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const {
  // YOUR CODE HERE
  if(path.size() == 0) return 0;
  int min = INT_MAX;

  for(unsigned i=0; i<path.size()-1; i++){
    int weight = residual_.getEdgeWeight(path[i], path[i+1]);

    if(weight == 0) return 0;

    if(weight < min){
      min = weight;
    }
  }
  return min;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow() {
  // YOUR CODE HERE

  while(1){
    vector<Vertex> path;
    findAugmentingPath(source_, sink_, path);
    // cout << " path " << path.size() << endl;
    
    if(path.size() <= 1) break;
    
    // cout << " v1 " << path[0] << " v2 " << path[1] << endl;
    int min_val = pathCapacity(path);

    for(unsigned i=0; i<path.size()-1; i++){
      int weight = residual_.getEdgeWeight(path[i], path[i+1]);
      residual_.setEdgeWeight(path[i], path[i+1], weight-min_val);
      residual_.setEdgeWeight(path[i+1], path[i], residual_.getEdgeWeight(path[i+1], path[i]) + min_val);

      
      if(residual_.getEdgeLabel(path[i], path[i+1]) == "dotted"){
        weight = flow_.getEdgeWeight(path[i+1], path[i]);
        flow_.setEdgeWeight(path[i+1], path[i], weight-min_val);
      }
      else{
        weight = flow_.getEdgeWeight(path[i], path[i+1]);
        flow_.setEdgeWeight(path[i], path[i+1], weight+min_val);
      }
    }
  }

  maxFlow_ = 0;

  vector<Vertex> vec = flow_.getAdjacent(source_);
  // cout << "vec:" << vec.size();
  for(Vertex v : vec){
    // cout  << "weight: " << flow_.getEdgeWeight(source_, v) << endl;
    maxFlow_ += flow_.getEdgeWeight(source_, v);
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
