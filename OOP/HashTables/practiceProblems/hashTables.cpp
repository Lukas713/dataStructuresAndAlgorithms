#include "pch.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>

/*
1) https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/pair-sums/
*/
bool pairSum(int* field, int k, int size);

/*
2) https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/frequency-of-students/
*/
void FrequencyofStudents(int n);

/*
3) https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/notebook-pages-dbad75a5/
*/ 
void SimilarChocolates(int n);

int numberOfDivisors(int x);

/*
4) https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/cricket-balls/
*/
void cricketBalls(int testCases, int k);

/*
5) https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/all-vowels-2/
*/
void allVowels(int n);

/*
6) https://www.hackerearth.com/practice/data-structures/hash-tables/basics-of-hash-tables/practice-problems/algorithm/n-co-ordinates-map-practice/
*/
void NCoCOrdinates(int n);

int main()
{
	
	int size; int k;
	int field[] = { 9, 8, 1, 2, 6, 3, 7, 4, 5,  9, 8, 1, 2, 6, 3, 7, 4, 5,  9, 8, 1, 2, 6, 3, 7, 4, 5,  9, 8, 1, 2, 6, 3, 7, 4, 5 };
	
	pairSum(field, 13, 36); 
	







	return 0;
}

/*
3 @params : int array, searching sum, size of array
1) creates map with false values
2) insert elements into map
3) traverse witin map, if finds missing operand, return true else continue
*/
bool pairSum(int* field, int k, int size) {
	//creates map with false values
	std::unordered_map<int, bool> a(size);

	//insert elements into map
	for (int i = 0; i < size; i++)
		a.insert(std::make_pair(field[i], false));
		
	//traverse witin map, if finds missing operand, return true else continue
	std::unordered_map<int, bool>::iterator p;
	for (p = a.begin(); p != a.end(); ++p) {
		if (a.find(k - (*p).first) != a.end()) {
			std::cout << "Yes";
			return true;
		}
	}
	std::cout << "No";
	return false;
}
/*
@param int
1) ceates map
2) inserts string names as keys with int values
3) if finds name, increment integer value by one 
	else insert element
4) display map wit iterator
*/
void FrequencyofStudents(int n) {

	std::map<std::string, int> map; 
	std::map<std::string, int>::iterator p; 
	std::string name; 

	for (int i = 0; i < n; ++i) {
		std::cout << "enter name: "; 
		std::cin >> name; 
		if (map.find(name) != map.end()) {
			p = map.find(name); 
			p->second += 1; 
			continue; 
		}
		map.insert(std::pair<std::string, int>(name, 1)); 
	}

	for (p = map.begin(); p != map.end(); ++p) 
		std::cout << p->first << " : " << p->second << "\n"; 
}
/*
@param int
create's hash table
fill it with numbers as key and divisors as value
display table
*/
void SimilarChocolates(int n) {

	std::unordered_map<int, int> map;
	int x;

	for (int i = 0; i < n; i++) {
		std::cin >> x;
		map.insert(std::make_pair(x, numberOfDivisors(x)));
	}

	std::unordered_map<int, int>::iterator p;
	for (p = map.begin(); p != map.end(); ++p)
		std::cout << "\n" << (*p).first << " : " << (*p).second;
}
int numberOfDivisors(int x) {
	int n = 0;
	for (int i = 1; i <= x; i++) {
		if (x % i == 0)
		n++;
	}
	return n;
}
/*
2 @params: integers
open test case, create's map and iterator
user inserts element into map, if there is equal complement, increment counter by one 
*/
void cricketBalls(int testCases, int k) {

	while (testCases > 0) {
		
		int counter = 0;	
		int n; 
		

		std::cout << "Enter number of boxes "; 
		std::cin >> n; 
		std::unordered_map<int, bool> map(n); 
		std::unordered_map<int, bool>::iterator p; 

		for (int i = 0; i < n; i++) {
			int x; 

			std::cin >> x; 
			p = map.find(k - x); 
			
			if (map.find(k - x) != map.end())
				counter++; 
			map.insert(std::make_pair(x, false)); 
		}
		std::cout << counter; 
		--testCases;
	}
}
/*
@param : integer
cout YES if string contains all vowels
NO otherwise
no return value
*/
void allVowels(int n) {
	std::string word; 
	std::cin >> word; 
	std::unordered_map<char, int> map; 

	for (char a : word) {
		if (a == 'a' || a == 'e' || a == 'i' || a == 'o' || a == 'u') {
			if (map.find(a) != map.end()) {
				(*map.find(a)).second += 1; 
				continue; 
			}
			map.insert(std::make_pair(a, 1)); 
		}
	}

	if (map.size() < 5) {
		std::cout << "NO"; 
		return; 
	}
	std::cout << "YES"; 
}

/*
@param integer
n times insert coordinates (x, y)
creates map and inserts coordinates into map with key as pair 
and value as number of ocurences
print table
no return value
*/
void NCoCOrdinates(int n) {

	std::map<std::pair<int, int>, int> map;

	for (int i = 0; i < n; ++i) {

		int x, y;
		std::cin >> x;
		std::cin >> y;

		if (map.find(std::make_pair(x, y)) != map.end()) {
			(*map.find(std::make_pair(x, y))).second += 1;
			continue;
		}
		map.insert(std::make_pair(std::make_pair(x, y), 1)); //creates pair of pairs of int's and int
	}

	std::map<std::pair<int, int>, int>::iterator p;
	for (p = map.begin(); p != map.end(); ++p)
		std::cout << p->first.first << " " << p->first.second << " " << p->second << "\n";
}
