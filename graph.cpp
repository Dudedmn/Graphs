//@author Daniel Yan
//@date 11/10/2018
//Graph implementation for graph.h
#include "graph.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <limits>
using namespace std;

Graph::Graph() {

}

/** destructor, delete all vertices and edges */
Graph::~Graph() {
	//Iterate through all strings and vertices in a map
	// then iterate through all edges in the vertices
	for (auto const & sV : vertices) {
		for (auto const & e : sV.second->allOutgoingEdges) {
			delete e;
		}
		//Delete the vertex
		delete sV.second;	
	}
	vertices.clear();
}

/**
* @return total number of vertices
* */
int Graph::NumberOfVertices() const {
	//Map keeps count of vertices
	return vertices.size();
}

/**
* @return total number of edges
* */
int Graph::NumberOfEdges() const {
	return numberOfEdges;
}

/**
* @param label
* @return number of edges from given vertex, -1 if vertex not found
* */
int Graph::NumberOfEdges(const std::string &label) const {
	if (findVertex(label) != nullptr) {
		return findVertex(label)->allOutgoingEdges.size();
	}
	//Vertex wasn't initalized or doesn't exist
	else {
		return -1;
	}
}

/**
* Add a vertex to the graph, no duplicates allowed
* @param label
* @return true if vertex added, false if it already is in the graph
* */
bool Graph::AddVertex(const std::string &label) {
	//Check if a vertex already exists with the label
	if (HasVertex(label)) {
		return false;
	}

	else {
	//Create a new Vertex and insert it into the map
		vertices.insert(make_pair(label, createVertex(label)));
		return true;
	}
}
/**
* @param label
* @return true if vertex is in the graph, false if not
* */
bool Graph::HasVertex(const std::string &label) const {
	for (auto const & sV : vertices) {
		//checking labels in map of vertices
		if (sV.first == label || (sV.second)->label == label) {
			return true;
		}
	}
	return false;
}

/*
* sorting function for vector of edges, uses a lambda function
* and iterators to determine what to sort
* @param string for origin Vertex
* @return nothing
*/
void Graph::sortEdges(std::string &label) {
	//Check if vertex exists
	if (HasVertex(label)) {
		sort(findVertex(label)->allOutgoingEdges.begin(), findVertex(label)->allOutgoingEdges.end(),
			//Lambda function which compares the toVertex string labels
			[](const Edge* edge1, const Edge* edge2) -> bool {
			return (edge2->vTo->label > edge1->vTo->label);
		});
	}
}


/**
* Get edges of the vertex in a readable format
* such as b(10),c(20),d(40)
* @param label
* @return string representing edges and weights, "" if vertex not found
* */
std::string Graph::GetEdges(const std::string &label) const {
	string edgeRead = "";
	int edgeWeight = 0;
	if (HasVertex(label)) {
		sort(findVertex(label)->allOutgoingEdges.begin(), findVertex(label)->allOutgoingEdges.end(),
			//Lambda function which compares the toVertex string labels
			[](const Edge* edge1, const Edge* edge2) -> bool{
			return (edge2->vTo->label > edge1->vTo->label);
		});
		//Not using a for each to account for the missing comma at the end
		for (auto e = findVertex(label)->allOutgoingEdges.begin(); e != findVertex(label)->allOutgoingEdges.end(); ++e) {
			if (e == findVertex(label)->allOutgoingEdges.end() - 1) {
				edgeWeight = (*e)->weight;
				edgeRead += (*e)->vTo->label + "(" + to_string(edgeWeight) + ")";
			}
			else {
				edgeWeight = (*e)->weight;
				edgeRead += (*e)->vTo->label + "(" + to_string(edgeWeight) + "),";
			}
		}
		return edgeRead;
	}

	else {
		return "";
	}
}

