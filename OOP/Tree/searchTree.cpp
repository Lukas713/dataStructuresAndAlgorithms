#include "pch.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>


template <typename T>
class BinaryTree {

protected:	//only BinaryTree and derived class can access Node
	struct Node {
		T value;	//element
		Node* parent;	//link to parent node
		Node* left;		//link to left node
		Node* right;	//lin to right node
		Node(T val = 0, Node* prnt = NULL, Node* lft = NULL, Node* rgt = NULL)	//constructor
			:value(val), parent(prnt), left(lft), right(rgt) {};
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
		Node* v; //pointer node
	};
	typedef std::list<Position> PositionList;	 //list of positions

	BinaryTree();
	BinaryTree(const BinaryTree& T);
	BinaryTree& operator=(BinaryTree T);
	~BinaryTree();
	Position getRoot() const; //get the root
	PositionList positions() const; //get list of nodes
	void addRoot();		//add root to empty tree
	void expandEternal(const Position& p);	//expand external Node
	Position removeAboveExternal(const Position& p); //remove p and parent
	int depth(const Position& p) const;
	int height(const Position& p) const;
	void preorderPrint(Position& p);
	void postorderPrint(Position& p);
	void inorderPrint(Position& p);
	void externalLeft(const Position& p, int& i);	//counting left external nodes
	void sumPaths(const Position& p, int i);
	void sumInternalPaths(const Position& p, int i);
	void sumExternalPaths(const Position& p, int i);
	void eulerPrint(const Position& p);
	int levelWidth(const Position& root, int lvl) const; //count width of tree lvl
	void reflect(const Position& root);	//left nodes become right and right become left
	T findMax(Position p);
	Position find(Position root, T value);
	/*if base data type is int*/
	int areAllHigherThen(int n, const Position& root) const; //return 1 if all tree's values are higher then n, 0 if not
	int sumAllValues(Position root) const;

protected:
	void preorder(Node* v, PositionList& pl) const;
	int size() const;	//check number of nodes
	bool isEmpty() const;	//check if tree is empty
	Node* clone(Node*  p) const;
	void emptyTree(Position p);

private:
	Node* root;	//root pointer to first node
	int n;	//number of nodes 
};

template <typename K, typename V>
class Entry {
public:
	typedef K Key;
	typedef V Value;
public:
	Entry(const K& k = K(), const V& v = V())
		:key(k), value(v) {}
	const K& getKey() { return key;  }
	const V& getValue() { return value;  }
	void setKey(const K& k) { key = k; }
	void setValue(const V& v) { value = v;  }
private:
	K key;
	V value;
};

template <typename E>
class SearchTree {
public:
	typedef typename E::Key K; 
	typedef typename E::Value V; 
	class Iterator; 
public:
	SearchTree(); 
	int size() const; 
	bool isEmpty() const; 
	Iterator find(const K& key); 
	Iterator insert(const K& key, const V& value); 
	void erase(const K& key); 
	void erase(const Iterator& p); 
	Iterator begin(); 
	Iterator end(); 
protected:
	/*utilityes*/
	typedef BinaryTree<E> BinaryTree; 
	typedef typename BinaryTree::Position TreePosition; 
	TreePosition root() const; 
	TreePosition finder(const K& key, const V& value); 
	TreePosition inserter(const K& key, const V& value); 
	TreePosition eraser(TreePosition& p);
	TreePosition restructure(const TreePosition& p); 
private:
	BinaryTree T; 
	int n; 
public:
	class Iterator {
	private:
		TreePosition p; 
	public:
		Iterator(const TreePosition& v)
			: p(v) {}
		const E& operator*() const { return *p;  }
		E& operator*() { return *p;  }
		bool operator==(const Iterator& other) const { return p == other.p;  }
		Iterator& operator++(); 
		friend class SearchTree; 
	};
};




int main()
{

	BinaryTree<int> a; 
	




	return 0;
}
/*
Position methods
*/
template <typename T>
BinaryTree<T>::Position::Position(Node* x) {	//construct position node
	this->v = x;
}

