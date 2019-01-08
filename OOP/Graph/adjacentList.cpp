#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>




class Graph {
	class Vertex {
		std::vector<std::string> adjList; 
	public:
		Vertex(int size = 10)
			:adjList(size) {}
		friend class Graph;
	};
public:
	Graph(int n = 10)
		:Vertices(n), size(n) {}
	void addEdge(std::string origin, std::string destination); 
	void addVertice(std::string); 

private:
	std::unordered_map<std::string, Vertex> Vertices; //every position has list of vertices that connects with ith vertice
	int size; 
};




void Graph::addEdge(std::string origin, std::string dest) {
	if (Vertices.find(origin) != Vertices.end()) {
		std::unordered_map<std::string, Vertex>::iterator p = Vertices.find(origin); 
		p->second.adjList.push_back(dest); 
		return; 
	}
	std::cout << "No souch vertice"; 
}

void Graph::addVertice(std::string key){
	if (Vertices.find(key) != Vertices.end()) {
		std::cout << "Vertice already exists \n"; 
		return; 
	}
	Vertex newVertex(size*(size - 1)); 
	Vertices.insert(std::make_pair(key, newVertex)); 
}



int main()
{

	Graph A; 
	A.addVertice("lukas"); 
	A.addVertice("lea"); 
	A.addVertice("dubravka");
	A.addVertice("goranka"); 
	
	



	return 0;
}

