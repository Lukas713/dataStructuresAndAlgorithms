#include "pch.h"
#include <iostream>
#include <string>
#include <vector>

class Exeption {	//exeption handling with constructor
private:
	std::string error;
public:
	Exeption(const std::string& err)
		: error(err) {};
	std::string getError() const {
		return this->error;
	}
};

class ItemExeption : public Exeption {
public:
	ItemExeption(const std::string& err)
		:Exeption(err) {};
};

class Item {		//nodes for inventory
	std::string name;
	double price;
	int quantity; 
	int sku; 
	Item* next;
	Item* prev; 

	friend class Inventar; 
	friend class ShoppingCart;
};

class Inventar {
private:
	bool uniqueSku(const int x);

public:
	Inventar();		//constructor
	virtual ~Inventar();	//destructor
	Item* getHead() {return head; }	
	virtual void checkout();
	Item takeItem(const int sku, const int quantity);
	virtual void addItem(const double& price, const int sku, const std::string& name, int quantity); 

protected:
	Item* head;
	Item* tail;
	virtual void addItemAfter(Item* x, const int sku, const double& price, const std::string& name, int quantity);	//add item after
	virtual void remove(Item* o);
	virtual void removeItem();
	virtual bool isEmpty() const;
};





class ShopingList {
friend class ShoppingCart;

private:
	int sku; 
	std::string name;
	double price;
	ShopingList* next;
	ShopingList* prev;
	int quantity; 
};

class ShoppingCart : public Inventar {
	double total; 
	ShopingList* headS;
	ShopingList* tailS;
	void addAfter(ShopingList* o, const std::string name, const double price, const int sku, const int quantity);
	double getTotal() { return total; }
	bool isEmpty();
	void setTotal(const double tot) { total = tot; }
	
public:
	ShoppingCart(Inventar* list); 
	~ShoppingCart();
	void addItem(Inventar* list, const int sku, const int quantity);
	void remove(ShopingList* o);
	void removeItem(const int sku, const int quantity); 
	void checkout(); 
};



int main()
{

	std::string txt;
	double pric;
	int sku, quant, choice; 

	Inventar* inventar = new Inventar;
	ShoppingCart* a;
	while (1) {
		std::cout << "***************************************************" << std::endl;
		std::cout << "Inventory" << std::endl;
		std::cout << "***************************************************" << std::endl;
		std::cout << "1. Add" << std::endl;
		std::cout << "2. Done" << std::endl;
		std::cout << "0. Exit" << std::endl;
		std::cout << "enter option: ";
		std::cin >> choice;
		switch (choice) {
		case 1:
			std::cout << "Enter name: " << std::endl;
			std::cin >> txt;
			std::cout << "Enter price: " << std::endl;
			std::cin >> pric; 
			std::cout << "Enter quantity: " << std::endl;
			std::cin >> quant; 
			std::cout << "Enter sku(unique ID i guess): " << std::endl;
			std::cin >> sku;
			inventar->addItem(pric, sku, txt, quant); 
			break;
		case 2:
			a = new ShoppingCart(inventar);
			while (1) {
				std::cout << "***************************************************" << std::endl;
				std::cout << "Shopping cart" << std::endl;
				std::cout << "***************************************************" << std::endl;
				std::cout << "1. Add" << std::endl;
				std::cout << "2. Remove" << std::endl;
				std::cout << "3. Checkout" << std::endl;
				std::cout << "0. Exit" << std::endl;
				std::cout << "enter option: ";
				std::cin >> choice;
				switch (choice) {
					case 1:
						std::cout << "Enter sku" << std::endl;
						std::cin >> sku;
						std::cout << "Enter quantity" << std::endl; 
						std::cin >> quant; 
						a->addItem(inventar, sku, quant);
						break; 
					case 2:
						std::cout << "Enter sku" << std::endl;
						std::cin >> sku;
						std::cout << "Enter quantity" << std::endl;
						std::cin >> quant; 
						a->removeItem(sku, quant); 
						break;
					case 3:
						a->checkout(); 
						delete a; 
						delete inventar;
						break; 
					case 0:
						exit(1);
						break; 
				}
			}
			break; 
		case 0:
			exit(1);
			break;
		}
	}	

	return 0; 
}


//constructor
Inventar::Inventar() {
	head = new Item;
	tail = new Item;
	head->next = tail;	//creates head node and set it to tail
	tail->prev = head;	//creates tail node and set it to head

}
//destructor
Inventar::~Inventar() {	
	while (!isEmpty()) {	//check if empty
		removeItem();	//remove item
	}
	delete head;	//delete head and tail nodes
	delete tail;
}
//checking if list is empty
bool Inventar::isEmpty() const {
	if (head->next != tail) {
		return false;
	}
	return true;
}
//checks if item with specific sku is in the list or throw exeption
bool Inventar::uniqueSku(const int sku) {
	try {
		Item* temp = head;	//pointer to head
		while (temp != tail) {	

			if (temp->sku == sku) {
				throw ItemExeption("Sku already exists!"); 
			}
			temp = temp->next;	//traverse
		}
		return true; 
	}
	catch (ItemExeption& err) {
		std::cout << "---------------------------" << std::endl;
		std::cout << err.getError(); 
		return false; 
	}
	
}

