#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>

template <typename T>	//generic data type
class Graph  {

	struct Vertex {
		T destination; 

		Vertex(const T& value)
			: destination(value) {}
		T getDestination() { return destination; }
	};

public:
	Graph(int n = 10)	//default constructor
		:Vertices(n), adjListSize(n*(n - 1)) {}

	void addVertice(const T& data);
	void addEdge(const T& origin, const T& destination);
	void print();
	void topSort(); //invoke utility topSort(Box)

private:
	void topSort(std::unordered_map<T, int> map); 

	std::unordered_map<T, std::vector<Vertex*>> Vertices; 	//map with T value as key and list as adjacency list
	std::unordered_map<T, int> Box; //box that holds indegree of every vertice

	int adjListSize;
};

int main()
{
	Graph<int> A;

	A.addVertice(0);
	A.addVertice(1);
	A.addVertice(2);
	A.addVertice(3);
	A.addVertice(4);
	A.addVertice(5); 
	A.addVertice(6); 
	A.addVertice(7); 

	A.addEdge(0, 1);
	A.addEdge(0, 3);
	A.addEdge(2, 5);
	A.addEdge(5, 7);
	A.addEdge(3, 7);
	A.addEdge(6, 7);
	A.addEdge(4, 6); 
	//A.addEdge(7, 2);	//uncomment if want cyclic graph 
	

	A.topSort(); 

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
	std::vector<Vertex*> adjList;
	Vertices.insert(std::make_pair(data, adjList));
	Box.insert(std::make_pair(data, 0)); 
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
		typename std::unordered_map<T, std::vector<Vertex*>>::iterator p = Vertices.find(origin);	//create iterator that points to vertice

		if (p->second.size() < adjListSize) {
			Vertex* adjVertice = new Vertex(destination); 
			p->second.emplace(p->second.end(), adjVertice); //push destination edge into adjacency list

			//add element into indegree box
			(*Box.find(destination)).second += 1; 
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
	typename std::unordered_map<T, std::vector<Vertex*>>::iterator p;
	typename std::vector<Vertex*>::iterator t;

	for (p = Vertices.begin(); p != Vertices.end(); ++p) {
		std::cout << (*p).first << ": ";

		for (t = (*p).second.begin(); t != (*p).second.end(); ++t)
			std::cout << (*t)->destination << ", ";
		std::cout << "\n";
	}
}

template <typename T>
void Graph<T>::topSort() {
	topSort(Box);
}
/*
@param: copyed unordered map by value
insert elements that has 0 indegree into queue
remove's 1 indegree from every vertice inside adjacency list inside that element with 0 indegree
recursive call for minimizing the box
no return value
*/
template <typename T>
void Graph<T>::topSort(std::unordered_map<T, int> box) {
	if (box.empty())
		return;

	std::queue<T> q; //holds vertices with 0 incidents

	typename std::unordered_map<T, int>::iterator p;
	for (p = box.begin(); p != box.end(); ++p) {	//iterate over indegree box

		if ((*p).second > 0)	//if vertice is incident
			continue;	//skip

		q.push((*p).first);		//else push element into queue
	}

	if (q.empty()) {
		std::cout << "\nGraph is not acyclic"; 
		return; 
	}

	//untill queue has elements
	while (!q.empty()) {

		typename std::vector<Vertex*>::iterator pV;
		pV = (*Vertices.find(q.front())).second.begin();	//adjacency list of vertice that has same key as queue's top element

		while (pV != (*Vertices.find(q.front())).second.end()) //traverse untill end of the adjacency list
			(*box.find((*pV++)->destination)).second -= 1;	//remove's edges from vertice

		box.erase(q.front()); //totaly remove that vertice from box

		std::cout << q.front() << " ";
		q.pop();	//remove it from queue
	}
	topSort(box); //recursive call on same box without verticies that are checked
}

