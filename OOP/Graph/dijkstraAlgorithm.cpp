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
			:key(val), distance(infinity), visited(false), origin(T()) {}
	};

public:
	Graph(int n = 10)	//default constructor
		:Vertices(n), adjListSize(n*(n - 1)), size(0) {}

	void addVertice(const T& data);
	void addEdge(const T& origin, const T& destination, int cost);
	void dijkstra(const T& data);
	void print();

	typename typedef std::vector<Edge*>::iterator adjItor;

private:
	/*utility*/
	adjItor adjBegin(T key);
	adjItor adjEnd(T key);
	Vertex* minAdjacent(std::unordered_map<T, Vertex*>& box);
	bool visitedBoxVertice(T key, const std::unordered_map<T, Vertex*>& box);
	void dijkstra(const T& data, std::unordered_map<T, Vertex*> box);
	void printBox(const T& origin, std::unordered_map<T, Vertex*>& box);

	std::unordered_map<T, std::vector<Edge*>> Vertices; 	//map with T value as key and list as adjacency list 
	std::unordered_map<T, Vertex*> Box;	//box that holds:  distance, visited, origin tuples

	static const int infinity = std::numeric_limits<int>::max();
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
	A.addVertice(6);
	A.addVertice(7);

	A.addEdge(1, 2, 2);
	A.addEdge(1, 4, 1);
	A.addEdge(2, 5, 10);
	A.addEdge(2, 4, 3);
	A.addEdge(3, 1, 4);
	A.addEdge(3, 6, 5);
	A.addEdge(4, 3, 2);
	A.addEdge(4, 5, 2);
	A.addEdge(4, 6, 8);
	A.addEdge(4, 7, 4);
	A.addEdge(5, 7, 6);
	A.addEdge(7, 6, 1);
	//A.addEdge(6, 3, 200);	//uncomment if want cyclic graph 
	A.dijkstra(1);

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

template <typename T>
void Graph<T>::dijkstra(const T& data) {
	dijkstra(data, Box);
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
@param: const genery type as origin, copy of unordered map
Algorithm (slow for sparse graph) - (V^2):
s.dist = 0;
while( there is an unknown distance vertex )
{
		Vertex v = smallest unknown distance vertex;
		v.known = true;
		for each Vertex w adjacent to v
		if( !w.known )
	{
		DistType cvw = cost of edge from v to w;
		if( v.dist + cvw < w.dist )
		{
			decrease( w.dist to v.dist + cvw );
			w.path = v;
		}
	}
}
no return value
*/
template <typename T>
void Graph<T>::dijkstra(const T& origin, std::unordered_map<T, Vertex*> box) {

	if (box.find(origin) != box.end()) {
		//set chosen vertice's distance to 0
		(*box.find(origin)).second->distance = 0;
		//loop V times
		for (int i = 0; i < size; ++i) {
			//find unVisited vertice with smalles value
			Vertex* temp = minAdjacent(box);
			if (!(*temp).visited) {
				//set chosen vertise to visited
				(*temp).visited = true;
				(*box.find((*temp).key)).second->visited = true;

				//go to adjacent vertices of temp
				typename std::vector<Edge*>::iterator t = adjBegin((*temp).key);
				for (t; t != adjEnd((*temp).key); ++t) {
					//if box in element is not visited
					if (!visitedBoxVertice((*t)->destination, box)) {

						//take weight of edge from origin to adjacent
						T cOA = (*t)->weight;
						if ((*box.find((*temp).key)).second->distance + cOA < (*box.find((*t)->destination)).second->distance) {

							(*box.find((*t)->destination)).second->distance = (*box.find((*temp).key)).second->distance + cOA;
							(*box.find((*t)->destination)).second->origin = (*temp).key;
						}

					}

				}
			}
		}
		printBox(origin, box); 
		return;
	}
	std::cout << "\nNo souch vertice!\n";
}
/*
@param: referance to unordered map
finds smallest unvisited element in box
return pointer to Verte as data type
*/
template <typename T>
typename Graph<T>::Vertex* Graph<T>::minAdjacent(std::unordered_map<T, typename Graph<T>::Vertex*>& box) {

	typename std::unordered_map<T, typename Graph<T>::Vertex*>::iterator p = box.begin()++;
	typename std::unordered_map<T, typename Graph<T>::Vertex*>::iterator min = box.begin();

	for (p; p != box.end(); ++p) {
		if (!visitedBoxVertice((*min).first, box)) {
			if ((*min).second->distance < (*p).second->distance)
				continue;
		}
		min = p;
	}
	return (*min).second;
}
/*
@params: generic data type, referance to box
checks if element is already visited inside box
return boolean
*/
template <typename T>
bool Graph<T>::visitedBoxVertice(T key, const std::unordered_map<T, Vertex*>& box) {
	return (*box.find(key)).second->visited == true;
}

template <typename T>
void Graph<T>::printBox(const T& origin, std::unordered_map<T, Vertex*>& box) {
	typename std::unordered_map<T, Vertex*>::iterator x;
	for (x = box.begin(); x != box.end(); ++x) {
		if ((*x).first == origin)
			std::cout << "o: ";
		std::cout << (*x).first << " " << (*x).second->distance << "\n";
	}
}