/**
* Add a new edge between start and end vertex
* If the vertices do not exist, create them
* A vertex cannot connect to itself
* or have multiple edges to the same vertex
* @param fromLabel
* @param toLabel
* @param edgeWeight optional, defaults to 0
* @return true if successfully connected
* */
bool Graph::Connect(const std::string &fromLabel,
	const std::string &toLabel, int edgeWeight = 0) {
	
	//Checking for self assignment and edgeweight
	if (fromLabel == toLabel || edgeWeight < 0) {
		return false;
	}
	//If vertices don't exist, add them
	if (!HasVertex(fromLabel)) {
		AddVertex(fromLabel);
	}
	if (!HasVertex(toLabel)) {
		AddVertex(toLabel);
	}
	
	//Checking for duplicate edges
	for (auto const & v : findVertex(fromLabel)->allOutgoingEdges) {
		if (v->vFrom->label == fromLabel && v->vTo->label == toLabel)
			return false;
	}

	//Making an new edge, and pushing the edge to the vertices
	Edge* newEdge = new Edge(findVertex(fromLabel), findVertex(toLabel), edgeWeight); 
	//Increment edge counter
	numberOfEdges++;
	//Pushing the outgoing edge to the fromVertex
	findVertex(fromLabel)->allOutgoingEdges.push_back(newEdge);
	return true;
}

/**
* Remove edge from graph
* @param fromLabel starting vertex label
* @param edge ending vertex label
* @return true if edge successfully deleted
* */
bool Graph::Disconnect(const std::string &fromLabel, const std::string &toLabel) {
	//If either vertex doesn't exist, then return false
	if (!HasVertex(fromLabel) || !HasVertex(toLabel)) {
		return false;
	}

	else {
		//Using range based for loop with pointers to determine which edge to erase
		for (auto e = findVertex(fromLabel)->allOutgoingEdges.begin(); e != findVertex(fromLabel)->allOutgoingEdges.end(); ++e) {
			if ((*e)->vTo->label == toLabel) {
				delete *e;
				//Erase the edge from the label, decrementing size
				findVertex(fromLabel)->allOutgoingEdges.erase(e);
				//Decrement edge count
				numberOfEdges--;
				return true;
			}
		}
		return false;
	}

}

/**
* Read edges from file
* first line of file is an integer, indicating number of edges
* each line represents an edge in the form of "string string int"
* vertex labels cannot contain spaces
* @param filename
* @return true if file successfully read
* */
bool Graph::ReadFile(const std::string &filename) {
	int edgeWeight;
	string line, vertexFrom, vertexTo;
	ifstream file(filename);
	if (file.is_open()) {
		//First line is number of edges
		//As we know the pre-format for the file where it's vertex 1, vertex 2, edge weight
		//we just loop to make the first 3 string elements correspond
		while (getline(file, line)) {
			file >> vertexFrom >> vertexTo >> edgeWeight;
			//Connect adds the number of edges
			Connect(vertexFrom, vertexTo, edgeWeight);
		}
		file.close();
		return true;
	}
	//Unable to open the file
	else {
		cout << "Unable to open file" << endl;
		return false;
	}

}

/**
* depth-first traversal starting from given startLabel
* @param startLabel starting vertex label
* @param visit function to be called on each vertex label
* */
void Graph::DFS(const std::string &startLabel, void visit(const std::string &)) {
	//Make sure no prior DFS affects new dfs by marking all vertices unvisited
	unvisitVertices();
	//Checks if vertex exists first
	if (HasVertex(startLabel)) {
		//Runs dfs if so
		dfsHelper(findVertex(startLabel), visit);
	}
}


/** breadth-first traversal starting from startLabel
call the function visit on each vertex label */
/**
* breadth-first traversal starting from given startLabel
* @param starting vertex label
* @param function to be called on each vertex label
* */
void Graph::BFS(const std::string &startLabel, void visit(const std::string &)) {
	//Make sure no prior BFS affects new bfs by marking all vertices unvisited
	unvisitVertices();
	//Checks if vertex exists first
	if (HasVertex(startLabel)) {
		//Runs bfs if so
		bfsHelper(findVertex(startLabel), visit);
	}
}

