//@author Daniel Yan
//@date 11/10/2018
//Lightweight interface for vertex
#include "edge.h"
#include <string>
#include <vector>
using namespace std;

class Vertex {
	friend class Graph;
	friend class Edge;
public:
	/**
	* @param string - outgoing string label for edge
	* @return Edge* to the outgoing string label
	*/
	Edge* getOutgoingEdge(string l);
	/*
	//Unused Getters and setters
	string getLabel() const;
	vector<Edge *> getEdges() const;
	void setVisited(bool state);
	bool getVisited() const;
	*/
private:
	//private Constructor, as Graph is friend it's accesible
	Vertex(string l);
	//Stores all edges that are going out 
	vector<Edge *> allOutgoingEdges;
	bool visited = false;
	string label = "";
};
