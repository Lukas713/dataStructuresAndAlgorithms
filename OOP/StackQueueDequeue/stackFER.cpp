#include "pch.h"
#include <iostream>
#include <string>
#include <list>
#include <queue>

/*
Funkcija Prazan vraæa 1 ukoliko je stog prazan, a 0 inaèe.
Za klasu Stog nije definiran copy konstruktor,
a možete pretpostaviti da u svakom objektu klase Stog ima dovoljno mjesta za dodavanje novih elemenata za stog.
Pokušaj skidanja elementa iz praznog stoga, dovest æe do pogreške.
Ukoliko drugaèije nije navedeno, smijete koristiti pomoæne stogove, ali ne i dodatna polja

Zadatak 1:
Napisati funkciju koja æe napraviti i vratiti duplikat zadanog stoga 
(isti takav stog, isti elementi koji imaju isti redoslijed). 
Zadani stog mora na kraju ostati nepromijenjen. 
Funkcija mora imati prototip:
	Stog *duplikat(Stog *zadani);

Zadatak 2:
Napisati funkciju koja æe iz stoga izbaciti sve parne brojeve.
Meðusobni redoslijed neparnih brojeva mora ostati nepromijenjen.
Funkcija vraæa broj izbaèenih brojeva te ima sljedeæi prototip:
	int izbaci_parne(Stog *stog);


Zadatak 3:
Napisati funkciju koja æe stvoriti novi stog koji æe sadržavati sve one brojeve iz zadanog stoga
za koje funkcija èiji je prototip int provjeri(int n) vrati istinu.
Poredak prostih brojeva u novom stogu nije bitan.
Zadani stog mora na kraju ostati nepromijenjen. Funkcija mora imati prototip:
	Stog *kopiraj_provjerene(Stog *zadani);

Zadatak 4:
Napisati funkciju koja æe na osnovu ulaznih stogova stog1 i stog2 stvoriti novi stog 
koristeæi pritom sljedeæe pravilo da se za novi element u novom stogu
uvijek odabere manji od elemenata na vrhu stogova stog1 i stog2. 
Ukoliko se jedan od stogova isprazni, onda uzeti preostale elemente iz drugog.
Ulazni stogovi moraju nakon završetka funkcije ostati nepromijenjeni. Funkcija mora imati prototip:
	Stog *spoji(Stog *stog1, Stog *stog2);

Zadatak 5*:
Napisati funkciju koja æe iz stoga izbaciti sve one brojeve koji se pojavljuju dva ili više puta.
Funkcija ima sljedeæi prototip:
	void izbaci_duple(Stog *stog);

Zadatak 6:
Napisati funkciju koja æe iz stoga izbaciti sva pojavljivanja broja n. 
Funkcija, mora u novi stog, koji je inicijalno prazan, 
ubaciti brojeve koji predstavljaju koliko je broj bio udaljen od originalnog vrha stoga. 
Funkcija ima sljedeæi prototip:
	void izbaci_broj(Stog *stog, int n, Stog *novi);
*/
class Exeption {
	std::string txt;
public:
	Exeption(std::string err)
		:txt(err) {};
	std::string getError() const {
		return this->txt;
	}
};



/*zadatak 0*/
class Stack {
public:
	Stack(); 
	void push(int element);
	void pop();
	int peek() const; 
	bool isEmpty() const; 
	int size() const; 
private:
	int n; 
	std::vector<int> V; 
};


Stack* copy(Stack* original); /*zadatak 1*/
int removeOdd(Stack& fromThisStack); /*zadatak 2*/
/*zadatak 3*/
bool check(int n);
Stack* copySomeNumbers(Stack* original);
Stack* combine(Stack* s1, Stack* s2);	/*zadatak 4*/
void removeDuplicatesFromStack(Stack& s1);	/*zadatak 5*/
void deleteNumber(Stack* fromThisStack, int n, Stack& newOne); /*zadatak 6*/

