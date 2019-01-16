#include "pch.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>


template <typename T>	//generic data type
class Graph {
	struct Edge {
		T destination;
		int weight;
		Edge(const T& value, int w = 0)
			: destination(value), weight(w) {}
	};
	struct Vertex {
		T key;
		int distance;
		bool visited;
		T origin;
		Vertex(T val)
			:key(val), distance(infinity), visited(false), origin(NOT_VERTICE) {}
	};
	struct isLess {
		bool operator()(const Graph<T>::Vertex* a, const Graph<T>::Vertex* b) const {
			return (a->distance > b->distance);
		}
	};
public:
	Graph(int n = 10)	//default constructor
		:Vertices(n), adjListSize(n*(n - 1)), size(0) {}

	void addVertice(const T& data);
	void addEdge(const T& origin, const T& destination, int cost);
	void bellmanFord(const T& origin, const T& finish);
	void print();

	typename typedef std::vector<Edge*>::iterator adjItor;
	//https://www.programiz.com/dsa/bellman-ford-algorithm
private:
	/*utility*/
	adjItor adjBegin(T key);
	adjItor adjEnd(T key);
	Vertex* minAdjacent(std::unordered_map<T, Vertex*>& box);
	void printBox(const T& origin, std::unordered_map<T, Vertex*>& box);
	void printPath(const T& origin, std::unordered_map<T, Vertex*>& box);
	void bellmanFord(const T& start, const T& finish, std::unordered_map<T, Vertex*> box);
	int getDistance(const T& origin, const std::unordered_map<T, Vertex*>& box) {
		return (*box.find(origin)).second->distance;
	}
	void setDistance(int newDistance, const T& origin, std::unordered_map<T, Vertex*>& box) {
		(*box.find(origin)).second->distance = newDistance;
	}

	std::unordered_map<T, std::vector<Edge*>> Vertices; 	//map with T value as key and list as adjacency list 
	std::unordered_map<T, Vertex*> Box;	//box that holds:  distance, visited, origin tuples

	static const int infinity = std::numeric_limits<int>::max();
	static const int NOT_VERTICE = std::numeric_limits<int>::min();
	int adjListSize;
	int size;
};

int main()
{
	Graph<int> A;

	A.addVertice(1);
	A.addVertice(2);
	A.addVertice(3);
	A.addVertice(4);
	A.addVertice(5);

	A.addEdge(1, 2, 4);
	A.addEdge(1, 3, 2);
	A.addEdge(2, 3, 3);
	A.addEdge(2, 4, 2);
	A.addEdge(2, 5, 3);
	A.addEdge(3, 2, 1);
	A.addEdge(3, 4, 4);
	A.addEdge(3, 5, 5);
	A.addEdge(5, 4, -5);
	//A.addEdge(6, 3, 200);	//uncomment if want cyclic graph 
	A.bellmanFord(1, 2);

	return 0;
}
/*
@param : generic data type
adds verrice into map
throw exeption if vertice aready exists
no return value
*/
template <typename T>
void Graph<T>::addVertice(const T& data) {
	//dont allow duplicate vertice's
	if (Vertices.find(data) != Vertices.end()) {
		throw std::runtime_error("Vertice already exists");
		return;
	}
	//create new list, insert argument into map as key and  new adjacency list as data value
	std::vector<Edge*> adjList;
	Vertices.insert(std::make_pair(data, adjList));

	Vertex* temp = new Vertex(data);
	Box.insert(std::make_pair(data, temp));
	++size;
}

/*
@param: two generic data types
finds origin and inserts edge that leads to destination
throw exeption if list of edges is higher than n(n-1), (highest number of adjacent verticies)
throw exeption if origin or destination does not exists
no return value
*/
template <typename T>
void Graph<T>::addEdge(const T& origin, const T& destination, int cost) {
	//check if there is origin and destination verices
	if (Vertices.find(origin) != Vertices.end() && Vertices.find(destination) != Vertices.end()) {

		typename std::unordered_map<T, std::vector<Edge*>>::iterator p = Vertices.find(origin);	//create iterator that points to vertice
		if (p->second.size() < adjListSize) {
			Edge* adjVertice = new Edge(destination, cost);
			p->second.emplace(p->second.end(), adjVertice); //push destination edge into adjacency list
			return;
		}
		throw std::runtime_error("Adjacency list is full");
		return;
	}
	throw std::runtime_error("Origin or destination does not exists");	//error if one of arguments does not exists
}
/*
@param: no param
visits every verticies and prints adjacent elements
no return value
*/
template <typename T>
void Graph<T>::print() {
	typename std::unordered_map<T, std::vector<Edge*>>::iterator p;
	typename std::vector<Edge*>::iterator t;

	for (p = Vertices.begin(); p != Vertices.end(); ++p) {
		std::cout << (*p).first << ": ";

		for (t = (*p).second.begin(); t != (*p).second.end(); ++t)
			std::cout << " (" << (*t)->weight << ") " << (*t)->destination << ", ";
		std::cout << "\n";
	}
}

