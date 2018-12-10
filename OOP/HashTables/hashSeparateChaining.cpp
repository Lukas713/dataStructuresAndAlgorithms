#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <map>
#include <limits>
#include <vector>


template <typename K, typename V, typename H>
class HashMap {
public:
	class Entry {
		const K key;
		V value;
	};
	class Iterator; 
public:
	HashMap(int size = 101);  // prime number
	int size() const; 
	bool isEmpty() const; 
	Iterator find(const K& key); 
	Iterator put(const K& key, const V& value); 
	void erase(const K& key); 
	void erase(const Iterator& key); 
	Iterator begin(); 
	Iterator end(); 
protected:
	typedef std::list<Entry> Bucket; 
	typedef std::vector<Bucket> List; 
	Iterator finder(const K& k); 
	Iterator insert(const Iterator& p, const Entry& e); 
	void eraser(const Iterator& p); 
	typedef typename Bucket::iterator BItor; //buket iterator
	typedef typename List::iterator EItor; //list iterator
	void nextEntry(Iterator& p) {
		++p.ent; 
	}
	bool endOfBkt(const Iterator& p) {
		return (p.ent == p.bkt->end()); 
	}
private:
	int n; 
	H hash; 
	List B; 
public:
	class Iterator {
	private:
		BItor bkt;
		EItor ent;
		const List* L; 
	public:
		Iterator(const List& list, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), L(&list) {}; 
		Entry& operator*() const; 
		bool operator==(const Iterator& p) const;
		Iterator& operator++(); 
		friend class HashMap<K,V,H>; 
	};
};




int main()
{
	

	
	





	return 0;
}

