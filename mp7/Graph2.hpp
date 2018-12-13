#include <queue>
#include <algorithm>
#include <string>
#include <list>

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
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  list<string> path;
  queue<string> q;
  bool directed;
  directed = edgeList.front().get().directed();

  for(auto it : edgeList) {
    it.get()["label"] = "unexplored";
  }
  for(auto it : vertexMap) {
    it.second["label"] = "unexplored";
  }
  vertexMap.at(start)["p"] = "";
  vertexMap.at(start)["label"] = "explored";
  q.push(start);

  while(q.empty() == false)
  {
    string current= q.front();
    q.pop();
    list<reference_wrapper<E>> edges = incidentEdges(current);
    for(auto it : edges)
    {
      if(it.get()["label"] == "unexplored")
      {
        Vertex & dest = vertexMap.at(it.get().dest().key());
        Vertex & source = vertexMap.at(it.get().source().key());
        if(!directed){
          if(source["label"] == "unexplored"){
              source["label"] = "visited";
              source["p"] = dest.key();
              q.push(source.key());
              it.get()["label"] = "discovery";
            }
           if(dest["label"] == "unexplored"){
            dest["label"] = "visited";
            dest["p"] = source.key();
            q.push(dest.key());
            it.get()["label"] = "discovery";
          }
          if(dest["label"] == "visited"){
            if(source["label"] == "visited"){
              it.get()["label"] = "cross";
            }
          }
        }
        if(directed) {
          if(dest["label"] == "visited"){
            it.get()["label"] = "cross";
          }
          if(dest["label"] == "unexplored"){
          dest["label"] = "visited";
          dest["p"] = source.key();
          q.push(dest.key());
          it.get()["label"] = "discovery";
        }
      }
    }
  }
}

  string curr = end;
  Vertex v = vertexMap.at(curr);
  path.push_front(curr);

  while(vertexMap.at(curr)["p"] != "") {
    curr = v["p"];
    v = vertexMap.at(curr);
    path.push_front(curr);
  }
  return path;
}
