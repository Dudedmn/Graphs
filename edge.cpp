//@author Daniel Yan
//@date 11/10/2018
//Edge implementation class for edge.h
#include "edge.h"
using namespace std;

//Constructor to initialize an edge
Edge::Edge(Vertex* v1, Vertex* v2, int edgeWeight) : vFrom(v1), vTo(v2), weight(edgeWeight){}


/*
//Unusued Getters and Setters
int Edge::getWeight() const { 
	return weight; 
}

Vertex* Edge::getVertexTo() const {
	return vTo; 
}
Vertex* Edge::getVertexFrom() const { 
	return vFrom; 
}

void Edge::setWeight(int w) { 
	weight = w;
}

void Edge::setVertexFrom(Vertex * v) {
	vFrom = v;
}

void Edge::setVertexTo(Vertex * v) {
	vTo = v; 
}
*/


