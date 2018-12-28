#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

/*
search : O(1)	- worst O(N)
insert : O(1)	- worst O(N)
delete : O(1)	- worst O(N)

space : O(N)
*/

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
class HashTable {

	enum Status { ACTIVE, DELETED, EMPTY };

	struct Node {
		K key;
		V value;
		Status type;

		Node(const K& k = K(), const V& val = V(), Status t = EMPTY)
			: key(k), value(val), type(t) {}
		Node(Node&& x, Status t = EMPTY)
			: key(std::move(x.key)), value(std::move(x.value)), type(t) {}
	};
public:
	HashTable(int capacity = 101);
	HashTable(const HashTable& x);
	~HashTable();
	bool contains(const K& key) const;
	void clear();
	void insert(const K& key, const V& value);
	void remove(const K& key);
	void search(const K& key);
	void display() {	//check hash table
		for (int i = 0; i < elements; i++)
			std::cout << i + 1 << ". " << List[i].key << " : " << List[i].value << "\n";

		std::cout << "colisions: " << colisions << "\n"; 
	}
private:
	bool isActive(int currentPosition) const;
	int findPosition(const K& key);
	void resize();

	int elements;
	std::vector<Node> List;
	Hash<K> hash;
	EqualKeys<K> areEqual;
	int colisions; 
};




bool isPrime(int x);

int nextPrime(int n);

int main()
{

	HashTable<int, int, Hash<int>, EqualKeys<int>> a;


	for (int i = 0; i < 50; i++) {
		a.insert(rand() % 100, i + 1);
	}

	a.display(); 







	return 0;
}
/*
constructor
1 param : int	(prime number prefer)
init List
*/
template <typename K, typename V, typename H, typename E>
HashTable<K, V, H, E>::HashTable(int capacity)
	: List(capacity), elements(0), colisions(0) {}

template <typename K, typename V, typename H, typename E>
HashTable<K, V, H, E>::HashTable(const HashTable& x)
	: elements(x.elements) {
	List = std::move(x.List);
}

template <typename K, typename V, typename H, typename E>
HashTable<K, V, H, E>::~HashTable() {
	clear();
	elements = 0;
}
/*
no param
check all nodes as empty
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashTable<K, V, H, E>::clear() {
	for (auto& node : List)
		node.type = EMPTY;
	elements = 0;
}

/*
1 param: const referance to key object
search for empty indice or indice with equal key
return int
*/
template <typename K, typename V, typename H, typename E>
int HashTable<K, V, H, E>::findPosition(const K& key) {

	int offset = 1;
	int indice = hash(key) % List.size();
	/* search while List indice is not EMPTY and while keys are not the same */
	while (List[indice].type != EMPTY && List[indice].key != key) {
		++colisions; 
		/* quadratic resolution: f(i) = f(i - 1) + 2i - 1*/
		indice += offset;
		offset += 2;
		if (indice < List.size())
			continue;
		indice -= List.size();
	}
	return indice;
}
/*
1 param: const referance to Key object
invoke isAtive(findPosition(Key))
return bool
*/
template <typename K, typename V, typename H, typename E>
bool HashTable<K, V, H, E>::contains(const K& key) const {
	return isActive(findPosition(key));
}
/*
1 param: int
check if Node is ACTIVE
return bool
*/
template <typename K, typename V, typename H, typename E>
bool HashTable<K, V, H, E>::isActive(int i) const {
	return List[i].type == ACTIVE;
}
/*
2 params: const referance to Key and Value object
find empty position or position with equal key
if already active, do nothing
insert new element and set it to ACTIVE
check if need to resize
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashTable<K, V, H, E>::insert(const K& key, const V& value) {
	int currentPosition = findPosition(key);
	if (!isActive(currentPosition)) {
		List[currentPosition].key = key;
		List[currentPosition].value = value;
		List[currentPosition].type = ACTIVE;

		if (++elements > List.size() / 2)
			resize();
		return;
	}
}
/*
1 param: const referance to Key object
take indice with key
if not ACTIVE, do nothing
else change status to DELETED
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashTable<K, V, H, E>::remove(const K& key) {
	int currentPosition = findPosition(key);
	if (!isActive(currentPosition)) {
		std::cout << "Element empty";
		return;
	}
	List[currentPosition].type = DELETED;
}
/*
1 param: const referance to Key object
finds and cout Node info
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashTable<K, V, H, E>::search(const K& key) {
	int indice = findPosition(key);
	std::cout << List[indice].key << " : " << List[indice].value;
}

/*
no param
resize vector at first higher prime number
no return value
*/
template <typename K, typename V, typename H, typename E>
void HashTable<K, V, H, E>::resize() {
	List.resize(nextPrime(List.size() * 2));
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