/*
@param: generic type key
return iterator on first adjacency list Vertice
*/
template <typename T>
typename Graph<T>::adjItor Graph<T>::adjBegin(T key) {
	return (*Vertices.find(key)).second.begin();
}

/*
@param: generic type key
return iterator on first adjacency list Vertice
*/
template <typename T>
typename Graph<T>::adjItor Graph<T>::adjEnd(T key) {
	return (*Vertices.find(key)).second.end();
}
/*
sequentialy
@param: referance to unordered map
finds smallest unvisited element in box
return pointer to Verte as data type
*/
template <typename T>
typename Graph<T>::Vertex* Graph<T>::minAdjacent(std::unordered_map<T, typename Graph<T>::Vertex*>& box) {

	typename std::unordered_map<T, typename Graph<T>::Vertex*>::iterator p = box.begin()++;
	typename std::unordered_map<T, typename Graph<T>::Vertex*>::iterator min = box.begin();

	for (p; p != box.end(); ++p) {
		if ((*p).second->visited)
			continue;
		if ((*min).second->distance > (*p).second->distance || (*min).second->visited) {
			min = p;
		}
	}
	return (*min).second;
}

/*
utility
@param: starting vertice and box
cout whole box and he's distances
*/
template <typename T>
void Graph<T>::printBox(const T& origin, std::unordered_map<T, Vertex*>& box) {
	typename std::unordered_map<T, Vertex*>::iterator x;
	for (x = box.begin(); x != box.end(); ++x) {
		if ((*x).second->distance != infinity) {
			std::cout << (*x).first << " " << (*x).second->distance << "\n";
			continue;
		}
		std::cout << (*x).first << " no path" << "\n";
	}
}

/*
@param: generic data type, box referance
recursively print path from finish to begining
no return value
*/
template <typename T>
void Graph<T>::printPath(const T& from, std::unordered_map<T, Vertex*>& box) {
	if ((*box.find(from)).second->origin != NOT_VERTICE) {
		printPath((*box.find(from)).second->origin, box);
		std::cout << " to ";
	}
	std::cout << (*box.find(from)).first << " ";
}

template<typename T>
void Graph<T>::bellmanFord(const T& origin, const T& finish) {
	bellmanFord(origin, finish, Box);
}
/*
distance[S] <- 0
for each vertex V in G
		for each edge (U,V) in G
			tempDistance <- distance[U] + edge_weight(U, V)
			if tempDistance < distance[V]
			   distance[V] <- tempDistance
			   previous[V] <- U

for each edge (U,V) in G
	If distance[U] + edge_weight(U, V) < distance[V]
		Error: Negative Cycle Exists

	return distance[], previous[]
*/
template<typename T>
void Graph<T>::bellmanFord(const T& origin, const T& finish, std::unordered_map<T, Vertex*> box) {

	/*initialize graph: step 0*/
	setDistance(0, origin, box);

	/*relax all edges V - 1 times: step 2*/
	for (int i = 1; i < size; ++i) {
		typename std::unordered_map<T, Vertex*>::iterator p;
		for (p = box.begin(); p != box.end(); ++p) {	//for each vertex in graph

			typename std::vector<Edge*>::iterator t;
			for (t = adjBegin((*p).first); t != adjEnd((*p).first); ++t) {	//for each adjacent vertice 

				//relaxation
				int distance = getDistance((*p).first, box) + (*t)->weight;
				if (getDistance((*p).first, box) != infinity && getDistance((*t)->destination, box) > distance) {

					setDistance(distance, (*t)->destination, box);
					(*box.find((*t)->destination)).second->origin = (*p).first;
				}
			}
		}
	}
	/*check if there is cycle with negative weight : step 3*/
	typename std::unordered_map<T, Vertex*>::iterator p;
	for (p = box.begin(); p != box.end(); ++p) {	//for each vertex in graph

		typename std::vector<Edge*>::iterator t;
		for (t = adjBegin((*p).first); t != adjEnd((*p).first); ++t) {

			int distance = getDistance((*p).first, box) + (*t)->weight;
			if (getDistance((*p).first, box) != infinity && getDistance((*t)->destination, box) > distance) {
				std::cout << "Negative weight cycle deteted \n";
				return;
			}
		}
	}
	printBox(finish, box);
}
