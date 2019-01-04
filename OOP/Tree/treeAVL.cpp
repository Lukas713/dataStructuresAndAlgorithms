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

	};

public:
	Tree();
	void insert(const K& key, const V& value);
	void remove(const K& key);
	bool contains(const K& key) const;
	void preorder() {
		preorder(root); 
	}

private:
	/*utility methods*/
	void insert(const K& key, const V& value, Node*& spot);
	void remove(const K& key, Node*& spot);
	bool contains(const K& key, Node* root) const;
	Node* findMin(Node*& root) const;
	void rotateWithLeftChild(Node*& spot);
	void rotateWithRightChild(Node*& spot);
	void doubleWithLeftChild(Node*& spot);
	void doubleWithRightChild(Node*& spot);
	void balance(Node*& spot);
	int height(Node* spot) const;
	void preorder(Node* root);



	static const int ALOWED_IMBALANCE = 1;
	Node* root;
	int n;
};



int main()
{


	Tree<int, int> A;
	A.insert(9, 1);
	A.insert(7, 3); 
	A.insert(5, 6); 
	A.insert(1, 34); 
	A.insert(2, 0); 
	A.preorder(); 





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
	return contains(key, root);
}
/*
@params: key, value, node
recursive calls until nullptr node
inserts new Node
*/
template <typename K, typename V>
void Tree<K, V>::insert(const K& key, const V& value, Node*& spot) {
	if (spot == nullptr) {
		++n;
		spot = new Node(key, value, nullptr, nullptr);
	}
	else if (key > spot->key)
		insert(key, value, spot->right);
	else if (key < spot->key)
		insert(key, value, spot->left);

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
	if (spot == nullptr) 
		return;
	
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
	balance(spot);
}

template <typename K, typename V>
typename Tree<K, V>::Node* Tree<K, V>::findMin(Node*& spot) const {
	if (spot->left == nullptr) 
		return spot;
	
	return findMin(spot->left);
}

/*
@param: referance to Node pointer
cheks where is violation
calls propertly rotation method
no return value
*/
template <typename K, typename V>
void Tree<K, V>::balance(Node*& spot) {
	if (spot != nullptr) {
		if (height(spot->left) - height(spot->right) > ALOWED_IMBALANCE) { //if violation is on left child
			if (height(spot->left->left) >= height(spot->left->right))	//left-left violation
				rotateWithLeftChild(spot);
			else  //left-right violation
				doubleWithLeftChild(spot);
		}
		else {
			if (height(spot->right) - height(spot->left) > ALOWED_IMBALANCE) { //if violation is on right child	
				if (height(spot->right->right) >= height(spot->right->left))//right-right violation
					rotateWithRightChild(spot);
				else  //right-left violation
					doubleWithRightChild(spot);
			}
		}
		spot->height = std::max(height(spot->left), height(spot->right)) + 1;
	}
}

/*
@param: pointer to Node
return -1 if spot is nullptr and return height if not
return int
*/
template <typename K, typename V>
int Tree<K, V>::height(Node* spot) const {
	return (spot == nullptr) ? -1 : spot->height;
}
/*
@param referance to Node pointer
creates Node and rotates it with root node
root node's left becomes temps right
temp's right becomes root node
*/
template <typename K, typename V>
void Tree<K, V>::rotateWithLeftChild(Node*& spot) {
	Node* temp = spot->left;
	spot->left = temp->right;
	temp->right = spot;
	spot->height = std::max(height(spot->left), height(spot->right)) + 1;
	temp->height = std::max(height(temp->left), height(spot)) + 1;
	spot = temp;
}
/*
@param referance to Node pointer
creates Node and rotates it with root node
root node's right becomes temps left
temp's left becomes root node
*/
template <typename K, typename V>
void Tree<K, V>::rotateWithRightChild(Node*& spot) {
	Node* temp = spot->right;
	spot->right = temp->left;
	temp->left = spot;
	spot->height = std::max(height(spot->right), height(spot->left)) + 1;
	temp->height = std::max(height(temp->right), height(spot)) + 1;
	spot = temp;
}
/*
@param: referance to Node pointer
first right rotation
then left rotation
no return value
*/
template <typename K, typename V>
void Tree<K, V>::doubleWithLeftChild(Node*& spot) {
	rotateWithRightChild(spot->left);
	rotateWithLeftChild(spot);
}
/*
@param: referance to Node pointer
first left rotation
then right rotation
no return value
*/
template <typename K, typename V>
void Tree<K, V>::doubleWithRightChild(Node*& spot) {
	rotateWithLeftChild(spot->right);
	rotateWithRightChild(spot);
}
/*
@param: root node
preorder traversal
traverses root first, then next node's
no return value
*/
template <typename K, typename V>
void Tree<K, V>::preorder(Node* p) {
	if (p == nullptr)
		return;
	std::cout << p->key << " : " << p->value << "\n";
	preorder(p->left);
	preorder(p->right);
}
