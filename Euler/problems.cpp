#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


int sumfOfThreesOrFivesBelow(int x);

int sumOfEvenInsideFibonacciBelow(int x);

long long largestPrimeFactorOf(long long x);
bool isPrime(long long x);

bool isPalindrome(int x);
int findLargestPalindromeFrom(int digits);

int main() {


    int x = findLargestPalindromeFrom(3);
    std::cout << x;



    return 0 ;
}
/**
 * Find the sum of all the multiples of 3 or 5 below 1000.
 */
int sumfOfThreesOrFivesBelow(int n) {
    int sum = 0;
    for(int i=0; i<n; i++){
        if(i % 3 != 0 && i % 5 != 0){
            continue;
        }
        sum += i;
    }
    return sum;
}

/**
 * Find the sum of the even-valued terms inside Fibonacci sequence whose values do not exceed four million.
 */
int sumOfEvenInsideFibonacciBelow(int n) {
    int x = 1, y = 0, z = 0, sum = 0;

    while(x < n){
        std::cout << x << ", ";
        z = x + y;
        y = x;
        x = z;
        if(x % 2 != 0){
            continue;
        }
        sum += x;
    }
    return sum;
}

/**
 * What is the largest prime factor of the number 600851475143
 */
long long largestPrimeFactorOf(long long x){
    int largestPrimeFactor = 0;
    for(long long i = 3; i < sqrt(x); i+= 2){
        if(x % i == 0 && isPrime(i)){
            std::cout << i << " ---------------prime na factor \n";
            largestPrimeFactor = i;
        }
    }
    return largestPrimeFactor;
}

bool isPrime(long long x){
    for(int i=3; i<=sqrt(x); i+=2){
        if(x % i == 0)
            return false;
    }
    return true;
}

/**
 * Find the largest palindrome made from the product of two 3-digit numbers.
 */
bool isPalindrome(int x){
    int n = x, i = 1, z = 0, j = 1;

    while(x){
        z += ((x % 10) * i);
        x /= 10;
        if(x == 0)
            break;
        i *= 10;
    }

    while(n) {
        x += (n / i) * j;
        n = n % i;
        if(n == 0)
            break;
        i /= 10;
        j *= 10;
    }
    return x == z;
}

int findLargestPalindromeFrom(int digits){
    int i = 10, j, palindrome = 0, z;

    i = pow(i, digits);
    i--; j = i, z = i;

    while(i){
        while(j){
            if(isPalindrome(i*j)){
                if(palindrome < (i*j))
                    palindrome = i*j;
            }
            --j;
        }
        j = z;
        --i;
    }
    return palindrome;
}