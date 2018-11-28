#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

/*
terminology:
	node with links that either null or references to other nodes.
	node is pointed to by just one other node, parent.
	node has two links, referance to left child and right child.
	each link is pointing to binary tree, whose root is referenced node.

definition:
	Binary search tree (BST) is a binary tree where each node has comparable key with associated value
	and satisfies the restriction that the key in any node is larger then keys in all node's LEFT
	subtree, and smaller then the keys in all nodes in the node's right subtree.
*/
template <typename Value, typename Key>
class Tree {

	struct  Node
	{
		Value value;
		Key key;
		Node* left; //link to left child
		Node* right;	//lin to right child
		Node(Key k, Value v, Node* lft, Node* rgt)
			: key(k), value(v), left(lft), right(rgt) {};
		Node(Key&& k, Value&& v, Node* lft, Node* rgt)
			: key(std::move(k)), value(std::move(v)), left(lft), right(rgt) {};
		Node& operator=(Node t); 
	};

	Node* root; //root node

	Node* clone(Node* root) const; //invoked by copy constructor
	Node* getElement(Key key, Node* root);	//find element with key
	Node* findMinimum(Node* root); //find minimum inside tree
	Node* findMaximum(Node* root);	//find maximum inside tree
	void pushElement(Key key, Value value, Node*& root);  //push element into tree
	void deleteElement(Key key, Node*& root);	//find Key node, invoke deleteElementExtension(r->right)
	Node* deleteElementExtension(Node*& root);	//finds lowers in subTree and returns
	void deleteMinimum(Node*& root);	//delete node with minimum key
	void deleteMaximum(Node*& root);	//delete node with maximum key
	void emptyTree(Node*& root);	//destructor invoke this method
	void preorder(Node* root);
	void postorder(Node* root);
	int height(Node* root);
	
public:
	Tree(); //constuct root node
	Tree(const Tree& T);	//copy constructor
	~Tree();	//destructor
	void getElement(Key key);	//invoke getElement(key, root)
	void pushElement(Key key, Value value);	//invoke pushElement(key, value, root) 
	void deleteElement(Key key);
	void displayPreorder(); //invoke preorder(Node* root); 
	void displayPostorder(); //invoke postorder(Node* root);
	/*check height, minimum and maximum*/
	void status() {
		std::cout << "height: " << height(root) << "\n"; 
		std::cout << "maximum: " << findMaximum(root)->value << "\n"; 
		std::cout << "minimum: " << findMinimum(root)->value << "\n"; 
	}
};

int main()
{
	Tree<int, int> a;
	a.pushElement(5, 5); 
	a.pushElement(10, 10); 
	a.pushElement(3, 3); 
	a.pushElement(6, 6); 
	a.pushElement(12, 12);
	a.pushElement(4, 4);
	a.pushElement(2, 2); 

	a.status(); 
	



	return 0;
}
/*
assignment constructor
*/
template <typename Value, typename Key>
typename Tree<Value, Key>::Node& Tree<Value, Key>::Node::operator=(Node t){
	key = t.key;
	value = t.value;
	left = t.left;
	right = t.right;
}
/*
constructor
*/
template <typename Value, typename Key>
Tree<Value, Key>::Tree()
	:root(nullptr) {}; 
/*
copy constructor
*/
template <typename Value, typename Key>
Tree<Value, Key>::Tree(const Tree& T)
	:root(nullptr) {
	root = clone(T.root); 
}; 
/*
destructor
*/
template <typename Value, typename Key>
Tree<Value, Key>::~Tree() {
	emptyTree(root); 
}

template <typename Value, typename Key>
void Tree<Value, Key>::displayPreorder() {
	return preorder(root);
}
template <typename Value, typename Key>
void Tree<Value, Key>::displayPostorder() {
	return postorder(root);
}
/*
Postordered traversal of an ordered tree,
where the root of Tree is visited first
*/
template <typename Value, typename Key>
void Tree<Value, Key>::postorder(Node* r) {
	if (r == nullptr) {
		return;
	}

	postorder(r->left);
	postorder(r->right);
	std::cout << "key: " << r->key << " value: " << r->value << " \n";
}
/*
Preordered traversal of an ordered tree,
where the children of each node are ordered from left to right
*/
template <typename Value, typename Key>
void Tree<Value, Key>::preorder(Node* r) {
	if (r == nullptr) {
		return;
	}
	std::cout << "key: " << r->key << " value: " << r->value << " \n";
	preorder(r->left);
	preorder(r->right);
}
/*
1 param: root
recreate tree with recursive calls
*/
template <typename Value, typename Key>
typename Tree<Value, Key>::Node* Tree<Value, Key>::clone(Node* r) const {
	if (r == nullptr) {
		return r;
	}
	return new Node(r->key, r->value, clone(r->left), clone(r->right));
}
/*
1 param: root
search right/left side of tree
set evrything to null
*/
template <typename Value, typename Key>
void Tree<Value, Key>::emptyTree(Node*& r) {
	if (r != nullptr) {
		emptyTree(r->left);
		emptyTree(r->right);
		delete r;
	}
	r = nullptr;
}