/**
* dijkstra's algorithm to find shortest distance to all other vertices
* and the path to all other vertices
* Path cost is recorded in the map passed in, e.g. weight["F"] = 10
* How to get to vertex is recorded in map passed in, previous["F" = "C"
* @param starting vertex label
* @param map of <string, int> to record shortest path to vertex
* @param map of <string, string> to record previous node in path to vertex
* */
void Graph::Dijkstra(const std::string &startLabel,
	std::map<std::string, int> &weights, std::map<std::string, std::string> &previous) {
	//Maximum distance
	int INF = std::numeric_limits<int>::max();
	//Set source vertex weight to 0, this will be erased later
	weights.insert(std::pair<string, int>(startLabel, 0));

	//Insert ONLY connected vertices into map, initialize weights to INF
	for (const auto & e : findVertex(startLabel)->allOutgoingEdges) {
		//Don't reinsert source vertex
			weights.insert(std::pair<std::string, int>(e->vTo->label, INF));
			//Assign all labels to itself first
			previous.insert(std::pair<string, string>(e->vTo->label, e->vTo->label));
		}

	//Distance of vertexes
	using priorityQueuePair = pair<Vertex*, int> ;
	//Sort priority quee based on least to greatest
	priority_queue<priorityQueuePair, vector<priorityQueuePair>, greater<priorityQueuePair>> pq;

	//Push source node into priority queue
	pq.push(make_pair(findVertex(startLabel) , 0));

	while (!pq.empty()) {
		//Assigns current vertex from priority queue
		Vertex* currentV = pq.top().first;

		//Insert ONLY connected vertices into map, for current vertex
		for (const auto & e : currentV->allOutgoingEdges) {
			//Don't reinsert source vertex
			weights.insert(std::pair<std::string, int>(e->vTo->label, INF));
			//Assign all labels to itself first
			previous.insert(std::pair<string, string>(e->vTo->label, e->vTo->label));
		}

		//Remove vertex from queue
		pq.pop();
		//Iterate through all connected edges to the current vertex
		for (const auto & e : currentV->allOutgoingEdges) {
			//If current vertex + edge weight is less than weight of adjacent vertex
	if ((weights.at(currentV->label) + e->weight) < weights.at(e->vTo->label)) {

				//Adjacent vertex weight is now current weight + edge weight
				weights.at(e->vTo->label) = (weights.at(currentV->label) + e->weight);
				//push weights into priority queue
				pq.push(make_pair(e->vTo, weights.at(e->vTo->label)));
				//Add vertex to previous map
				previous.at(e->vTo->label) = currentV->label;
			}
		}

	}
	//Erase the source weights and the source item
	weights.erase(startLabel);
	previous.erase(startLabel);
}

//Helper functions

/** mark all verticies as unvisited */
void Graph::unvisitVertices() {
	for (const auto & v : vertices) {
		v.second->visited = false;
	}
}

/** helper for depthFirstTraversal */
void Graph::dfsHelper(Vertex *v, void visit(const std::string &)) {
	//Set current label visited and visit label
	visit(v->label);
	v->visited = true;
	//Sort edges or adjacent vertices
	sortEdges(v->label);
	//Visit all adjacent vertices
	for (auto const & e : v->allOutgoingEdges) {
		if (e->vTo->visited != true) {
			dfsHelper(e->vTo, visit);
		}
	}

}

/** helper for breadthFirstTraversal */
void Graph::bfsHelper(Vertex *v, void visit(const std::string &)) {
	//Sorts edges in alphabetical order
	sortEdges(v->label);
	//Create a new empty queue and enqueue v
	queue<Vertex*> *qV = new queue<Vertex*>;
	qV->push(v);

	//Visit the vertex
	visit(v->label);
	v->visited = true;
	//While queue is not empty
	while (!qV->empty()) {
		//Put the next element as your vertex
		Vertex* frontV = qV->front();
		//Dequeue each vertex
		 qV->pop();
		for (auto const & e : frontV->allOutgoingEdges) {
			//If vertex is not vistsed visit it and put it in queue
			if (e->vTo->visited != true) {
				//Set the vertex to visited
				e->vTo->visited = true;
				visit(e->vTo->label);
				//Add vertext queue
				qV->push(e->vTo);
				}
			}
	}
	//Deallocate memory for the queue
	delete qV;
}

/**
* find vertex with given label
* @param vertexLabel string as the vertex label
* @return pointer to vetex or nullptr if not in graph
*/
Vertex * Graph::findVertex(const std::string &vertexLabel) const {
	for (auto const & v : vertices) {
		if (v.second->label == vertexLabel)
			return v.second;
	}
	//Vertex with label was not found
	return nullptr;
}

/**
* create a new vertex,
* @param vertexLabel string as the vertex label
* @return pointer to the newly created vertex
*/
Vertex * Graph::createVertex(const std::string &vertexLabel) {
	return new Vertex(vertexLabel);
}


