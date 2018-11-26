#include "pch.h"
#include <iostream>
#include <string>
#include <vector>


class Tree {

	struct Node {
		int value;	//associated value
		Node* left; //link to lower values
		Node* right; //link to higher values

		Node(const int& val, Node* lft, Node* rgt)
			: value(val), left(lft), right(rgt) {}; 
		Node(int&& val, Node* lft, Node* rgt)
			: value(static_cast<int &&>(val)), left(lft), right(rgt) {}; 
	};

	Node* root; //node root
	
	void insert(const int& value, Node*& root);
	void insert(int&& x, Node*& root);
	void remove(const int& value, Node*& root); 
	bool contains(const int value, Node* root) const; 
	Node* removeMin(Node*& root); 
	void emptyTree(Node*& root); 
	Node* clone(Node* root); 

public:
	Tree();
	Tree(const Tree& T);
	~Tree(); 
	void insert(const int value); 
	void remove(const int value); 
	bool contains(const int value) const; 
	Node* findMin(Node*& root) const;
	Node* findMax(Node*& root) const;

	void display() {
		Node* x = findMin(root); 
		Node* y = findMax(root); 
		std::cout << "min: " << x->value; 
		std::cout << "max: " << y->value; 
	}
};

int main()
{
	Tree a;  
	
	for (int i = 0; i < 5; i++) {
		a.insert(rand() % 100); 
	}
	a.insert(28); 
	a.insert(36); 
	a.insert(35);
	a.insert(37); 
	a.remove(34); 
	std::cout << a.contains(34); 
	


	return 0; 
}
/*
public methds
*/
Tree::Tree()
	:root(nullptr) {}; 
Tree::~Tree() {
	emptyTree(root); 
}
Tree::Tree(const Tree& T)
	:root(nullptr) {
	root = clone(T.root); 
}
Tree::~Tree() {
	emptyTree(root); 
}
void Tree::insert(const int x) {
	return insert(x, root);
}
bool Tree::contains(const int value) const {
	return contains(value, root);
}
void Tree::remove(const int v) {
	return remove(v, root);
}
/*
internal methods
*/
Tree::Node* Tree::clone(Node* r) {
	if (r != nullptr) {
		return new Node(r->value, clone(r->left), clone(r->right));	//recreate tree with recursion calls of left/right side
	}
	return nullptr; 
}
bool Tree::contains(const int val, Node* r) const {	//check if value is in the tree
	if (r == nullptr) {	//if there is no souch value
		return false;
	}
	else if (r->value > val) {	//if value is higher then argument, go to right node
		return contains(val, r->left);
	}
	else if (r->value < val) {
		return contains(val, r->right);	//if value is lower then argument, go to left noe
	}
	else {
		return true;	//return true
	}
}

void Tree::insert(const int& val, Node*& r) {	//const ref to value and reference to pointer(root)
	if (r != nullptr) {	//if root of tree/subTree is nullPtr
		if (r->value > val) {
			return insert(val, r->left);	//if value is higher, go left
		}
		else if (r->value < val) {	//if value is lower, go right
			return insert(val, r->right);
		}
		else {
			//do nothing... for now
		}
	}
	r = new Node(val, nullptr, nullptr);	//insert new root
}
void Tree::insert(int&& v, Node*& r) {	//rvalue and ref. to pointer (root)
	if (r != nullptr) {
		if (r->value > v) {
			return insert(std::move(v), r->right);
		}
		else if (r->value < v) {
			return insert(std::move(v), r->left);
		}
		else {
			//do nothing for now
		}
	}
	r = new Node(static_cast<int &&>(v), nullptr, nullptr);
}

Tree::Node* Tree::findMin(Node*& r) const {	//ref to pointer(root)
	if (r == nullptr) {	//if it hits empty root
		return r;
	}
	if (r->left == nullptr) {	//if it hits empty left root
		return r;
	}
	return findMin(r->left);	//recursive call to next left
}
Tree::Node* Tree::findMax(Node*& r) const {
	if (r == nullptr) {
		return r;
	}
	if (r->right == nullptr) {
		return r;
	}
	return findMax(r->right);
}
Tree::Node* Tree::removeMin(Node*& r) {
	if (r == nullptr) {
		return r;
	}
	if (r->left == nullptr) {	//find lowerst node
		Node* old = r;
		r = (r->right != nullptr) ? r->right : r->left;
		return old;
	}
	return removeMin(r->left);
}
void Tree::remove(const int& value, Node*& r) {
	if (r == nullptr) {
		return;		//item not found
	}

	if (r->value > value) {
		return remove(value, r->left);	//recursive call for left side
	}
	else if (r->value < value) {
		return remove(value, r->right); //recursive call for right side
	}
	else if (r->left != nullptr && r->right != nullptr) {
		r->value = removeMin(r->right)->value; //find r's successor and delete
	}
	else {
		Node* oldNode = r;
		r = (r->left != nullptr) ? r->left : r->right;
		delete oldNode;
	}
}
void Tree::emptyTree(Node*& r) {
	if (r != nullptr) {	
		emptyTree(r->left);	//recursive call for left side
		emptyTree(r->right);	//for right side of the root
		delete r;	
	}
	r = nullptr;
}
