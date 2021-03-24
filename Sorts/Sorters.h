#ifndef _MYSORTS2019_

#define _MYSORTS2019_

#include <time.h>
#include <utility>	

template <typename T>
void BubbleSort(T* A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	bool isSorted;
	for (int i = 0; i < n - 1; ++i)
	{
		isSorted = true;
		for (int j = n - 1; j > i; --j)
		{
#ifdef SORTSTAT
			++c1;
#endif
			if (A[j] < A[j - 1])
			{
				std::swap(A[j], A[j - 1]);
#ifdef SORTSTAT
				c2 += 3;
#endif
				isSorted = false;
			}
		}
		if (isSorted == true) break;
	}
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
}

template <typename T>
void ChooseSort(T* A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	for (int i = 0; i < n - 1; ++i)
	{
		int min_ind = i;
		for (int j = i + 1; j < n; ++j)
		{
#ifdef SORTSTAT
			++c1;
#endif
			if (A[j] < A[min_ind]) 
			{
				min_ind = j; 
#ifdef SORTSTAT
				++c2;
#endif
			}
		}
		++c1;
		if (min_ind > i) 
		{
			std::swap(A[min_ind], A[i]);
#ifdef SORTSTAT
			c2 += 3;
#endif
		}
	}
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
}

template <typename T>
void InsertSort(T *A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	T tmp;
	for (int i = 1; i < n; ++i)
	{
#ifdef SORTSTAT
		++c2;
#endif
		tmp = A[i];
		int j;
		for (j = i; j > 0; --j)
		{
#ifdef SORTSTAT
			++c1;
#endif
			if (tmp < A[j - 1])
			{
#ifdef SORTSTAT
				++c2;
#endif
				A[j] = A[j - 1];
			}
			else break;
		}
		if (i != j) 
		{
#ifdef SORTSTAT
			++c2;
#endif
			A[j] = tmp;
		}
	}
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
}

template <typename T>
void InsertSortAdvanced(T* A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	for (int i = 1; i < n; ++i)
	{
		T tmp;
		int left = 0, right = i, mid;
		do 
		{
			mid = left + (right - left) / 2; // деление пополам без переполнения
#ifdef SORTSTAT
			++c1;
#endif
			if (A[i] < A[mid])
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		} while (left < right);
		if (right >= 0)
		{
#ifdef SORTSTAT
			++c1;
#endif
			if (A[i] < A[right])
				--right;
		}
		if (i > right + 1)
		{
#ifdef SORTSTAT
			++c2;
#endif
			tmp = A[i];
			for (int j = i; j > right + 1; --j)
			{
#ifdef SORTSTAT
				++c2;
#endif
				A[j] = A[j - 1];
			}
#ifdef SORTSTAT
			++c2;
#endif
			A[right + 1] = tmp;
		}
	}
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
}

template <typename T>
void QuickSortRec(T* A, int n)
{
	int left = 0, right = n - 1;
	int p_ind = left + (right - left) / 2;
	T p = A[p_ind];
	int i = left, j = right;
	while (i < j)
	{
		while (A[i] < p)
		{ 
			++i; 
		}
		while (p < A[j])
		{ 
			--j;
		}
		if (i < j)
		{
			std::swap(A[i], A[j]);
			++i; --j;
		}
		else if (i == j)
		{
			++i; --j;
		}
	}
	if (p_ind < i)
	{
		if (i < right) QuickSortRec(A + i, right - i + 1);
		if (j > left) QuickSortRec(A + left, j - left + 1);
	}
	else
	{
		if (j > left) QuickSortRec(A + left, j - left + 1);
		if (i < right) QuickSortRec(A + i, right - i + 1);
	}
}

template <typename T>
void QuickSort(T* A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	int N = n, size = 1;
	while (N > 0)
	{
		N >>= 1;
		++size;
	}
	int* StackLeft = new int[size];
	int* StackRight = new int[size];
	int LastInStack = -1;
	++LastInStack;
	StackLeft[LastInStack] = 0;
	StackRight[LastInStack] = n - 1;
	while (LastInStack > -1)
	{
		int left = StackLeft[LastInStack];
		int right = StackRight[LastInStack];
		--LastInStack;
		int pIndex = left + (right - left) / 2;
#ifdef SORTSTAT
		++c2;
#endif
		T p = A[pIndex];
		int i = left, j = right;
		while (i < j)
		{
			while (A[i] < p)
			{
#ifdef SORTSTAT
				++c1;
#endif
				++i;
			}
			while (p < A[j])
			{
#ifdef SORTSTAT
				++c1;
#endif
				--j;
			}
			if (i < j)
			{
				std::swap(A[i], A[j]);
#ifdef SORTSTAT
				c2 += 3;
#endif
				++i; --j;
			}
			else if (i == j)
			{
				++i; --j;
			}
		}
		if (i > pIndex)
		{
			if (j > left)
			{
				++LastInStack;
				StackLeft[LastInStack] = left;
				StackRight[LastInStack] = j;
			}
			if (i < right)
			{
				++LastInStack;
				StackLeft[LastInStack] = i;
				StackRight[LastInStack] = right;
			}
		}
		else
		{
			if (i < right)
			{
				++LastInStack;
				StackLeft[LastInStack] = i;
				StackRight[LastInStack] = right;
			}
			if (j > left)
			{
				++LastInStack;
				StackLeft[LastInStack] = left;
				StackRight[LastInStack] = j;
			}
		}
	}
	delete[] StackLeft;
	delete[] StackRight;
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
}

