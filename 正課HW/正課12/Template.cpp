// Name: ±i¥Ã©Ó	
// Date: 2020.05.21
// Last Update:2020.05.21
// Problem statement: Template Binary Search
#include<iostream>


template<class T>
void ItrBinarySearch(const T a[], int first, int last, T key, bool& found, int& location) {
	int left = first;
	int right = last;
	int mid;
	while (left <= right) {
		mid = left + (right - left) / 2;
		if (a[mid] == key) {
			found = true;
			location = mid;
			return;
		}
		else if (a[mid] < key) {
			left = mid + 1;
		}
		else if (a[mid] > key) {
			right = mid - 1;
		}
	}
	found = false;

}




template<class T>
void RecBinarySearch(const T a[], int first, int last, T key, bool& found, int& location) {
	int left = first;
	int right = last;
	if (left <= right) {
		int mid = left + (right - left) / 2;
		if (a[mid] == key) {
			found = true;
			location = mid;
			return;
		}
		else if (a[mid] < key) {
			RecBinarySearch(a, mid+1, last, key, found, location);
		}
		else if (a[mid] > key) {
			RecBinarySearch(a, first, mid - 1, key, found, location);
		}
	}
	else {
		found = false;
		return;
	}
}