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
		Node(const K& k = K(), const V& v = V())
			:key(k), value(v) {}
		void setValue(const V& v) { value = v;  };
		void setKey(const K& k) { key = k;  };
		K getKey() { return key;  };
		V& getValue();
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
	bool endOfArray(const Iterator& p) {
		return (p.node == p.list->end()); 
	}
private:
	/*utility methods*/
	Iterator finder(const K& key);
	Iterator inserter(const Iterator& p, const Node& n); 


	/*HashMap properties*/
	std::vector<Node> L; 
	int n;	//number of elements in the list
	Hash<K> hash; 
};

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& key) {
	Iterator p = finder(key);
	if (p.node != L.end())
		return p;
	return end();
}

template <typename K, typename V, typename H>
typename HashMap<K,V,H>::Iterator HashMap<K, V, H>::finder(const K& key) {
	int indice = hash(key) % L.size(); 
	ListIterator node = L.begin() + indice; 
	Iterator p(L, node); 
	return p; 
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& p, const Node& x) {
	ListIterator a = p.node; 
	a = L.insert(a, x); 
	return Iterator(L, a); 
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::insert(const K& key, const V& value) {
	Iterator p = finder(key);
	if (!endOfArray(p)) {
		for (p; p != end(); ++p) {
			if ((*p).getKey() == "")
				return inserter(p, Node(key, value));

			if ((*p).getKey() == key) {
				(*p).setValue(value);
				return p;
			}
			if (p == (begin())) {
				std::cout << " da"; 
			}
		}
	}
	return end(); 
}


template <typename K, typename V>
struct Node {
	K key;
	V value;
	Node(const K& k = K(), const V& v = V())
		:key(k), value(v) {}
	void setValue(const V& v);
	void setKey(const K& k);
	K getKey() { return key; };
	V& getValue() { return value;  }
};
int main()
{
	
	HashMap<std::string, int, Hash<std::string>> f; 
	HashMap<std::string, int, Hash<std::string>>::Iterator p = f.begin();
	f.insert("dd", 1); 
	 
	
	





	return 0;
}

template <typename K, typename V, typename H>
int HashMap<K, V, H>::size() const {
	return n;
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::isEmpty() const {
	return n == 0;
}
/*Iterator methods*/
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator==(const Iterator& p) const {
	if (list != p.list)
		return false;
	return (node == p.node);
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator!=(const Iterator& p) const {
	if (list != p.list)
		return false;
	return (node != p.node);
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++() {
	++node;
	return *this; 
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Node& HashMap<K, V, H>::Iterator::operator*() {
	return *node;
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin() {
	return Iterator(L, L.begin());
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::end() {
	return Iterator(L, L.end());
}


