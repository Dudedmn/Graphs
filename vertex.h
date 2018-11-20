//@author Daniel Yan
//@date 11/10/2018
//Lightweight interface for vertex
#include "edge.h"
#include <string>
#include <vector>

class Vertex {
	friend class Graph;
	friend class Edge;
public:
	/**
	* @param string - outgoing string label for edge
	* @return Edge* to the outgoing string label
	*/
	Edge* getOutgoingEdge(const std::string &);
private:
	//private Constructor, as Graph is friend it's accesible
	Vertex(const std::string &);
	//Stores all edges that are going out 
	std::vector<Edge *> allOutgoingEdges;
	bool visited;
	std::string label;
};
