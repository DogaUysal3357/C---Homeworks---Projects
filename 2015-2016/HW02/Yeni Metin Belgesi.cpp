/*
* File:   main.cpp
* Author: vislab
*
* Created on October 12, 2015, 2:22 PM
*/

#include <cstdlib>
#include <iostream>

using namespace std;


void* lsearch(void* key, void* arr, int sizeof_elem, int n_elem, int(*foo)(void*, void*)
	);

int compare_int(void* el1, void* el2);

int compare_double(void* el1, void* el2);

/*
*
*/
int main(int argc, char** argv) {

	int arr[] = { 4, 2, 1, 5, 0 };
	int size = 5;
	int key = 2;

	int* res = (int*)lsearch(&key, arr, sizeof(int), size, compare_int);

	if (NULL == res) {

		cout << "could not found key!" << endl;

	}
	else
		cout << *res << endl;

	{

		double arr[] = { 4, 2, 1, 5, 0 };
		int size = 5;
		double key = 2;

		double* res = (double*)lsearch(&key, arr, sizeof(double), size, compare_double);

		if (NULL == res) {

			cout << "could not found key!" << endl;

		}
		else
			cout << *res << endl;


	}


	return 0;
}


int compare_double(void* el1, void* el2){


	double* p1 = (double*)el1;
	double* p2 = (double*)el2;

	if (*p1 < *p2) {

		return -1;

	}
	else if (*p1 == *p2) {

		return 0;
	}


	return 1;


}

int compare_int(void* el1, void* el2) {

	int* p1 = (int*)el1;
	int* p2 = (int*)el2;

	if (*p1 < *p2) {

		return -1;

	}
	else if (*p1 == *p2) {

		return 0;
	}


	return 1;

}

void* lsearch(void* key, void* arr, int sizeof_elem, int n_elem, int(*foo)(void*, void*)
	) {

	unsigned char* elem = (unsigned char*)arr;

	unsigned char* end = (unsigned char*)arr + (sizeof_elem * n_elem);


	for (; elem < end; elem += sizeof_elem) {

		if (foo(key, elem) == 0) {

			return elem;

		}

	}

	return NULL;

}