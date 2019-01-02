#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>


template <typename K, typename V>
class Tree {
	struct Node {
		K key; 
		V value; 
		int height; 

		Node* left; 
		Node* right;

		Node(const K& k, const V& val, Node* lft, Node* rgt, int h = 0)
			:key(k), value(val), left(lft), right(rgt), height(h) {}
		int getHeight(Node* spot) const {
			return (spot == nullptr) ? -1 : spot->height; 
		}
	};

public:
	Tree();
	void insert(const K& key, const V& value); 
	void remove(const K& key); 
	bool contains(const K& key) const;

private:
	/*utility methods*/
	void insert(const K& key, const V& value, Node*& spot); 
	void remove(const K& key, Node*& spot); 
	bool contains(const K& key, Node* root) const; 
	Node* findMin(Node*& root) const; 
	void balance(Node*& spot) {
		if (spot == nullptr) {
			return; 
		}

		
	}


	static const int ALOWED_IMBALANCE = 1; 
	Node* root; 
	int n; 
};








int main()
{

	
	Tree<int, int> A; 
	A.insert(1, 2); 
	A.insert(5, 1); 
	A.remove(5); 





	return 0;
}
template <typename K, typename V>
Tree<K, V>::Tree()
	:root(nullptr), n(0) {}

template <typename K, typename V>
void Tree<K, V>::insert(const K& key, const V& value) {
	insert(key, value, root);
}

template <typename K, typename V>
void Tree<K, V>::remove(const K& key) {
	remove(key, root);
}

template <typename K, typename V>
bool Tree<K, V>::contains(const K& key) const {
	contains(key, root);
}
/*
@params: key, value, node
recursive calls until nullptr node
inserts new Node
*/
template <typename K, typename V>
void Tree<K, V>::insert(const K& key, const V& value, Node*& spot) {
	if (spot != nullptr) {
		if (key > spot->key)
			insert(key, value, spot->right);
		else if (key < spot->key)
			insert(key, value, spot->left);
		else
			return;
	}
	++n; 
	spot = new Node(key, value, nullptr, nullptr);
	balance(spot); 
}
/*
@params: key, node
recursive calls untill searched key
return true if finds
false othewise
*/
template <typename K, typename V>
bool Tree<K, V>::contains(const K& key, Node* root) const {
	if (root != nullptr) {
		if (key > root->key)
			return contains(key, root->right);
		else if (key < root->key)
			return contains(key, root->left);
		else
			return true;
	}
	return false;
}
/*
@params: key, node
if node is nullptr, do nothing
recursive calls untill searched node
if middle of tree, take minimum from right subtree
remove minimum from subtree
*/
template <typename K, typename V>
void Tree<K, V>::remove(const K& key, Node*& spot) {
	if (spot == nullptr) {
		return;
	}
	if (spot->key < key)
		remove(key, spot->right);
	else if (spot->key > key)
		remove(key, spot->left);
	else if (spot->left != nullptr && spot->right != nullptr) {
		spot->value = findMin(spot->right)->value;
		remove(spot->value, spot->right);
	}
	else {
		Node* oldNode = spot;
		spot = (spot->left != nullptr) ? spot->right : spot->left;
		delete oldNode;
	}

}

template <typename K, typename V>
typename Tree<K, V>::Node* Tree<K, V>::findMin(Node*& spot) const {
	if (spot->left == nullptr) {
		return spot;
	}
	return findMin(spot->left);
}
