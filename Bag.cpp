#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	lenU = 0;
	lenP = 0;
	capP = 1;
	capU = 1;
	U = new TElem[capU];
	P = new TElem[capP];
}
// Theta(1) 

void Bag::add(TElem elem) {
	resize(U, lenU, capU);
	resize(P, lenP, capP);
	if (search(elem) == false) {
		U[lenU] = elem;
		lenU++;
	}
	P[lenP] = searchIndex(elem);
	lenP++;
}
//Best Case : Theta(1) ,  Worst Case : Theta(lenU) => Total Complexity : O(lenU)

void Bag::resize(TElem *&arr, int len, int &cap) {
	if (len == cap) {
		cap = cap * 2;
		TElem* newarray = new TElem[cap];
		for (int i = 0; i <= len; i++) {
			newarray[i] = arr[i];
		}
		delete[] arr;
		arr = newarray;
	}
}
//Best Case : Theta(1) ,  Worst Case : Theta(len) => Total Complexity : O(len)

int Bag::searchIndex(TElem elem) {
	for (int i = 0; i < lenU; i++) {
		if (U[i] == elem) {
			return i;
		}
	}
}
//Best Case : Theta(1) ,  Worst Case : Theta(lenU) => Total Complexity : O(lenU)

bool Bag::remove(TElem elem) {
	for (int i = 0; i < lenU; i++) {
		if (U[i] == elem) {
			for (int j = 0; j < lenP; j++) {
				if (P[j] == i) {
					for (int k = j; k < lenP-1; k++) {
						P[k] = P[k + 1];
						
					}
					j = lenP;
				}
			}
			lenP = lenP - 1;
			if (nrOccurrences(elem) == 0) {
				for (int k = i; k < lenU-1; k++) {
					U[k] = U[k + 1];
				}
				lenU = lenU - 1;
				for (int m = 0; m < lenP; m++) {
					if (P[m] > i) {
						P[m] = P[m] - 1;
					}
				}
			}
			return 1;
		}
		 
	}
	return 0;
}
//Best Case : Theta(lenP) ,  Worst Case : Theta(lenP) => Total Complexity : O(lenP)

bool Bag::search(TElem elem) const {
	for (int i = 0; i < lenU; i++) {
		if (U[i] == elem) {
			return true;
		}
	}
	return false; 
}
//Best Case : Theta(1) ,  Worst Case : Theta(lenU) => Total Complexity : O(lenU)

int Bag::nrOccurrences(TElem elem)  {
	int count = 0;
	for (int i = 0; i < lenP; i++) {
		if (U[P[i]] == elem) {
			count++;
		}
	}
	return count; 
}
//Best Case : Theta(1) ,  Worst Case : Theta(lenP) => Total Complexity : O(lenP)

int Bag::size() const {
	
	return lenP;
}
// Theta(1) 

bool Bag::isEmpty() const {
	if (lenU == 0) {
		return 1;
	}
	return 0;
}
// Theta(1) 

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}
// Theta(1) 

Bag::~Bag() {
	
	delete[] U;
	delete[] P;
	
	
}
// Theta(1) 
