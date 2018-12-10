#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <vector>


template <typename hashedOBJ>
class HashTable {
public:
	HashTable(int size = 101);
	bool contains(const hashedOBJ& me) const; 

	void makeEmpty();
	bool insert(const hashedOBJ& x); 
	bool insert(hashedOBJ&& rvalue); 
	bool remove(const hashedOBJ& x); 

private:
	std::vector<std::list<hashedOBJ>> list;		//array of lists
	int currentSize; 
	
	void rehash(); 
	size_t myhash(const hashedOBJ& o) const; 
};



/*
polynomial hash fnction 

size_t represents size of the object
A class that implements a hash table algorithm can then use calls
to the generic hash function object to generate an
integral type size_t and then scale the result into a suitable array index. In hash tables,
this is manifested in private member function myhash
*/
template <typename T>
class hash {
public:
	size_t operator()(const std::string& key) {
		size_t hashVal = 0; 

		for (char ch : key) 
			hashVal = 37 * hashVal + ch; 
		return hashVal; 
	}
};




int main()
{
	

	HashTable<std::string> a; 
	a.insert("Lukas"); 
	




	return 0;
}
template <typename hashedOBJ>
size_t HashTable<hashedOBJ>::myhash(const hashedOBJ& o) const {
	hash<hashedOBJ> hf;
	return hf(o) % list.size();	//construct hash and insert in list 
}
template <typename hashedOBJ>
void HashTable<hashedOBJ>::makeEmpty() {
	for (auto& theList : list) {	//remove's all lists from buckets
		list.clear();
	}
}
template <typename hashedOBJ>
bool HashTable<hashedOBJ>::contains(const hashedOBJ& me) const {
	auto& whichList = list[myhash(me)];		//construct hash with argumented object, catch bucket
	return std::find(std::begin(whichList), std::end(whichList), me) != end(whichList);
}
template <typename hashedOBJ>
bool HashTable<hashedOBJ>::remove(const hashedOBJ& obj) {
	auto& tempList = list[myhash(obj)];
	auto& iterator = std::find(std::begin(tempList), std::end(tempList), obj);

	if (iterator == std::end(tempList)) {
		std::cout << "\nElement not found!\n";
		return false;
	}
	tempList.erase(iterator);
	currentSize--;
	return true;
}
template <typename hashedOBJ>
void HashTable<hashedOBJ>::rehash() {
	std::vector<std::list<hashedOBJ>> oldList = list;
	list.resize(2 * list.size());

	for (auto & lists : list) {
		list.clear();
	}
	/*copy table over*/
	currentSize = 0;
	for (auto& thisList : oldList) {
		for (auto& x : thisList) {
			insert(std::move(x));
		}
	}
}
template <typename hashedOBJ>
bool HashTable<hashedOBJ>::insert(const hashedOBJ& x) {
	auto& tempList = list[myhash(x)];
	if (std::find(std::begin(tempList), std::end(tempList), x) != std::end(tempList))
		return false;
	list.push_back(x);

	if (++currentSize > list.size()) {
		rehash();
	}
	return true;
}
