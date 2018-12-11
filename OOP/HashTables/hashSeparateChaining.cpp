#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>

template <typename K>
class Hash {
public:
	unsigned int operator()(const std::string& key) {
		unsigned int hashValue = 0; 
		for (char ch : key) {
			hashValue = 37 * hashValue + ch; 
		}
		return hashValue;
	}
};

template <typename K, typename V, typename H>
 class HashMap {

	class Node {
	public:
		Node(const K& k = K(), const V& v = V())
			:	key(k), value(v) {}
		void setKey(const K& k) { key = k;  };
		void setValue(const V& v) { value = v;  }
		K getKey() const { return key;  };
		V getValue() const { return value;  };
	private:
		K key;
		V value;
	};
	typedef typename Node Node;
	typedef typename std::list<Node> Bucket;
	typedef typename std::vector<Bucket> Array;
	typedef typename Bucket::iterator bucketIterator;
	typedef typename Array::iterator arrayIterator;
 public:
	 class Iterator {
	 public:
		 Iterator(const Array& a, const arrayIterator& ator, const bucketIterator& btor = bucketIterator())
			 : bucketPosition(btor), arrayPosition(ator), list(&a) {};
		 Node& operator*() const;
		 bool operator==(const Iterator& p); 
		 Iterator& operator++(); 
		 friend class HashMap<K, V, H>; 
	 private:
		 bucketIterator bucketPosition;
		 arrayIterator arrayPosition; 
		 const Array* list; 
	 };
 public:
	 /*public methods*/
	 HashMap(int capacity = 101); 
	 int size() const; 
	 bool isEmpty() const;
	 Iterator insert(const K& key, const V& value);
	 void erase(const K& key);
	 Iterator begin(); 
	 Iterator end(); 
	 Iterator find(const K& key); 
private:
	/*utility*/
	Iterator finder(const K& key);
	Iterator inserter(const Iterator& p, const Node& element);
	void eraser(const Iterator& p); 
	static bool endOfBucket(const Iterator& p); 
	static void nextNode(Iterator& p);

	int n; //number of elements
	Hash<K> hash;		//hash composition
	Array L; 
};

 template <typename K, typename V, typename H>
 typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::insert(const K& key, const V& value) {
	 Iterator position = finder(key); 
	 if (!endOfBucket(position)) {
		 position.bucketPosition->setValue(value);
		 return position;
	 }
	 return inserter(position, Node(key, value));
 }

 template <typename K, typename V, typename H>
 typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& p, const Node& element) {
	 bucketIterator bItor = p.arrayPosition->insert(p.bucketPosition, element); 
	 n++; 
	 return Iterator(L, p.arrayPosition, bItor); 
 }





 

int main()
{


	HashMap<std::string, int, Hash<std::string>> A; 
	A.insert("a", 5); 
	A.insert("b", 3); 









	return 0;
}


template <typename K, typename V, typename H>
HashMap<K, V, H>::HashMap(int capacity)
	: L(capacity), n(0) {}

template <typename K, typename V, typename H>
int HashMap<K, V, H>::size() const {
	return n;
}
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::isEmpty() const {
	return (n == 0);
}
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Node& HashMap<K, V, H>::Iterator::operator*() const{
	return *bucketPosition;
}

template <typename K, typename V, typename H>
void HashMap<K, V, H>::nextNode(Iterator& p) {
	++p.bucketPosition;
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator==(const Iterator& operand) {
	if (list != operand.list || bucketPosition != operand.bucketPosition)
		return false;
	else if (arrayPosition == list->end()) 
		return true;
	else 
		return (arrayPosition == operand.arrayPosition);
}

template <typename K, typename V, typename H>
bool HashMap<K, V, H>::endOfBucket(const Iterator& p) {
	return (p.bucketPosition == p.arrayPosition->end());
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++() {
	++bucketPosition;	//go to next bucket
	if (endOfBucket(*this)) {	//if end is reached
		++arrayPosition; //move to next bucket
		while (arrayPosition != list.end() && arrayPosition->empty())
			++arrayPosition;	//traverse untill finde nonempty bucket
		if (arrayPosition != list->end())
			bucketPosition = arrayPosition->begin();
		return *this;
	}
	return *this;
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin() {
	if (!isEmpty()) {	//if list is empty
		arrayIterator position = L.begin(); //set iterator to begining of list
		while (position->empty())
			++position;	//traverse untill bucket is non empty
		return Iterator(L, position, position->begin());	//return iterator to first node in that bucket
	}
	return end();	//return end of the list
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::end() {
	return Iterator(L, L.end());
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::finder(const K& key) {
	int indice = hash(key) % L.size();	//get indice of arrat
	arrayIterator aItor = L.begin() + indice;	//position on indice in array
	Iterator p(L, aItor, aItor->begin());	//create iterator on list indice with bucket position to firsst item in bucket
	while ((*p).getKey() != key || endOfBucket(p))
		nextNode(p); //traverse iterators's bucket iterator
	return p; //return that p
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& key) {
	Iterator position = finder(position);
	if (!endOfBucket(position)) //if there is no souch ke
		return position;
	return end();	//go one after end
}