int main()
{
	
	Stack* a = new Stack; 
	Stack* b = new Stack;

	a->push(62);
	std::cout << a->peek() << " ";
	for (int i = 0; i<10; i++) {
		a->push(rand() % 100); 
		std::cout << a->peek() << " ";
	}
	
	std::cout << "\n"; 
	deleteNumber(a, 62, *b); 

	for (int i = 0; i <= 10; i++) {
		std::cout << b->peek() << " ";
		b->pop(); 
	}
	
	
	return 0;
}
Stack::Stack()
	: n(0) {};

void Stack::push(int element) {
	V.push_back(element);
	n++;
}

void Stack::pop() {
	try {
		if (!isEmpty()) {
			V.pop_back();
			n--;
			return; 
		}
		throw Exeption("Stack underflow!"); 
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n"; 
	}

}

int Stack::peek() const {
	try {
		if (!isEmpty()) {
			return V.back();
		}
		throw Exeption("Stack underflow!");
	}
	catch (Exeption& err) {
		std::cout << err.getError() << "\n";
		return NULL; 
	}
}

bool Stack::isEmpty() const {
	return (n == 0);
}

int Stack::size() const {
	return n;
}

Stack* copy(Stack* current) {
	Stack* temp = new Stack;
	Stack* second = new Stack;

	while (!current->isEmpty()) {
		temp->push(current->peek());
		current->pop();
	}
	while (!temp->isEmpty()) {
		second->push(temp->peek());
		temp->pop();
	}
	delete temp;
	return second;
}

int removeOdd(Stack& current) {
	int n = 0; 
	Stack* temp = new Stack;
	while (!current.isEmpty()) {
		temp->push(current.peek());
		current.pop();
	}
	while (!temp->isEmpty()) {
		if (temp->peek() % 2 != 0) {
			temp->pop();
			n++; 
			continue;
		}
		current.push(temp->peek());
		temp->pop();
	}
	return n; 
}
bool check(int n) {
	return (n == n);
}

Stack* copySomeNumbers(Stack* original) {

	Stack* temp = new Stack;

	while (!original->isEmpty()) {
		if (check(original->peek())) {
			temp->push(original->peek());
			original->pop();
			continue;
		}
		original->pop();
	}
	return temp;
}
Stack* combine(Stack* s1, Stack* s2) {
	Stack* temp = new Stack;

	while (!s1->isEmpty() && !s2->isEmpty()) {
		if (s1->isEmpty()) {
			temp->push(s2->peek());
			s2->pop();
			continue;
		}
		else if (s2->isEmpty()) {
			temp->push(s1->peek());
			s1->pop();
			continue;
		}
		else {
			if ((s1->peek() >= s2->peek())) {
				temp->push(s1->peek());
				s1->pop();
				temp->push(s2->peek());
				s2->pop();
			}
			else {
				temp->push(s2->peek());
				s2->pop();
				temp->push(s1->peek());
				s1->pop();
			}
		}
	}
	return temp;
}
void removeDuplicatesFromStack(Stack& s1) {
	std::list<int> L;
	int n = 0;

	while (!s1.isEmpty()) {
		L.push_back(s1.peek());
		s1.pop();
	}
	std::list<int>::iterator p;
	std::list<int>::iterator temp;
	std::list<int>::iterator p2 = L.begin(); p2++;
	for (p = L.begin(); p != L.end(); ++p) {
		for (p2; p2 != L.end(); ++p2) {
			if (*p == *p2) {
				temp = p2;
				p2++;
				L.erase(temp);
			}
		}
		s1.push(*p);
	}
}

void deleteNumber(Stack* fromThisStack, int n, Stack& newOne) {
	std::list<int> L;
	int counter = 0;

	while (!fromThisStack->isEmpty()) {
		if (fromThisStack->peek() == n) {
			L.push_back(counter); 
			fromThisStack->pop(); 
			counter++; 
			continue; 
		}
		L.push_back(fromThisStack->peek());
		fromThisStack->pop();
		counter++; 
	}

	while (L.size() > 0) {
		newOne.push(L.back());
		L.pop_back();
	}
}
