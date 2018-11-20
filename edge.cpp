//@author Daniel Yan
//@date 11/10/2018
//Edge implementation class for edge.h
#include "edge.h"

//Constructor to initialize an edge
Edge::Edge(Vertex* v1, Vertex* v2, int edgeWeight) 
	: vFrom(v1), vTo(v2), weight(edgeWeight){}
