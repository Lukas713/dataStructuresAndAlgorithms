#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <queue>

class Exeption {
public:
    Exeption(const std::string& err){
        this->err = err;
    }
    std::string getError(){
        return err;
    }
private:
    std::string err;
};

template <typename T>
class Graph {
    struct Edge {
        T destination;
        int capacity;
        int flow;

        Edge(const T& dest, int cap = 0)
            :destination(dest), capacity(cap) {};
    };
    struct Vertex {
        T key;
        bool visited;
        int distance;
        T origin;

        Vertex(const T& k)
            :key(k), visited(false), distance(infinity), origin(NOT_VERTICE) {}
    };
public:
    Graph()
        :Vertices(), size(0) {};
    void push_vertice(const T& origin);
    void push_edge(const T& origin, const T& destination, int capacity);
    void fordFulkerson(const T& origin, const T& sink);

    typedef typename std::vector<Edge*>::iterator adjItor;
    typedef std::unordered_map<T, std::vector<Edge*>> V;
    typedef std::unordered_map<T, Vertex*> B;
private:
    static const int infinity = std::numeric_limits<int>::max();
    static const T NOT_VERTICE = std::numeric_limits<T>::max();;
    /*utility*/
    void fordFulkerson(const T& origin, const T& sink, V vertices, B box);
    adjItor adjBegin(T key, V& vertices);
    adjItor adjEnd(T key, V& vertices);
    void BFS(const T& origin, V& vertice, B& box);

    /*properties*/
    std::unordered_map<T, std::vector<Edge*>> Vertices;
    std::unordered_map<T, Vertex*> Box;
    int size;
};

template <typename T>
void Graph<T>::BFS(const T &origin, Graph<T>::V &vertices, Graph<T>::B &box) {

    std::queue<Vertex*> q;

    (*box.find(origin)).second->distance = 0;
   // Vertex* source = new Vertex((*box.find(origin)).second);
    q.push((*box.find(origin)).second);

    while(!q.empty()){

        Vertex* front = q.front();
        q.pop();

        typename std::vector<Edge*>::iterator p = adjBegin((*front).key, vertices);
        for(p; p != adjEnd((*front).key, vertices); ++p){
            //if Vertex from adjacecny list has infinity distance (default)
            typename std::unordered_map<T, Vertex*>::iterator pBx;
            pBx = box.find((*p)->destination);

            if ((*pBx).second->distance != infinity)
                continue;
            //set distance to vertice that holds him (in adjacency list) + 1
            (*pBx).second->distance = (*front).distance + 1;
            (*pBx).second->origin = (*front).key; //set path
            q.push((*pBx).second);	//set vertice of lvl 1 into queue
        }
    }
}


template <typename T>
void Graph<T>::fordFulkerson(const T &origin, const T &sink, V vertices, B box) {
    int maxFlow = 0;    //variable that holds the maxFlow
    //Step 1. init starting flow
    typename std::unordered_map<T, std::vector<Edge*>>::iterator p;
    for(p = vertices.begin(); p != vertices.end(); ++p){    //every vertice

        typename std::vector<Edge*>::iterator pV;
        pV = (*p).second.begin();
        for(pV; pV != (*p).second.end(); ++p)
            (*pV)->flow = 0;    //set flow to every adjacent vertice to 0

    }

    //Step 2. create box that holds path from source untill sink
    BFS(origin, vertices, box);

    //Step 3. find path and update flow
    typename std::unordered_map<T, Vertex*>::iterator pB = box.find(sink);  //go to sink vertice
    int minCapacity;
    while(pB != box.find(origin)){  //traverse within path till source

        typename std::vector<Edge*>::iterator pV = adjBegin((*pB).second->origin, vertices);
        for(pV; pV != adjEnd((*pB).second->origin, vertices); ++pV){

            if((*pV)->destination != (*pB).second->key)
                continue;

            minCapacity = (*pV)->capacity;
            if((*pV)->destination != sink)
                minCapacity = std::min((*pV)->capacity, minCapacity);
        }


        pB = box.find((*pB).second->origin);
    }
}

int main(){

    Graph<int> A;

    A.push_vertice(1);
    A.push_vertice(2);
    A.push_vertice(3);
    A.push_vertice(4);
    A.push_vertice(5);
    A.push_vertice(6);

    A.push_edge(1, 2, 11);
    A.push_edge(1, 3, 13);
    A.push_edge(2, 3, 4);
    A.push_edge(2, 4, 12);
    A.push_edge(3, 2, 10);
    A.push_edge(3, 5, 14);
    A.push_edge(4, 3, 9);
    A.push_edge(5, 4, 7);
    A.push_edge(5, 6, 4);
    A.push_edge(4, 6, 20);

    A.fordFulkerson(1, 6);


    return 0;
}
/*
@param: generic type key
return iterator on first adjacency list Vertice
*/
template <typename T>
typename Graph<T>::adjItor Graph<T>::adjBegin(T key, V& vertices) {
    return (*vertices.find(key)).second.begin();
}

/*
@param: generic type key
return iterator on first adjacency list Vertice
*/
template <typename T>
typename Graph<T>::adjItor Graph<T>::adjEnd(T key, V& vertices) {
    return (*vertices.find(key)).second.end();
}

template <typename T>
void Graph<T>::push_vertice(const T &origin) {
    try{
        if(Vertices.find(origin) != Vertices.end())
            throw Exeption("Vertice is already inside map!");

        std::vector<Edge*> adjList;
        Vertices.insert(std::make_pair(origin, adjList));
        Vertex* newVertex = new Vertex(origin);
        Box.insert(std::make_pair(origin, newVertex));

    }catch(Exeption& err){
        std::cout << err.getError();
    }
}

template <typename T>
void Graph<T>::push_edge(const T &origin, const T &sink, int capacity) {
    try{
        if(Vertices.find(origin) != Vertices.end() || Vertices.find(sink) != Vertices.end()){

            Edge* newEdge = new Edge(sink, capacity);
            typename std::unordered_map<T, std::vector<Edge*>>::iterator p = Vertices.find(origin);
            (*p).second.push_back(newEdge);
            return;
        }
        throw Exeption("Origin or sink does not exist!");
    }catch(Exeption& err){
        std::cout << err.getError();
    }
}

template <typename T>
void Graph<T>::fordFulkerson(const T &origin, const T &sink) {
    fordFulkerson(origin, sink, Vertices, Box);
}