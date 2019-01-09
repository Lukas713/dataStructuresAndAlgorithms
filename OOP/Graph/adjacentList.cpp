#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

template <typename T>
class Graph {

public:
	Graph(int n = 10)
		:Vertices(n) {}

	void addVertice(T data); 
	void addEdge(T origin, T destination); 
	void print(); 

private:
	std::unordered_map<T, std::list<T>> Vertices; 
};

template <typename T>
void Graph<T>::print() {
	
	typename std::unordered_map<T, std::list<T>>::iterator p; 
	typename std::list<T>::iterator t;

	for (p = Vertices.begin(); p != Vertices.end(); ++p) {
		std::cout << (*p).first << ": "; 
		
		for (t = (*p).second.begin(); t != (*p).second.end(); ++t)
			std::cout << *t << "--->"; 
		std::cout << "null \n";
	}
}


int main()
{
	
 
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
template <typename T>
void Graph<T>::addVertice(T data) {
	if (Vertices.find(data) != Vertices.end()) {
		throw std::runtime_error("Vertice already exists");
		return;
	}

	std::list<T> adjList;
	Vertices.insert(std::make_pair(data, adjList));
}

template <typename T>
void Graph<T>::addEdge(T from, T to) {

	if (Vertices.find(from) != Vertices.end() && Vertices.find(to) != Vertices.end()) {

		typename std::unordered_map<T, std::list<T>>::iterator p;
		p = Vertices.find(from);
		p->second.push_back(to);
		return;
	}
	throw std::runtime_error("Origin or destination does not eists");
}
