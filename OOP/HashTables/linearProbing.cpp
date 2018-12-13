#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>


template <typename K>
class Hash {
public:
	unsigned int operator()(const K& key) {
		unsigned int hashValue = 0;
		for (char ch : key)
			hashValue = 37 * hashValue + ch;
		return hashValue;
	}
};

template <typename K, typename V, typename H>
class HashMap {
	struct Node {
		K key;
		V value;
		bool available;	//flag 

		Node(const K& k = K(), const V& v = V(), bool a = true)	//flag is true at construct as default
			:key(k), value(v), available(a) {}
		void setValue(const V& v);
		void setKey(const K& k);
		K getKey();
		V getValue();
		bool isAvailable();	//checks flag
	private:
		void changeStatus();	//change flag bool
	};
	typedef typename Node Node; 
	typedef typename std::vector<Node> List; 
	typedef typename List::iterator ListIterator; 
public:
	class Iterator {
	public:
		Iterator(const List& l, const ListIterator& p)
			:node(p), list(&l) {}
		Node& operator*(); 
		Iterator& operator++(); 
		bool operator==(const Iterator& p) const;
		bool operator!=(const Iterator& p) const; 
		friend class HashMap<K, V, H>; 
	private:
		ListIterator node; 
		const List* list; 
	};
public:
	/*public methods*/
	HashMap(int capacity = 101)
		: L(capacity), n(0) {}
	int size() const; 
	bool isEmpty() const; 
	Iterator insert(const K& key, const V& value);
	Iterator find(const K& key); 
	Iterator begin(); 
	Iterator end(); 
private:
	/*utility methods*/
	Iterator finder(const K& key);
	Iterator inserter(const Iterator& p, const Node& n);
	bool endOfArray(const Iterator& p) const;


	/*HashMap properties*/
	std::vector<Node> L; 
	int n;	//number of elements in the list
	Hash<K> hash; 
};

int main()
{
	
	HashMap<std::string, int, Hash<std::string>> a; 
	HashMap<std::string, int, Hash<std::string>>::Iterator p = a.begin(); 
	 
	 p = a.insert("d", 5); 
	 p = a.insert("d", 13); 
	 
	 std::cout << (*p).getKey(); 
	





	return 0;
}
/*
no param
size of list
return int
*/
template <typename K, typename V, typename H>
int HashMap<K, V, H>::size() const {
	return n;
}
/*
no param
checks if list is empty
boolean return
*/
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::isEmpty() const {
	return n == 0;
}
/*Iterator methods
1 param: iterator (const referance)
checks if list is diferent
and equility of iterator's nodes
return boolean
*/
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator==(const Iterator& p) const {
	if (list != p.list)
		return false;
	return (node == p.node);
}
/*
1 param: iterator (const referance)
check inequalit of two iterators
checks inner list and node properties
return boolean
*/
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator!=(const Iterator& p) const {
	if (list != p.list)
		return false;
	return (node != p.node);
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::endOfArray(const Iterator& p) const {
	return (p.node == p.list->end());
}
/*
no param
move iterator to next node
modify operator overload
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++() {
	++node;
	return *this; 
}
/*
no param
access operator overload
access to node iterator property
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Node& HashMap<K, V, H>::Iterator::operator*() {
	return *node;
}
/*
no param
construct Iterator with node pointer as property to begining of list
return Iterator object
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin() {
	return Iterator(L, L.begin());
}
/*
no param
construct Iterator with node pointer as property to element after last 
return Iterator object
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::end() {
	return Iterator(L, L.end());
}
/*
1 param: K (const referance)
invoke finder()
checks if key exists
return Iterator object
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& key) {
	Iterator p = finder(key);
	if (!endOfArray(p)); 
		return p;
	return end();
}
/*
1 param: K (const referance)
invoke h(key) % N
construct Iterator object with node pointer at position as property
return Iterator object
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::finder(const K& key) {
	int indice = hash(key) % L.size();
	ListIterator node = L.begin() + indice;
	Iterator p(L, node);
	return p;
}
/*
2 params: iterator and node
inserts element at 
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& p, const Node& x) {
	return Iterator(L, L.insert(p.node, x));
}
/*
2 params: key nad value (constant references)
construct iterator and inserts new node
return Iterator object
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::insert(const K& key, const V& value) {
	Iterator p = finder(key);
	for (p.node; p.node != L.end(); ++p) {
		if (!(*p).isAvailable() && (*p).getKey() == key) {	//if key is reserved
			(*p).setValue(value);
			return p;
		}
		if ((*p).isAvailable())	//if key is not reserved
			return inserter(p, Node(key, value, false)); //construct unaviable node, insert it in the list and return Iterator object

		if (p.node == (L.begin() + (L.size() - 1)))
			p.node = L.begin(); 
	}
	return p; 
}
/*
		void setValue(const V& v) { value = v;  };
		void setKey(const K& k) { key = k;  };
		K getKey() { return key;  };
		V getValue() { return value;  }
		bool isAvailable() { return available;  }
	private:
		void changeStatus() {
			available = false;
		}
*/
template <typename K, typename V, typename H>
void HashMap<K, V, H>::Node::setValue(const V& v) {
	this->value = v; 
}
template <typename K, typename V, typename H>
void HashMap<K, V, H>::Node::setKey(const K& k) {
	this->key = k;
}
template <typename K, typename V, typename H>
V HashMap<K, V, H>::Node::getValue() {
	return value; 
}
template <typename K, typename V, typename H>
K HashMap<K, V, H>::Node::getKey() {
	return key;
}
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Node::isAvailable() {
	return available;
}
template <typename K, typename V, typename H>
void HashMap<K, V, H>::Node::changeStatus() {
	available = !available;
}



