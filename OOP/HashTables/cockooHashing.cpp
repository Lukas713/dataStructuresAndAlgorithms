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
};

template <typename K, typename V, typename H1, typename H2>
class HashTable {
	enum status { ACTIVE, DELETED, EMPTY }; 

	struct Node {
		K key; 
		V value; 
		status current; 

		Node( K k = K(), V val = V(), status c = EMPTY)
			:key(k), value(val), current(c) {}
	};

public:
	HashTable(int capacity = 7)
		:A(capacity), B(capacity), n(0) {}

	void insert(K key, V value); 
	void erase(K key); 
	void display() {	/*checker*/
		for (int i = 0; i < A.size(); i++) {
			std::cout << i + 1 << ". " << A[i].key << " : " << A[i].value; 
			std::cout << "\n"; 
		}
		std::cout << "\n"; 
		for (int i = 0; i < B.size(); i++) {
			std::cout << i + 1 << ". " << B[i].key << " : " << B[i].value;
			std::cout << "\n";
		}
	}

private:
	int findPosition(const K& key); 
	void rehash();

	static const int MAX_LOOP = 5; 
	HashOne<K> hashOne; 
	HashTwo<K> hashTwo;
	std::vector<Node> A; 
	std::vector<Node> B; 
	int n; 
};





int main()
{
 


	HashTable <std::string, int, HashOne<std::string>, HashTwo<std::string>> A; 
	A.insert("a", 3); 
	A.insert("x", 6); 
	A.insert("b", 12); 
	A.insert("c", 15); 
	A.insert("s", 19); 
	A.insert("r", 41); 
	A.insert("n", 1); 
	A.display(); 




	return 0;
}
template <typename K, typename V, typename H1, typename H2>
int HashTable<K, V, H1, H2>::findPosition(const K& key) {
	unsigned int indice = hashOne(key) % A.size();
	if (A[indice].current != EMPTY && A[indice].key != key) {
		indice = hashTwo(key) % B.size();
		if (B[indice].current != EMPTY && B[indice].key != key)
			return -1;
		return indice;
	}
	return indice;
}

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
		if (A[hashOne(key) % A.size()].current == EMPTY) {
			A[hashOne(key) % A.size()].key = key;
			A[hashOne(key) % A.size()].value = value;
			A[hashOne(key) % A.size()].current = ACTIVE;
			return;
		}
		key = A[hashOne(key) % A.size()].key;
		value = A[hashOne(key) % A.size()].value;

		if (B[hashOne(key) % B.size()].current == EMPTY) {
			B[hashOne(key) % B.size()].key = key;
			B[hashOne(key) % B.size()].value = value;
			B[hashOne(key) % B.size()].current = ACTIVE;
			return;
		}
		key = B[hashOne(key) % B.size()].key;
		value = B[hashOne(key) % B.size()].value;
	}
	rehash();
	insert(key, value);
}

bool isPrime(int x);

int nextPrime(int n);

template <typename K, typename V, typename H1, typename H2>
void HashTable<K, V, H1, H2>::rehash() {
	A.resize(nextPrime(A.size() * 2));
	B.resize(nextPrime(B.size() * 2));
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