template <typename Value, typename Key>
void Tree<Value, Key>::pushElement(Key key, Value value) {
	pushElement(key, value, root);	//invoke
}
/*
3 params: key, value and root node
search with recursion untill nullptr
insert new Node on that spot
*/
template <typename Value, typename Key>
void Tree<Value, Key>::pushElement(Key key, Value value, Node*& r) {
	if (r != nullptr) {
		if (r->key > key) {

			return pushElement(key, value, r->left);
		}
		else if (r->key < key) {

			return pushElement(key, value, r->right);
		}
	}
	r = new Node(key, value, nullptr, nullptr);
}
template <typename Value, typename Key>
void Tree<Value, Key>::getElement(Key key) {
	Node* temp = getElement(key, root);	//invoke
	if (temp != nullptr) {
		std::cout << temp->value << "\n";
	}
	else {
		std::cout << "No souch element" << "\n";
	}
}
/*
2 params: key and root node
search untill args.key == key
return r
*/
template <typename Value, typename Key>
typename Tree<Value, Key>::Node* Tree<Value, Key>::getElement(Key key, Node* r) {
	if (r != nullptr) {

		if (r->key > key) {	//if r's key is higher, go right
			return getElement(key, r->left);
		}
		else if (r->key < key) {	//if r'y key is lower, go left
			return getElement(key, r->right);
		}
		else {
			return r;	//return r
		}
	}
	return r; // return nullptr if it is not found
}
/*
1 param root node
search untill left link is empty
(thats smallest value)
*/
template <typename Value, typename Key>
typename Tree<Value, Key>::Node* Tree<Value, Key>::findMinimum(Node* r) {
	if (r->left == nullptr) {
		return r;
	}
	return findMinimum(r->left);
}
/*
1 param root node
search untill right link is empty
(thats highest value)
*/
template <typename Value, typename Key>
typename Tree<Value, Key>::Node* Tree<Value, Key>::findMaximum(Node* r) {
	if (r->right == nullptr) {
		return r;
	}
	return findMaximum(r->right);
}
/*
1 param: root
recursive search untill smallest value (left link is nullptr)
set it to right, and delete
no return value
*/
template <typename Value, typename Key>
void Tree<Value, Key>::deleteMinimum(Node*& r) {
	if (r == nullptr) {
		return;
	}
	if (r->left == nullptr) {
		Node* old = r;
		r = r->right;
		delete old;
		return;
	}
	return deleteMinimum(r->left);
}
/*
1 param: root
recursive search untill highest value (right link is nullptr)
set it to left, and delete
no return value
*/
template <typename Value, typename Key>
void Tree<Value, Key>::deleteMaximum(Node*& r) {
	if (r == nullptr) {
		return;
	}
	if (r->right == nullptr) {
		Node* old = r;
		r = r->left;
		delete old;
		return;
	}
	return deleteMaximum(r->right);
}
template <typename Value, typename Key>
void Tree<Value, Key>::deleteElement(Key key) {
	return deleteElement(key, root);
}
/*
2 params: key and root
finds node, invoke findMinDeleteMin(r->right)
delete old
*/
template <typename Value, typename Key>
void Tree<Value, Key>::deleteElement(Key key, Node*& r) {
	if (r == nullptr) {
		return;
	}
	if (r->key > key) {
		return deleteElement(key, r->left);
	}
	else if (r->key < key) {
		return deleteElement(key, r->right);
	}
	else if (r->left != nullptr && r->right != nullptr) {	//if node with two link is found
		Node* temp = deleteElementExtension(r->right);
		r->key = temp->key;	//find minimum successor from right subtree and set it to r->key
		r->value = temp->value;
		delete temp;  
	}
	else {
		Node* old = r;
		r = (r->left != nullptr) ? r->left : r->right;
		delete old;
	}
}
/*
1 param: node
set up last node for deletion at deleteElement
return node that will be deleted
*/
template <typename Value, typename Key>
typename Tree<Value, Key>::Node* Tree<Value, Key>::deleteElementExtension(Node*& r) {
	if (r == nullptr) {
		return r;
	}
	if (r->left != nullptr) {
		return deleteElementExtension(r->left);
	}
	Node* oldNode = r;
	r = r->right;
	return oldNode; 
}
/*
return height of the tree using postorder traverse
*/
template <typename Value, typename Key>
int Tree<Value, Key>::height(Node* r) {
	if (r == nullptr) {
		return -1; 
	}
	return std::max(height(r->right), height(r->left)) + 1; 
}
