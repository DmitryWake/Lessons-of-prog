#include <iostream>
#include <ctime>
#include <utility>

#define SORTSTAT
#include "Sorters.h"

void RandomArray(int *A, int n)
{
	for (int i = 0; i < n; ++i)
	{
		A[i] = rand() % 9000 + 1000;
	}
}

template <typename T>
void print(T *A, int n, const char* str = "")
{
	std::cout << str;
	for (int i = 0; i < n; ++i)
	{
		std::cout << A[i] << ' ';
	}
	std::cout << std::endl;
}

void SortedArray(int *A, int n)
{
	for (int i = 0; i < n; ++i)
	{
		A[i] = i;
	}
}

void ReversedArray(int* A, int n)
{
	for (int i = 0; i < n; ++i)
		A[i] = n - i;
}

void NearlyReversedArray(int* A, int n)
{
	for (int i = 0; i < n; ++i) A[i] = n - i;
	for (int i = 0; i < n / 2; ++i) std::swap(A[i], A[i + 1]);
}

void QuickSortKillerArray(int* A, int n)
{
	for (int i = 0; i < n; ++i)
	{
		A[i] = i;
	}
	for (int i = 2; i < n; ++i) std::swap(A[i], A[i/2]);

}

template <typename T>
bool isSorted(T* A, int n)
{
	for (int i = 1; i < n; ++i)
		if (A[i] < A[i - 1]) return false;
	return true;
}

void SortArray(void (*sorter)(int*, int), int* A, int n, const char* arrayname)
{
	std::cout << "--- Array: " << arrayname << std::endl;
	if (n < 25) print(A, n, "Before: ");
	sorter(A, n);
	if (!isSorted(A, n)) std::cout << "ERROR: Not sorted!";
	if (n < 25) print(A, n, "After sort: ");
}

void tester(void (*sorter)(int*, int), const int* R, int n, const char* name)
{
	std::cout << "====== Method: " << name << "==========" << std::endl;
	int* A = new int[n];
	SortedArray(A, n);
	SortArray(sorter, A, n, "Sorted");

	ReversedArray(A, n);
	SortArray(sorter, A, n, "Reversed");

	for (int i = 0; i < n; ++i) A[i] = R[i];
	SortArray(sorter, A, n, "Random");

	NearlyReversedArray(A, n);
	SortArray(sorter, A, n, "Nearly Reversed");

	QuickSortKillerArray(A, n);
	SortArray(sorter, A, n, "QuickSortKillerArray");
	delete[] A;
}

int main()
{
#ifdef _DEBUG
	std::cout << "=============DEBUG version=============" << std::endl;
#endif // _DEBUG

	int n;
	do { std::cout << "Array size: "; std::cin >> n; std::cout << std::endl; } while (n < 1);
	int* A = new int[n];
	RandomArray(A, n);
	
	tester(BubbleSotr, A, n, "Bubble sorting");
	tester(ChooseSort, A, n, "Choose sorting");
	tester(InsertSort, A, n, "Insert sorting");
	tester(InsertSortAdvanced, A, n, "Insert Advanced sorting");
	//tester(QuickSortRec, A, n, "Quick Rec sorting"); falling
	tester(QuickSort, A, n, "Quick sorting");
	tester(MergeSort, A, n, "Merge sorting");
	tester(MergeSortAdvanced, A, n, "Merge Advanced Sorting");
	tester(HeapSort, A, n, "Heap Sorting");

	delete[] A;
	return 0;
}

