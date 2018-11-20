//@author Daniel Yan
//@date 11/10/2018
//Lightweight edge interface
#include <string>
using namespace std;

class Vertex;

class Edge {
friend class Vertex;
friend class Graph;

private:
	//Initialize an edge with 2 vertex pointers and a edge weight
	Edge(Vertex* vertexFrom, Vertex* vertexTo, int edgeWeight);
	//Vertex pointers and edge weight
	Vertex * vFrom;
	Vertex * vTo;
	int weight;
};