template <typename T>
void _Merge(T* A, int first, int middle, int last, unsigned long long& c1, unsigned long long& c2)
{
	int size = last - first + 1;
	T* tmp = new int[size];
	int start1 = first;
	int end1 = middle;
	int start2 = middle + 1;
	int end2 = last;
	int i = 0; //индекс в массиве tmp
	while (start1 <= end1 && start2 <= end2)
	{
#ifdef SORTSTAT
		++c1;
#endif
		if (A[start1] < A[start2])
			tmp[i++] = A[start1++];
		else
			tmp[i++] = A[start2++];
	}
	while (start1 <= end1) 
	{ 
		tmp[i++] = A[start1++];
#ifdef SORTSTAT
		++c2;
#endif
	}
	while (start2 <= end2) 
	{ 
		tmp[i++] = A[start2++];
#ifdef SORTSTAT
		++c2;
#endif
	}
	// Копируем обратно из tmp в A
	i = 0;
	while (first <= last)
	{
		A[first++] = tmp[i++];
#ifdef SORTSTAT
		++c2;
#endif
	}
	delete[] tmp;
}

template <typename T>
void _Split(T* A, int first, int last, unsigned long long &c1, unsigned long long &c2)
{
	if (first < last)
	{
		int middle = first + (last - first) / 2;
		_Split(A, first, middle, c1, c2);
		_Split(A, middle + 1, last, c1, c2);
		_Merge(A, first, middle, last, c1, c2);
	}
}

template <typename T>
void MergeSort(T* A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	_Split(A, 0, n - 1, c1, c2);
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
} 
//доп память + рекурсия

template <typename T>
void MergeSortAdvanced(T* A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	T* tmp = new T[n];
	T* from = A;
	T* to = tmp;
	for (int step = 1; step < n; step *= 2)
	{
		int start1 = 0, end1, start2, end2;
		int i = 0; // Индекс в tmp
		for (int start = 0; start < n; start += 2 * step)
		{
			start1 = start;
			end1 = start1 + step;
			end1 = (end1 < n) ? end1 : n;
			start2 = end1;
			end2 = start2 + step;
			end2 = (end2 < n) ? end2 : n;
			while (start1 < end1 && start2 < end2)
			{
				to[i++] = (from[start1] < from[start2]) ? from[start1++] : from[start2++];
#ifdef SORTSTAT
				++c1;
#endif
#ifdef SORTSTAT
				++c2;
#endif
			}
			while (start1 < end1)
			{
#ifdef SORTSTAT
				++c2;
#endif
				to[i++] = from[start1++];
			}
			while (start2 < end2)
			{
#ifdef SORTSTAT
				++c2;
#endif
				to[i++] = from[start2++];
			}
		}
		std::swap(from, to);
#ifdef SORTSTAT
		c2 += 3;
#endif
	}
	if (from != A)
	{
		//Копировать из отсортированного массива в А
		int i = 0;
		while (i < n)
		{
#ifdef SORTSTAT
			++c2;
#endif
			A[i] = from[i++];
		}
		delete[] tmp;
	}
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
}
//Доп память

template <typename T>
void HeapSort(T* A, int n)
{
#ifdef SORTSTAT
	unsigned long long c1 = 0, c2 = 0;
	clock_t t = clock();
#endif
	//make heap
	for (int i = 1; i < n; ++i)
	{
		int pos = i;
		while (pos != 0)
		{
#ifdef SORTSTAT
			++c1;
#endif
			if (A[(pos - 1) / 2] < A[pos])
			{
#ifdef SORTSTAT
				c2 += 3;
#endif
				std::swap(A[(pos - 1) / 2], A[pos]);
					pos = (pos - 1) / 2;
			}
			else break;
		}
	}
	//shift down each elem
	int size = n; // текущий размер пирамиды
	for (int i = 1; i < n; ++i)
	{
#ifdef SORTSTAT
		c2 += 3;
#endif
		std::swap(A[0], A[size - 1]);
		--size;
		int pos = 0;
		while (2 * pos + 1 < size)
		{
			int posMaxChild = 2 * pos + 1;
			if (posMaxChild + 1 < size)
			{
#ifdef SORTSTAT
				++c1;
#endif
				if (A[posMaxChild] < A[posMaxChild + 1])
					++posMaxChild;
			}
#ifdef SORTSTAT
			++c1;
#endif
			if (A[pos] < A[posMaxChild])
			{
#ifdef SORTSTAT
				c2 += 3;
#endif
				std::swap(A[pos], A[posMaxChild]);
				pos = posMaxChild;
			}
			else break;
		}
	}
#ifdef SORTSTAT
	t = clock() - t;
	std::cout << "< " << c1 << ", = " << c2 << ", tics " << t << std::endl;
#endif
}
//Не требует доп памяти

#endif // !_MYSORTS2019_