//ADDING ITEMS
void Inventar::addItemAfter(Item* o, const int sku, const double& price, const std::string& name, int quantity) {
	if (!uniqueSku(sku)) {	//if item is not in the list
		return;
	}
	Item* newItem = new Item;	//pointer to item
	newItem->name = name;	//sets members
	newItem->price = price;
	newItem->quantity = quantity;
	newItem->sku = sku; 

	//inserting node in the list
	newItem->next = o;	
	newItem->prev = o->prev;
	o->prev->next = newItem;
	o->prev = newItem;
}
void Inventar::addItem(const double& price, const int sku, const std::string& name, int quantity) {
	return addItemAfter(head->next, sku, price, name, quantity);	//inserting node at begining of the list
}
//DELETE NODES
void Inventar::remove(Item* o) {
	Item* prevItem = o->prev;	//pointer to previous
	Item* nextItem = o->next;	//pointer to next
	prevItem->next = nextItem;	//colaboration
	nextItem->prev = prevItem;
	delete o;	//delete what you want tot delete
}
void Inventar::removeItem() {
	try {
		if (head->next != tail) {	//remove if list is not empty
			return remove(head->next);
		}
		throw ItemExeption("List is empty!");
	}
	catch (ItemExeption& err) {
		std::cout << "---------------------------" << std::endl;
		std::cout << err.getError();
	}
}

Item Inventar::takeItem(const int sku, const int quantity) {	//catch item with specific sku and remove quantity many 
	Item* temp = head->next;
	try {
		while (temp->sku != sku) {
			temp = temp->next;
			if (temp == tail) {
				throw ItemExeption("There is no souch item.");
			}
			if (temp->quantity < quantity) {	//checks if you enter higher quantity
				throw ItemExeption("Your quantity is too large."); 
			}
		}
		temp->quantity -= quantity; //remove some quantity
		return *temp;
	}
	catch (ItemExeption& err) {
		std::cout << "---------------------------" << std::endl;
		std::cout << err.getError(); 
	}
}

void Inventar::checkout() {	//pinter on first node
	Item* temp = head->next;

	while (temp != tail) {	//write specifications
		std::cout << "Name: " << temp->name << std::endl;
		std::cout << "Price: " << temp->price << std::endl;
		std::cout << "Quantity: " << temp->quantity << std::endl;
		std::cout << "sku: " << temp->sku << std::endl;
		std::cout << std::endl;

		temp = temp->next;	//traverse 
	}
	return;
}

//SHOPPING CART
ShoppingCart::ShoppingCart(Inventar* list) {	//constructor
	headS = new ShopingList;
	tailS = new ShopingList;
	headS->next = tailS;
	tailS->prev = headS;

	total = 0.0;	//sets total to 0.0
	list->checkout();	//write items in inventory
}
//DESTRUCTOR
ShoppingCart::~ShoppingCart() {
	while (!isEmpty()) {	//checks if not empty
		remove(headS->next);	//remove one by one
	}
	delete headS;	//delete head node
	delete tailS;	//delete tail node
}
void ShoppingCart::checkout() {	//virtual methods
	ShopingList* temp = headS->next;	//pointer to firt node

	while (temp != tailS) {	//while temp is not last node write specifications
		std::cout << "Name: " << temp->name << std::endl;
		std::cout << "Quantity: " << temp->quantity << std::endl;
		std::cout << "Price: " << temp->price << std::endl;

		temp = temp->next;	//traverse
	}
	std::cout << "---------------------" << std::endl;
	std::cout << "total: " << getTotal() << std::endl;	//write total at the end
	return;
}


bool ShoppingCart::isEmpty() {	//checks if list is empty
	if (headS->next != tailS) {
		return false;
	}
	return true;
}
//ADD ITEM TO SHOPPING CART
void ShoppingCart::addAfter(ShopingList* o, const std::string name, const double price, const int sku, const int quantity) {
	ShopingList* newItem = new ShopingList;	//dynamic aloc pointer to Shopping list
	newItem->name = name;	//set members to node
	newItem->price = price;
	newItem->sku = sku;
	newItem->quantity = quantity;
	//insert node in the list
	newItem->next = o;
	newItem->prev = o->prev;	
	o->prev->next = newItem;
	o->prev = newItem;
	total += (price * quantity);	//set total

}
void ShoppingCart::addItem(Inventar* list, const int sku, const int quantity) {
	Item temp = list->takeItem(sku, quantity);
	addAfter(headS->next, temp.name, temp.price, temp.sku, quantity); //add node at beggining
	return;
}
//REMOVE ITEM
void ShoppingCart::remove(ShopingList* o) {
	ShopingList* prev = o->prev;	//pointer to previous
	ShopingList* next = o->next;	//pointer to next
	//colaboration
	prev->next = next;	
	next->prev = prev;
	delete o;	//delete that node
}

void ShoppingCart::removeItem(const int sku, const int quantity) {
	ShopingList* temp = headS;
	try {
		while (temp != tailS) {	//traverse to the end of the lit
			if (temp->sku == sku) {	//if this item
				if (temp->quantity == quantity) {	//if want to remove all quantitys
					if (total <= (quantity*temp->price)) {
						setTotal(0.0);	//set total to 0
					}
					remove(temp);	//remove totaly
					return;
				}
				else if (temp->quantity > quantity) {	//if want to remove some
					temp->quantity -= quantity;		//remove little bit
					total -= (quantity*temp->price);	//remove a little bit from total
					return; 
				}
			}
			temp = temp->next;	//traverse
		}
		throw ItemExeption("There is no souch item.");
	}
	catch (ItemExeption& err) {
		std::cout << "---------------------------" << std::endl;
		std::cout << err.getError();
	}

}





