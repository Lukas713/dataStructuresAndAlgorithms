#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <unordered_map>


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

template <typename K>
class EqualKeys {
public:
	bool operator()(const K& one, const K& other) {
		return (one == other); 
	}
};

template <typename K, typename V, typename H, typename E>
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
		void changeStatus();	//change flag bool
	private:
		
	};
	typedef typename Node Node; 
	typedef typename std::vector<Node> List; 
	typedef typename List::iterator ListIterator; 
	typedef typename List::const_iterator constListIterator; 
public:
	class iterator {
	public:
		iterator(const List& l = List(), const ListIterator& p = ListIterator())
			:node(p), list(&l) {};
		Node& operator*(); 
		iterator& operator++();
		iterator& operator++(int); 
		bool operator==(const iterator& p) const;
		bool operator!=(const iterator& p) const;
		friend class HashMap<K, V, H, E>; 
	private:
		ListIterator node; 
		const List* list; 
	};
	class const_iterator {
		public:
			const_iterator(const List& l = List(), constListIterator p = constListIterator())
				:node(p), list(&l) {};
		const Node& operator*() const; 
		const_iterator& operator++();
		const_iterator& operator++(int);
		bool operator==(const const_iterator& p) const;
		bool operator!=(const const_iterator& p) const;
		friend class HashMap<K, V, H, E>;
	private:
		constListIterator node;
		const List* list;
	};
public:
	/*public methods*/
	HashMap(int capacity = 101)
		: L(capacity), n(0) {}
	int size() const; 
	bool isEmpty() const; 
	iterator insert(const K& key, const V& value);
	iterator find(const K& key);
	iterator erase(const K& key); 
	iterator begin();
	iterator end();
	const_iterator cbegin() const;
	const_iterator cend() const;
private:
	/*utility methods*/
	iterator finder(const K& key);
	iterator inserter(const iterator& position, const Node& n);
	iterator eraser(iterator& position);
	bool endOfArray(const iterator& position) const;


	/*HashMap properties*/
	std::vector<Node> L; 
	int n;	//number of elements in the list
	Hash<K> hash;
	EqualKeys<K> testKeys; 
};

template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::erase(const K& key) {
	//get indice

	int i = hash(key) % L.size(); 
	for (i; i < L.size(); (i + 1) % L.size()) {
		if (!testKeys(L[i].getKey(), key) || L[i].isAvailable()) {	//search untill key is valid
			continue; 
		}	
		iterator p(L, L.begin() + i); 
		L[i].changeStatus(); 
		return eraser(p); 
	}
	//if indice is out of bounds
	return end(); 
}

template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::eraser(iterator& p) {
	--n;
	return iterator(L, L.erase(p.node));
}

