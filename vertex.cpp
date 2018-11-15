//@author Daniel Yan
//@date 11/10/2018
//Vertex implementation for vertix.h
#include "vertex.h"

//One liner to initialize vertex with a label and visit state
Vertex::Vertex(string l) : label(l), visited(false) {}


//Returns the outgoing edge based on the string
Edge* Vertex::getOutgoingEdge(string l) {
	//Ranged based iterator to return an edge based on the string
	for (const auto & e : allOutgoingEdges) {
		if (e->vTo->label == l) {
			return e;
		}
	}
	//If outgoing edge is not found
	return nullptr;
}
		

//Unused Getters and setters 
/*
vector<Edge *> Vertex::getEdges() const {
	return allOutgoingEdges;
}
string Vertex::getLabel() const {
	return label;
}

void Vertex::setVisited(bool state) {
	visited = state;
}
bool Vertex::getVisited() const {
	return visited;
}
*/
