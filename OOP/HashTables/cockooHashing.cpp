#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>


/*
COCKOO HASHING

insert : O(1)
delete : O(1)
search : O(1)
*/

template <typename K>
class HashOne {
public:
	size_t operator()(K key) {
		std::hash<K> a;
		return a(key);
	}
};

template <typename K>
class HashTwo {
public:
	size_t operator()(std::string key) {
		size_t hashValue = 0;
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

template <typename K, typename V, typename H1, typename H2>
class HashTable {
	enum status { ACTIVE, DELETED, EMPTY };

	struct Node {
		K key;
		V value;
		status current;

		Node(K k = K(), V val = V(), status c = EMPTY)
			:key(k), value(val), current(c) {}
	};

public:
	HashTable(int capacity = 7)
		:A(capacity), B(capacity), n(0) {}
	~HashTable();
	void insert(K key, V value);
	void erase(K key);
	void display();
	int find(const K& key); 

private:

	void rehash();

	static const int MAX_LOOP = 5;
	HashOne<K> hashOne;
	HashTwo<K> hashTwo;
	std::vector<Node> A;
	std::vector<Node> B;
	int n;
};

int nextPrime(int n);

bool isPrime(int x);


int main()
{


	HashTable <int, int, HashOne<int>, HashTwo<int>> A;
	for (int i = 0; i < 10; i++) {
		A.insert(rand() % 100, rand() % 100); 
	}


	A.display(); 


	return 0;
}
template <typename K, typename V, typename H1, typename H2>
HashTable<K, V, H1, H2>::~HashTable() {
	B.clear(); 
	A.clear(); 
}
/*
1 param: Key object
check in first table
check in second table
return -1 if not found
*/
template <typename K, typename V, typename H1, typename H2>
int HashTable<K, V, H1, H2>::find(const K& key) {
	
	unsigned int indice = hashOne(key) % A.size();	//indice within first table

	if (A[indice].current != EMPTY && A[indice].key != key) {	//if keys are diferent

		indice = hashTwo(key) % B.size();	//go to second table
		if (B[indice].current != EMPTY && B[indice].key != key)
			return -1;	//return -1 if not found

		std::cout << B[indice].key << " : " << B[indice].value; 
		return indice;
	}
	std::cout << A[indice].key << " : " << A[indice].value;
	return indice;
}
/*
1 param: Key objet
check in both tables
delete if find
no return value
*/
template <typename K, typename V, typename H1, typename H2>
void HashTable<K, V, H1, H2>::erase(K key) {

	if (A[hashOne(key) % A.size()].key != key) {

		if (B[hashOne(key) % B.size()].key != key) {
			std::cout << "ELEMENT NOT FOUND";
			return;
		}
		B[hashOne(key) % B.size()].current = DELETED;
		return;
	}
	A[hashOne(key) % A.size()].current = DELETED;
}

template <typename K, typename V, typename H1, typename H2>
void HashTable<K, V, H1, H2>::insert(K key, V value) {
	int i = MAX_LOOP;
	while (i > 0) {
		if (A[hashOne(key) % A.size()].current != ACTIVE) {	//if element in left side is empty
			/*insert there and return*/
			A[hashOne(key) % A.size()].key = key;
			A[hashOne(key) % A.size()].value = value;
			A[hashOne(key) % A.size()].current = ACTIVE;
			return;
		}
		std::swap(key, A[hashOne(key) % A.size()].key);
		std::swap(value, A[hashOne(key) % A.size()].value);

		if (B[hashOne(key) % B.size()].current != ACTIVE) {//if element in right side is empty
			/*insert there and return*/
			B[hashOne(key) % B.size()].key = key;
			B[hashOne(key) % B.size()].value = value;
			B[hashOne(key) % B.size()].current = ACTIVE;
			return;
		}
		std::swap(key, B[hashOne(key) % B.size()].key);
		std::swap(value, B[hashOne(key) % B.size()].value);

		++n; --i; 
	}
	rehash();
	insert(key, value);
}

template <typename K, typename V, typename H1, typename H2>
void HashTable<K, V, H1, H2>::rehash() {
	A.resize(nextPrime(A.size() * 2));
	B.resize(nextPrime(B.size() * 2));
}

template <typename K, typename V, typename H1, typename H2>
void HashTable<K, V, H1, H2>::display() {	/*display tables*/
	for (int i = 0; i < A.size(); i++) {
		std::cout << "\n" << A[i].key << " : " << A[i].value << "   |   " << B[i].key << " : " << B[i].value << "\n";
	}

}

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


