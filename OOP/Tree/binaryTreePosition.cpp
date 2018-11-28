#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

/*
The most basic entity structure is Node. Node is declared inside protected part of BinaryTree class as struct. 
Each node has value, link to parent, left and right node. In public section of BinaryTree class we define Position.
He's data members consist of Node pointer to a Tree. Access to node's value is provided with overloaded 
dereferencing operatr ("*"). BinaryTree is declared as friend. Functions parent(), left(), right() are used to 
accessed apropriate member of a Node structure. List declaration is used to represent list of nodes. 
There are some update methods inside BinaryTree. addRoot(), expandExternal() and removeAboveExternal() 
BinaryTree private part consist of Node pointer (Node* root) and number of nodes (int n).
*/

template <typename T>
class BinaryTree {
protected:	//only BinaryTree and derived class can access Node
	struct Node {	
		T value;	//element
		Node* parent;	//link to parent node
		Node* left;		//link to left node
		Node* right;	//lin to right node
		Node()	//constructor
			:value(), parent(NULL), left(NULL), right(NULL) {};
	};
public:
	class Position {	
	public:
		Position(Node* x = NULL);	//constructor
		T& operator*();		//access element
		Position parent() const;	//get parent
		Position left() const;	//get left chid
		Position right() const;	//get right child
		bool isRoot() const;	//check if node is a root
		bool isExternal() const;	//check if node is external
		friend class BinaryTree<T>; //BinaryTree can acces private members
	private:
		Node* v; //pointer to node
	};
	typedef std::list<Position> PositionList;	 //list of positions
	BinaryTree(); 
	int size() const;	//check number of nodes
	bool isEmpty() const;	//check if tree is empty
	Position getRoot() const; //get the root
	PositionList positions() const; //get list of nodes
	void addRoot();		//add root to empty tree
	void expandEternal(const Position& p);	//expand external Node
	Position removeAboveExternal(const Position& p); //remove p and parent
protected:
	void preorder(Node* v, PositionList& pl) const;
private:
	Node* root;		//root pointer to first node
	int n;	//number of nodes 
};


int main()
{
	
	
	
	



	return 0;
}
/*
Position methods
*/
template <typename T>
BinaryTree<T>::Position::Position(Node* x) {
	this->v = x; 
}

template <typename T>
T& BinaryTree<T>::Position::operator*() {
	return v->value;
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::left() const {
	return Position(v->left);
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::right() const {
	return Position(v->right);
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::parent() const {
	return Position(v->parent);
}

template <typename T>
bool BinaryTree<T>::Position::isExternal() const {
	return (v->left == NULL && v->right == NULL);
}
/*
BinaryTree methods declarations
*/
template <typename T>
bool BinaryTree<T>::Position::isRoot() const {
	return (v->parent == NULL);
}
template <typename T>
BinaryTree<T>::BinaryTree()
	:root(NULL), n(0) {};

template <typename T>
int BinaryTree<T>::size() const {
	return n;
}
template <typename T>
bool BinaryTree<T>::isEmpty() const {
	return (n == 0);
}
template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::getRoot() const {
	return Position(root);
}
template <typename T>
void BinaryTree<T>::addRoot() {
	root = new Node;
	n = 1;
}

template <typename T>
void BinaryTree<T>::expandEternal(const Position& p) {	//expand external node
	Node* v = p.v;			//set pointer to external position
	v->left = new Node;		//create left node
	v->left->parent = v;	//set left's parent
	v->right = new Node;	//create right node
	v->right->parent = v;	//set right's parent
	n += 2;			//increment number of nodes by two
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::removeAboveExternal(const Position& p) {	//remove p and p's parent
	Node* position = p.v;
	Node* parent = position->parent;
	Node* sibling = (position == parent->left) ? parent->right : parent->left;
	if (parent == root) {	//if p is child of root
		root = sibling;		//sibling is new root
		sibling->parent = NULL;		//root dont have parents
	}
	else {	//if p is not child of the node
		Node* gparent = parent->parent;		//take he's grandparent
		if (gparent->left == parent) {	//if parent node is left child
			gparent->left = sibling;	//sibling is now left child
		}
		else {	//else if parent node is right child
			gparent->right = sibling;	//sibling is now right child
		}
		sibling->parent = gparent; //and sibling's parent is granparent of node that will be deleted
	}
	delete position; //delete p node
	delete parent;	//delete he's parent
	n -= 2;		//reduce number of nodes
	return Position(sibling);
}

template <typename T>
void BinaryTree<T>::preorder(Node* v, PositionList& L) const {	//list of all node
	L.push_back(Position(v)); //add this node
	if (v->left != NULL) {
		preorder(v->left, L);	//recursive call for left side of the tree 
	}
	if (v->right != NULL) {
		preorder(v->right, L); //recursivve call for right call of the tree
	}
}

template <typename T>
typename BinaryTree<T>::PositionList BinaryTree<T>::positions() const {	//list of all node
	PositionList L;		//creates list
	preorder(root, L);	//traverse the tree and stores nodes inside list
	return PositionList(L);		//return resulting list
}
