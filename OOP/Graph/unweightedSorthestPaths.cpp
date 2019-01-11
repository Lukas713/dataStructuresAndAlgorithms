#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>


template <typename T>	//generic data type
class Graph  {

	struct Edge {
		T destination; 
		int weight; 

		Edge(const T& value, int w = 0)
			: destination(value), weight(w) {}
	};

	struct Vertex {
		int distance; 
		bool visited; 
		T origin; 

		Vertex()
			:distance(infinity), visited(false), origin(0) {}
	};

public:
	Graph(int n = 10)	//default constructor
		:Vertices(n), adjListSize(n*(n - 1)), size(0) {}

	void addVertice(const T& data);
	void addEdge(const T& origin, const T& destination, int cost);
	void BFS(T origin); //breath-first search
	//void fasterBFS(T origin); 
	void print();

private:
	/*utility*/
	void BFS(T origin, std::unordered_map<T, Vertex*> box); //breath-first search
	//void fasterBFS(T origin, std::unordered_map<T, std::tuple<int, bool, T>> box);

	std::unordered_map<T, std::vector<Edge*>> Vertices; 	//map with T value as key and list as adjacency list 
	std::unordered_map<T, Vertex*> Box;	//box that holds:  distance, visited, origin tuples

	static const int infinity = 1000000; 
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

	
	A.addEdge(1, 2, 100);
	A.addEdge(1, 4, 200);
	A.addEdge(2, 5, 300);
	A.addEdge(2, 4, 250);
	A.addEdge(3, 1, 50);
	A.addEdge(3, 6, 200);
	A.addEdge(4, 3, 150);
	A.addEdge(4, 5, 150);
	A.addEdge(4, 6, 150); 
	A.addEdge(4, 7, 150);
	A.addEdge(5, 7, 150);
	A.addEdge(7, 6, 150);
	//A.addEdge(7, 2);	//uncomment if want cyclic graph 
	A.BFS(3); 

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

	Vertex* temp = new Vertex; 
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
template<typename T>
void Graph<T>::BFS(T origin) {
	BFS(origin, Box); 
}
/*
@param: generic type value
iterate over verties and assign distance between
no return value

expensive version O(V^2)
*/
template<typename T>
void Graph<T>::BFS(T origin, std::unordered_map<T, Vertex*> box) {

	typename std::unordered_map<T, Vertex*>::iterator p;
	p = box.find(origin);

	if (p != box.end()) {
		(*p).second->distance = 0; 
		//iterate over distances
		for (int curDistance = 0; curDistance < size; ++curDistance) {
			//iterate over every vertice inside box
			for (p = box.begin(); p != box.end(); ++p) {
				//if its not visited AND its on i-th distance
				if (!(*p).second->visited && (*p).second->distance == curDistance) {
					//visit that vertice
					(*p).second->visited = true;
					//go to adjacent verticies

					//adjacency list iterator
					typename std::vector<Edge*>::iterator pV;
					pV = (*Vertices.find((*p).first)).second.begin();
					//iterate over elements inside adjacency list
					for (pV; pV != (*Vertices.find((*p).first)).second.end(); ++pV) {

						//take distance from tuple inside box
						int x = (*box.find((*pV)->destination)).second->distance;

						if (x == infinity) {
							(*box.find((*pV)->destination)).second->distance = (curDistance + 1); //distance from origin
							(*box.find((*pV)->destination)).second->origin = (*p).first;
						}
					}
				}
			}
		}
		for (p = box.begin(); p != box.end(); ++p)
			std::cout << (*p).first << " : " << (*p).second->distance << "\n";
		return; 
	}
	std::cout << "No souch origin \n";
}


