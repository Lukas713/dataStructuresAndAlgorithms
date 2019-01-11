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

public:
	Graph(int n = 10)	//default constructor
		:Vertices(n), adjListSize(n*(n - 1)), size(0) {}

	void addVertice(const T& data);
	void addEdge(const T& origin, const T& destination, int cost);
	void BFS(T origin); //breath-first search
	void print();

private:
	std::unordered_map<T, std::vector<Edge*>> Vertices; 	//map with T value as key and list as adjacency list 
	std::unordered_map<T, std::tuple<int, bool, T>> Box;	//box that holds:  distance, visited, origin tuples

	static const int infinity = 1000000; 
	int adjListSize;
	int size; 
};

/*
@param: generic type value

*/
template<typename T>
void Graph<T>::BFS(T origin) {
	
	typename std::unordered_map<T, std::tuple<int, bool, T>>::iterator p; 

	p = Box.find(origin);

	if (p != Box.end()) {
		std::get<0>((*p).second) = 0;

		//iterate over distances
		for (int curDistance = 0; curDistance < size; ++curDistance) {
			//iterate over every vertice inside box
			for (p = Box.begin(); p != Box.end(); ++p) {
				//if its not visited AND its on i-th distance
				if (!std::get<1>((*p).second) && std::get<0>((*p).second) == curDistance) {
					//visit that vertice
					std::get<1>((*p).second) = true;
					//go to adjacent verticies

					//adjacency list iterator
					typename std::vector<Edge*>::iterator pV;
					pV = (*Vertices.find((*p).first)).second.begin();
					//iterate over elements inside adjacency list
					for (pV; pV != (*Vertices.find((*p).first)).second.end(); ++pV) {

						//take distance from tuple inside box
						int x = std::get<0>((*Box.find((*pV)->destination)).second);

						if (x == infinity) {
							std::get<0>((*Box.find((*pV)->destination)).second) = (curDistance + 1); //distance from origin
							std::get<2>((*Box.find((*pV)->destination)).second) = (*p).first;
						}
					}
				}
			}
		}

		for (p = Box.begin(); p != Box.end(); ++p)
			std::cout << (*p).first << " : " << std::get<0>((*p).second) << "\n";
	}
	
	//there is no souch origin
}




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
	A.BFS(2); 

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
	Box.insert(std::make_pair(data, std::make_tuple(infinity, false, T()))); 
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