int main()
{
	HashMap <std::string, int, Hash<std::string>, EqualKeys<std::string>> a; 
	HashMap <std::string, int, Hash<std::string>, EqualKeys<std::string>>::iterator ca; 
	a.insert("a", 3); 
	a.insert("b", 4); 
	a.insert("c", 5); 
	a.insert("c", 7); 
	a.erase("z"); 
	for (ca = a.begin(); ca != a.end(); ++ca) {
		if ((*ca).isAvailable()) {
			continue; 
		}
		std::cout << (*ca).getKey() << " : " << (*ca).getValue() << "\n"; 
	}








	return 0;
}
/*
no param
size of list
return int
*/
template <typename K, typename V, typename H, typename E>
int HashMap<K, V, H, E>::size() const {
	return n;
}
/*
no param
checks if list is empty
boolean return
*/
template <typename K, typename V, typename H, typename E>
bool HashMap<K, V, H, E>::isEmpty() const {
	return n == 0;
}
/*Iterator methods
1 param: iterator (const referance)
checks if list is diferent
and equility of iterator's nodes
return boolean
*/
template <typename K, typename V, typename H, typename E>
bool HashMap<K, V, H, E>::iterator::operator==(const iterator& p) const {
	if (list != p.list)
		return false;
	return (node == p.node);
}
/*
1 param: const_iterator(const referance)
checks if list is diferent
and equility of iterator's nodes
return boolean
*/
template <typename K, typename V, typename H, typename E>
bool HashMap<K, V, H, E>::const_iterator::operator==(const const_iterator& p) const {
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
template <typename K, typename V, typename H, typename E>
bool HashMap<K, V, H, E>::iterator::operator!=(const iterator& p) const {
	if (list != p.list)
		return false;
	return (node != p.node);
}
/*
1 param: iterator (const referance)
check inequalit of two iterators
checks inner list and node properties
return boolean
*/
template <typename K, typename V, typename H, typename E>
bool HashMap<K, V, H, E>::const_iterator::operator!=(const const_iterator& p) const {
	if (list != p.list)
		return false;
	return (node != p.node);
}

template <typename K, typename V, typename H, typename E>
bool HashMap<K, V, H, E>::endOfArray(const iterator& p) const {
	return (p.node == p.list->end());
}
/*
no param
move iterator to next node
modify pre increment operator overload
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator& HashMap<K, V, H, E>::iterator::operator++() {
	++node;
	return *this; 
}
/*
no param
move iterator to next node
modify pre increment operator overload
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::const_iterator& HashMap<K, V, H, E>::const_iterator::operator++() {
	++node;
	return *this;
}
/*
no param 
move iteratr to next node
modify post increment operator overload
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator& HashMap<K, V, H, E>::iterator::operator++(int) {
	auto temp = *this; 
	++(*this); 
	return temp; 
}
/*
no param
move iteratr to next node
modify post increment operator overload
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::const_iterator& HashMap<K, V, H, E>::const_iterator::operator++(int) {
	auto temp = *this;
	++(*this);
	return temp;
}
/*
no param
access operator overload
access to node iterator property
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::Node& HashMap<K, V, H, E>::iterator::operator*(){
	return *node;
}
/*
no param
access operator overload
access to node iterator property
*/
template <typename K, typename V, typename H, typename E>
typename const HashMap<K, V, H, E>::Node& HashMap<K, V, H, E>::const_iterator::operator*() const {
	return *node;
}
/*
no param
construct Iterator with node pointer as property to begining of list
return Iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::begin() {
	return iterator(L, L.begin());
}
/*
no param
construct const_Iterator with node pointer as property to begining of list
return const_iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::const_iterator HashMap<K, V, H, E>::cbegin() const{
	return const_iterator(L, L.cbegin());
}
/*
no param
construct Iterator with node pointer as property to element after last 
return Iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::end() {
	return iterator(L, L.end());
}
/*
no param
construct const_iterator with node pointer as property to element after last
return const_iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::const_iterator HashMap<K, V, H, E>::cend() const{
	return const_iterator(L, L.cend());
}
/*
1 param: K (const referance)
invoke finder()
checks if key exists
return Iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::find(const K& key) {
	iterator p = finder(key);
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
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::finder(const K& key) {
	int indice = hash(key) % L.size();
	ListIterator node = L.begin() + indice;
	iterator p(L, node);
	return p;
}
/*
2 params: iterator and node
inserts element at 
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::inserter(const iterator& p, const Node& x) {
	return iterator(L, L.insert(p.node, x));
}
/*
2 params: key nad value (constant references)
construct iterator and inserts new node
return Iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::insert(const K& key, const V& value) {
	iterator p = finder(key);
	int i = hash(key) % L.size();

	for ( i ; i < L.size(); ((i + 1) % L.size())) {
		if (!L[i].isAvailable() && testKeys(L[i].getKey(), key)) {
			iterator p(L, L.begin() + i); 
			(*p).setValue(value);
			return p;
		}
		if (L[i].isAvailable()) {
			iterator p(L, L.begin() + i);
			return inserter(p, Node(key, value, false));
		}
	} 
	//if i is above size
	return end(); 
}
/*
Node methods declaration
*/
template <typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::Node::setValue(const V& v) {
	this->value = v; 
}
template <typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::Node::setKey(const K& k) {
	this->key = k;
}
template <typename K, typename V, typename H, typename E>
V HashMap<K, V, H, E>::Node::getValue() {
	return value; 
}
template <typename K, typename V, typename H, typename E>
K HashMap<K, V, H, E>::Node::getKey() {
	return key;
}
template <typename K, typename V, typename H, typename E>
bool HashMap<K, V, H, E>::Node::isAvailable() {
	return available;
}
template <typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::Node::changeStatus() {
	available = !available;
}
