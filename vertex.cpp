//@author Daniel Yan
//@date 11/10/2018
//Vertex implementation for vertix.h
#include "vertex.h"

//One liner to initialize vertex with a label and visit state
Vertex::Vertex(const string & sLabel) : label(sLabel), visited(false) {}

//Returns the outgoing edge based on the string
Edge* Vertex::getOutgoingEdge(const string & sLabel) {
	//Ranged based iterator to return an edge based on the string
	for (const auto & e : allOutgoingEdges) {
		if (e->vTo->label == sLabel) {
			return e;
		}
	}
	//If outgoing edge is not found
	return nullptr;
}
