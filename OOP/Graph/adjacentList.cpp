#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>


template <typename T>	//generic data type
class Graph {

public:
	Graph(int n = 10)	//default constructor
		:Vertices(n), adjListSize(n*(n-1)) {}

	void addVertice(const T& data);
	void addEdge(const T& origin, const T& destination);
	void print();

private:
	std::unordered_map<T, std::vector<T>> Vertices; 	//map with T value as key and list as adjacency list 
	int adjListSize; 
};




int main()
{

	/*
	std::vector<int> A; 
	A.emplace(A.end(), 2); 

	std::vector<int>::iterator p; 
	for (p = A.begin(); p != A.end(); ++p)
		std::cout << *p << " "; 
	*/

	Graph<int> A;
	A.addVertice(5);
	A.addVertice(4);
	A.addVertice(3);
	A.addVertice(2);
	A.addVertice(1);
	A.addEdge(5, 1);
	A.addEdge(5, 2);
	A.addEdge(5, 3);
	A.addEdge(1, 5);
	A.addEdge(1, 4);
	A.print();



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
	std::vector<T> adjList;
	Vertices.insert(std::make_pair(data, adjList));
}

/*
@param: two generic data types
finds origin and inserts edge that leads to destination
throw exeption if list of edges is higher than n(n-1), (highest number of adjacent verticies)
throw exeption if origin or destination does not exists
no return value
*/
template <typename T>
void Graph<T>::addEdge(const T& origin, const T& destination) {
	//check if there is origin and destination verices
	if (Vertices.find(origin) != Vertices.end() && Vertices.find(destination) != Vertices.end()) {
		typename std::unordered_map<T, std::vector<T>>::iterator p = Vertices.find(origin);	//create iterator that points to vertice
		
		if (p->second.size() < adjListSize) {
			p->second.emplace(p->second.end(), destination); //push destination edge into adjacency list
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

	typename std::unordered_map<T, std::vector<T>>::iterator p;
	typename std::vector<T>::iterator t;

	for (p = Vertices.begin(); p != Vertices.end(); ++p) {
		std::cout << (*p).first << ": ";

		for (t = (*p).second.begin(); t != (*p).second.end(); ++t)
			std::cout << *t << ", ";
		std::cout << "\n";
	}
}
