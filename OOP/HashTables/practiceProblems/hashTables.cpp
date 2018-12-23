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
