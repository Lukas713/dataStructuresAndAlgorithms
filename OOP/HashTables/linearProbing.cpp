#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>


template <typename K>
class Hash {
public:
	unsigned int operator()(std::string key) {
		unsigned int hashValue = 0;
		for (char ch : key)
			hashValue = 37 * hashValue + ch;
		return hashValue;
	}

	unsigned int operator()(unsigned int key) {
		key = ((key >> 16) ^ key) * 0x45d9f3b;
		key = ((key >> 16) ^ key) * 0x45d9f3b;
		key = (key >> 16) ^ key;
		return key;
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
		Node(const Node& x);
		void setValue(const V& v);
		void setKey(const K& k);
		K getKey();
		V getValue();
		bool isAvailable();	//checks flag
	};
	typedef typename Node Node;
	typedef typename std::vector<Node> List;
	typedef typename List::iterator ListIterator;
public:
	class iterator {
	public:
		iterator(const List& l = List(), const ListIterator& p = ListIterator())
			:node(p), list(&l) {}
		iterator(const iterator& p)
			:node(p.node), list(p.list) {}
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

public:
	/*public methods*/
	HashMap(int capacity = 101)
		: L(capacity), n(0), colisions(0) {}
	HashMap(const HashMap& x)
		: n(x.n), L(std::move(x.L)), colisions(0) {}
	HashMap(HashMap&& x)
		: n(x.n), L(std::move(x.L)), colisions(0) {}
	~HashMap();
	int size() const;
	bool isEmpty() const;
	iterator insert(const K& key, const V& value);
	iterator find(const K& key);
	void erase(const K& key);
	iterator begin();
	iterator end();
	void display();
private:
	/*utility methods*/
	iterator finder(const K& key);
	void eraser(iterator& position);
	bool endOfArray(const iterator& position) const;
	void resize(int capacity);

	/*HashMap properties*/
	std::vector<Node> L;
	int n;	//number of elements in the list
	Hash<K> hash;
	EqualKeys<K> testKeys;
	int colisions; 
};

/*find next prime number for resize()*/
bool isPrime(int x);

int nextPrime(int n);

int prevPrime(int n);

int main()
{


	HashMap <int, int, Hash<int>, EqualKeys<int>> a;

	for (int i = 0; i < 100; i++) {
		a.insert(rand() % 100, rand() % 100);
	}



	a.display();













	return 0;
}
template <typename K, typename V, typename H, typename E>
HashMap<K, V, H, E>::~HashMap() {
	L.clear();
	n = 0;
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
access operator overload
access to node iterator property
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::Node& HashMap<K, V, H, E>::iterator::operator*() {
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
construct Iterator with node pointer as property to element after last
return Iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::end() {
	return iterator(L, L.end());
}


/*
2 params: key nad value (constant references)
construct iterator and inserts new node
return iterator object
*/
template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::insert(const K& key, const V& value) { 
	if (n > (L.size() / 2)) {	//if half of vector is full
		resize(nextPrime(L.size() * 2));	//set to next prime that is twice as big as last one
	}

	unsigned int i = hash(key) % L.size();
	if (!L[i].isAvailable() && !testKeys(L[i].getKey(), key)) {
		++colisions; 
	}

	for (i; i < L.size(); (i += 1) % L.size()) {
		if (!L[i].isAvailable() && testKeys(L[i].getKey(), key)) { //node with key and value is already inserted
			iterator p(L, L.begin() + i);
			(*p).setValue(value);
			return p;
		}
		if (L[i].isAvailable()) {	//find spot that is available
			Node temp = Node(key, value, false);
			L[i] = temp;
			iterator p(L, L.begin() + i);
			n++;
			return p;
		}
	}
	 
	return end();
}
/*
1 param: int
dinamic alocation of new HashMap
inserts elements from first array into second one
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::resize(int capacity) {
	L.resize(capacity);
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
	for (p; !(*p).isAvailable(); ++p) {
		if ((*p).getKey() != key)
			continue;
		return p;
	}
	return end();
}

template <typename K, typename V, typename H, typename E>
typename HashMap<K, V, H, E>::iterator HashMap<K, V, H, E>::find(const K& key) {
	iterator p = finder(key);
	if (!endOfArray(p)) {
		return p;
	}
	std::cout << "\nNo element\n";
	return end();
}

/*
1 param: key const referance
if no in array, error occur
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::erase(const K& key) {
	iterator p = finder(key);
	if (!endOfArray(p)) {
		return eraser(p);
	}
	std::cout << "Element not found \n";
}
/*
1 param: iterator position
erase element
reinserts rest of cluster
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::eraser(iterator& position) {
	iterator p(position);	//create iterator on position 
	++p;	//move to next node
	*position.node = Node(); //reconstruct node at given position
	while (!(*p).isAvailable()) {	//while next node's are in cluster
		K key = (*p).getKey();	//take values
		V value = (*p).getValue();
		iterator temp(p); //construct temporary iterator
		++p; //move to next one
		*temp.node = Node(); //reconstruct temporary
		n--;
		insert(key, value); //insert node with values
	}
	n--;
	if (n > 0 && n <= (L.size() / 8)) {
		resize(prevPrime(L.size()));	//next prime that is twice as large 
	}
}
template <typename K, typename V, typename H, typename E>
void HashMap<K, V, H, E>::display() {	//print whole table
	for (unsigned int i = 0; i < L.size(); i++) {
		if (!L[i].isAvailable())
			std::cout << i + 1 << ". " << L[i].getKey() << " : " << L[i].getValue() << " \n";
	}

	std::cout << "colisions: " << colisions << "\n"; 
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
HashMap<K, V, H, E>::Node::Node(const Node& x)
	: value(x.value), key(x.key), available(x.available) {}

/*find next prime number*/
bool isPrime(int x) {
	for (int i = 2; i < x; i++) {
		if (x % i == 0) {
			return false;
		}
	}
	return true;
}

int nextPrime(int n) {
	while (!isPrime(++n));
	return n;
}

int prevPrime(int n) {
	int x = n;
	while (!isPrime(--x));
	if (x < 3) {
		return n;
	}
	return x;
}

