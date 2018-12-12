#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>


template <typename K>
class Hash {	/*good hash function*/
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
	struct Node {	//entry inside bucket
		Node(const K& k = K(), const V& v = V())
			: key(k), value(v) {}
		void setKey(const K& k) { key = k; };	
		void setValue(const V& v) { value = v; }
		K getKey() const { return key; };
		V getValue() const { return value; };
	private:
		K key;	//properties
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
		Node& operator*() const;	//access operator (return access to bucketIterator)
		bool operator==(const Iterator& p);	//checks if iterators are equal
		Iterator& operator++();	//move to next position in bucket or first nonempt buket
		friend class HashMap<K, V, H>;	//HashMap has access
	private:
		bucketIterator bucketPosition;	//bucket iterator
		arrayIterator arrayPosition;	//array iterator
		const Array* list;	//whole list
	};
public:
	/*public methods*/
	HashMap(int capacity = 101);	//prime number 
	int size() const;	//return size of elements
	bool isEmpty() const;	//return true if Map is empty
	Iterator insert(const K& key, const V& value);	//invoke inserter() or replace's value
	void erase(const K& key);	//invoke finder() and sends position to eraser()
	Iterator begin();	//set iterator to begining of first non empty bucket
	Iterator end();		//set iterator to one element after array
	Iterator find(const K& key);	//invoke finder() 
private:
	/*utility*/
	Iterator finder(const K& key);		//returns iterator to key's position
	Iterator inserter(const Iterator& p, const Node& element);	//insert's Node element at position p
	void eraser(const Iterator& p);	//erase bucketPosition on position p
	static bool endOfBucket(const Iterator& p);	
	static void nextNode(Iterator& p);

	int n; //number of elements
	Hash<K> hash;		//hash composition
	Array L;
};









int main()
{


	HashMap<std::string, int, Hash<std::string>> A;
	A.insert("a", 5);
	A.insert("b", 3);
	A.erase("aw2"); 
	
 








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
/*
return access to bucket position (Node)
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Node& HashMap<K, V, H>::Iterator::operator*() const {
	return *bucketPosition;
}
/*
move iterator's bucket position to next one
*/
template <typename K, typename V, typename H>
void HashMap<K, V, H>::nextNode(Iterator& p) {
	++p.bucketPosition;
}
/*
1 param: const referance to iterator
checks if bot lists are different and if position in bucket is diferent
if they are both at end of the list
if they refer to same bucket position
*/
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
/*
go to next bucke
if thats the end of bucket move to next bucket untill there is nonempty bucket
if end of list is reached, return end
else position is first Entry in bucket
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++() {
	++bucketPosition;	//go to next bucket
	if (endOfBucket(*this)) {	//if end is reached
		++arrayPosition; //move to next bucket
		while (arrayPosition != list.end() && arrayPosition->empty())
			++arrayPosition;	//traverse untill finde nonempty bucket
		if (arrayPosition != list->end())
			bucketPosition = arrayPosition->begin();
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
	int indice = hash(key) % L.size();	//get indice of array
	arrayIterator aItor = L.begin() + indice;	//position on indice in array
	Iterator p(L, aItor, aItor->begin());	//create iterator on list indice with bucket position to firsst item in bucket
	while (!endOfBucket(p)  && (*p).getKey() != key)
		nextNode(p); //traverse iterators's bucket iterator
	return p; //return that p
}

template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& key) {
	Iterator position = finder(key);
	if (!endOfBucket(position)) //if there is no souch ke
		return position;
	return end();	//go one after end
}

/*
replaces element's value
or 
inserts Node at given position by finder
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::insert(const K& key, const V& value) {
	Iterator position = finder(key);
	if (!endOfBucket(position)) {
		position.bucketPosition->setValue(value);
		return position;
	}
	return inserter(position, Node(key, value));
}
/*
inserts element at bucket and get position in bucketIterator
returns Iterator in array inside bucket where element is inserted
*/
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& p, const Node& element) {
	bucketIterator bItor = p.arrayPosition->insert(p.bucketPosition, element);
	n++;	//increment number of elements by 1
	return Iterator(L, p.arrayPosition, bItor);
}
/*
1 param: const referance to key
find key, if its end of the list, do nothing
else eraser() is invoked
*/
template <typename K, typename V, typename H>
void HashMap<K, V, H>::erase(const K& key) {
	Iterator position = finder(key);
	if (!endOfBucket(position)) {
		eraser(position);
		return;
	}
	std::cout << "Element not found";
}
/*
in array, erase bucketPosition
no return value
*/
template <typename K, typename V, typename H>
void HashMap<K, V, H>::eraser(const Iterator& p) {
	p.arrayPosition->erase(p.bucketPosition);
	n--;	//decrement size by 1
}