template <typename T>
T& BinaryTree<T>::Position::operator*() {	//access value
	return v->value;
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::left() const {	//construct position on left link
	return Position(v->left);
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::right() const { //construct position on right link
	return Position(v->right);
}

template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::Position::parent() const { //construct position on parent
	return Position(v->parent);
}
/*
no param
check if node is external
*/
template <typename T>
bool BinaryTree<T>::Position::isExternal() const {
	return (v->left == NULL && v->right == NULL);
}
/*
BinaryTree methods declarations
*/
template <typename T>
BinaryTree<T>::BinaryTree()
	:root(NULL), n(0) {};

template <typename T>
BinaryTree<T>::~BinaryTree() {	//destroy whole tree
	emptyTree(getRoot());
}
template <typename T>
BinaryTree<T>::BinaryTree(const BinaryTree& T)	//copy constrcutor
	:root(NULL), n(0) {
	root = clone(T.getRoot().v);
}
template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(BinaryTree T) {	//assignment operator
	if (this != &T) {
		if (root != NULL) emptyTree(root);
		root = clone(T.getRoot().v);
	}
	return *this;
}
/*
1 param: position
visit left side, then right side
clone Tree
*/
template <typename T>
typename BinaryTree<T>::Node* BinaryTree<T>::clone(Node* p) const {	//clone with postorder
	if (p == NULL) {
		return p;
	}
	return new Node(p->value, p->parent, clone(p->left), clone(p->right));
}
/*
param position
clean whole tree with recursive calls
no return value
*/
template <typename T>
void BinaryTree<T>::emptyTree(Position p) {
	if (p.v != NULL) {
		emptyTree(p.left());
		emptyTree(p.right());
		delete p.v;
	}
	root = NULL;
}
/*
no param
check if node is root
return bool
*/
template <typename T>
bool BinaryTree<T>::Position::isRoot() const {
	return (v->parent == NULL);
}
/*
no param
number of nodes
return int
*/
template <typename T>
int BinaryTree<T>::size() const {
	return n;
}

/*
no param
checks if tree is empty
return bool
*/
template <typename T>
bool BinaryTree<T>::isEmpty() const {
	return (n == 0);
}
/*
no param
construct Position on root
return Position
*/
template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::getRoot() const {
	return Position(root);
}
/*
no param
add's root, set n to 1
no ret value
*/
template <typename T>
void BinaryTree<T>::addRoot() {
	root = new Node;
	n = 1;
}
/*
1 param: const referance to position
creates two siblings
no ret value
*/
template <typename T>
void BinaryTree<T>::expandEternal(const Position& p) {	//expand external node
	Node* v = p.v;			//set pointer to external position
	v->left = new Node;		//create left node
	v->left->parent = v;	//set left's parent
	v->right = new Node;	//create right node
	v->right->parent = v;	//set right's parent
	n += 2;			//increment number of nodes by two
}
/*
1 param: const referance to Position
delete Position Node and he's parent
return new Position
*/
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
/*
2 params: pointer to Node, referance to List
fill list with nodes
reursive calls through whole list
no return value
*/
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
/*
no param
creates list, fill it with nodes
return PositionList
*/
template <typename T>
typename BinaryTree<T>::PositionList BinaryTree<T>::positions() const {	//list of all node
	PositionList L;
	preorder(root, L);	//traverse the tree and stores nodes inside list
	return PositionList(L);	//return resulting list
}
/*
1 param: Position
compute depth of Node
return int
*/
template <typename T>
int BinaryTree<T>::depth(const Position& p) const {
	if (p.isRoot()) {
		return 0;
	}
	else {
		return 1 + depth(p.parent());
	}
}
/*
return height of tree
argument position
test if its NULL,
*/
template <typename T>
int BinaryTree<T>::height(const Position& p) const {
	if (p.v == NULL) {
		return -1;
	}
	return 1 + std::max(height(p.left()), height(p.right()));
}
/*
2 params: position and integer referance
counts depths of every node and adds to i
no return value
*/
template <typename T>
void BinaryTree<T>::sumPaths(const Position& p, int i) {
	if (p.v == NULL) {
		return;
	}
	i += depth(p);
	sumPaths(p.left(), i);
	sumPaths(p.right(), i);
}
/*
2 params: position and referance to int
if internal position, add he's depth to int
no return value
*/
template <typename T>
void BinaryTree<T>::sumInternalPaths(const Position& p, int i) {
	if (p.v == NULL) {
		return;
	}
	if (!p.isExternal()) {
		i += depth(p);
	}
	sumInternalPaths(p.left(), i);
	sumInternalPaths(p.right(), i);
}
/*
2 params: position and referance to int
if external, add he's depth to int
no return value
*/
template <typename T>
void BinaryTree<T>::sumExternalPaths(const Position& p, int i) {
	if (p.v == NULL) {
		return;
	}
	if (p.isExternal()) {
		i += depth(p);
	}
	sumExternalPaths(p.left(), i);
	sumExternalPaths(p.right(), i);
}

template <typename T>
void BinaryTree<T>::preorderPrint(Position& p) {		//root is visited first and then the subtrees as children
	std::cout << *p << " ";							//are visited recursively
	if (!p.isExternal()) {
		preorderPrint(*&p.left());
		preorderPrint(*&p.right());
	}
}

template <typename T>
void BinaryTree<T>::postorderPrint(Position& p) {	//visits children of tree first, then visit the root
	if (!p.isExternal()) {
		postorderPrint(*&p.left());
		postorderPrint(*&p.right());
	}
	std::cout << *p << " ";
}
template <typename T>
void BinaryTree<T>::inorderPrint(Position& p) {	//with inorder traversal, node is visited between recursive calls
	if (!p.isExternal()) {
		inorderPrint(*&p.left());
	}
	std::cout << *p << " ";		//node visit
	if (!p.isExternal()) {
		inorderPrint(*&p.right());
	}
}
/*
1 param: Position p
every node is visited three times
external nodes 3 times in a row
*/
template <typename T>
void BinaryTree<T>::eulerPrint(const Position& p) {
	std::cout << *p << " ";
	if (!p.isExternal()) {
		eulerPrint(p.left());
	}
	std::cout << *p << " ";
	if (!p.isExternal()) {
		eulerPrint(p.right());
	}
	std::cout << *p << " ";
}
/*
Algorithm for counting the number of left external nodes in a
binary tree, using the Binary tree ADT.
*/
template <typename T>
void BinaryTree<T>::externalLeft(const Position& p, int& i) {
	if (p.v == NULL) return;

	if (p.isExternal() && p.parent().left().v == p.v) {
		i++;
	}
	externalLeft(p.left(), i);
	externalLeft(p.right(), i);
}

/*
2 params: root position and level of tree
returns number of children at that level
return int
*/
template <typename T>
int BinaryTree<T>::levelWidth(const Position& r, int lvl) const {
	if (r.v == NULL || lvl < 1) {
		return 0;
	}
	if (lvl == 1) {
		return 1;
	}
	return levelWidth(r.left(), lvl - 1) + levelWidth(r.right(), lvl - 1);
}
/*
1 param: Position
opens all nodes with recursive calls
swap right and left
no return value
*/
template <typename T>
void BinaryTree<T>::reflect(const Position& r) {	//clone with postorder
	if (r.v == NULL) {
		return;
	}
	reflect(r.left());
	reflect(r.right());
	Node* temp = r.v->right;
	r.v->right = r.v->left;
	r.v->left = temp;
}
/*
1 param: root node
check higher value (left or right sie)
return higher value
*/
template <typename T>
T BinaryTree<T>::findMax(Position p) {
	if (p.isExternal()) {
		return *p;
	}
	T maxL = findMax(p.left());
	T maxR = findMax(p.right());
	T max = maxL > maxR ? maxL : maxR;

	return (max > *p) ? max : *p;
}
/*
2 params: root position and value
check left/right side for argument value
if found return that position
if not, retur root position
*/
template <typename T>
typename BinaryTree<T>::Position BinaryTree<T>::find(Position p, T value) {
	if (p.isExternal() || *p == value) {
		return p;
	}
	Position left = find(p.left(), value);
	Position right = find(p.right(), value);

	if (*left == value) {
		return left;
	}
	else if (*right == value) {
		return right;
	}
	else {
		if (p.isRoot()) {
			std::cout << "Not found! \n";
		}
		return p;
	}
}
/*
2 params: n value and root position
if every node has lower value then value n
return 1, else return 0
int return
*/
template <typename T>
int BinaryTree<T>::areAllHigherThen(int n, const Position& r) const {
	int i = 0;
	if (*r < n) {
		i = 1;
	}
	if (!r.isExternal()) {
		areAllHigherThen(n, r.left());
		areAllHigherThen(n, r.right());
	}
	return i;
}
/*
1 param: root position
traverse whole tree and count node's value
int return value
*/
template <typename T>
int BinaryTree<T>::sumAllValues(Position p) const {
	if (!p.isExternal()) {
		return sumAllValues(p.left()) + sumAllValues(p.right()) + *p;
	}
	return *p;
}
/*
SEARCH TREE
*/
/*
construct super root
and adds two children
only left one is used (as root)
*/
template <typename E>
SearchTree<E>::SearchTree()
	: T(), n(0)
{
	T.addRoot(); //create's super root
	T.expandEternal(T.getRoot());
}
/*
no param
return left child of superRoot
*/
template <typename E>
typename SearchTree<E>::TreePosition SearchTree<E>::root() const {
	return T.getRoot().left();
}
/*
operator overload
increment position at inorder succesor
(left most children of right subtree)
*/
template <typename E>
typename SearchTree<E>::Iterator& SearchTree<E>::Iterator::operator++() {
	TreePosition w = p.right();	

	if (!w.isExternal()) {
		do {
			p = w;
			w = w.left();
		} while (!w.isExternal());
	}
	else {
		w = p.parent();
		while (p == w.right()) {
			p = w; w = w.parent();
		}
		p = w;
	}
	return *this;
}

template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::end() {
	return Iterator(T.root);	//return iterator on super root
}

template <typename E>
typename SearchTree<E>::Iterator SearchTree<E>::begin() {
	TreePosition p = root();	//get root node (left child of super root)
	while (!p.isExternal())
		p = p.left();
	return Iterator(p.parent()); //return parent of unused leaf node
}
