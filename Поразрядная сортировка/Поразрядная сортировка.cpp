// Поразрядная сортировка

#include <iostream>
#include <ctime>

#define each(i,x) for(i = 0; i < x; ++i)

void PrintA(int* A, int n)
{
	int i;
	each(i, n) std::cout << A[i] << ' ';
	std::cout << std::endl;

}

void randomArray(int* A, int n)
{
	srand(unsigned int(time(0)));
	int i;
	each(i, n) A[i] = rand() % 1000 - 500;
}

bool isSorted(int* A, int n)
{
	int i;
	each(i, n-1) if (A[i + 1] < A[i]) return false;
	return true;
}

void lsd_radix_sort(unsigned int* M, int len)
{
	if (len < 2) return;
	unsigned int mask = 1;
	unsigned int* tmp = new unsigned int[len];
	unsigned int* A = M;
	unsigned int* B = tmp;
	int j;
	while (mask)
	{
		int cnt0 = 0, cnt1 = 0; // номера ячек, где начинаются 0 и 1
		each(j, len)
		{
			if (!(A[j] & mask)) ++cnt1;
		}
		each(j, len)
		{
			if (A[j] & mask) B[cnt1++] = A[j];
			else B[cnt0++] = A[j];
		}
		mask <<= 1;
		std::swap(A, B);
	}
	if (B == M)
	{
		each(j, len)
			M[j] = tmp[j];
	}
	delete[] tmp;

}

unsigned int lsd_radix_sort_mem_free(unsigned int* M, int len)
{
	if (len < 2) return 0;
	unsigned int perms_cnt = 0;
	unsigned int mask = 1;
	int j;
	while (mask)
	{
		int cnt1 = 1; // номера ячек, где начинаются 1
		if (M[0] & mask) cnt1 = 0;
		for (int j = 1; j < len; ++j)
		{
			if (!(M[j] & mask))
			{
				if (j > cnt1)
				{
					unsigned int tmp = M[j];
					++perms_cnt;
					for (int k = j; k > cnt1; --k)
					{
						M[k] = M[k - 1];
						++perms_cnt;
					}
					M[cnt1] = tmp;
					++perms_cnt;
				}
				++cnt1;
			}
		}
		mask <<= 1;
	}
	return perms_cnt;
}

void msd_radix_sort(unsigned int* from, int len, unsigned int mask, unsigned int& c)
{
	if (len < 2 || mask == 0) return;
	int i = 0;
	int j = len - 1;
	while (i < j)
	{
		while (i < len && !(from[i] & mask)) ++i;
		while (j >= 0 && (from[j] & mask)) --j;
		if (i < j)
		{
			std::swap(from[i], from[j]);
			c += 3;
		}
	}
	mask >>= 1;
	msd_radix_sort(from, i, mask, c);
	msd_radix_sort(from, len - i, mask, c);
}

unsigned int radixSort3(int* A, int n)
{
	unsigned int* x = (unsigned int*)A;
	int i;
	unsigned int cnt = 0;
	each(i, n) x[i] ^= INT_MIN;
	msd_radix_sort(x, n, INT_MIN, cnt);
	each(i, n) x[i] ^= INT_MIN;
	return cnt;
}

int radixSort(int* A, int n)
{
	unsigned int* x = (unsigned int*) A;
	int i;
	each(i, n) x[i] ^= INT_MIN;
	lsd_radix_sort(x, n);
	each(i, n) x[i] ^= INT_MIN;
	return n * 32;
}

unsigned int radixSort2(int* A, int n)
{
	unsigned int* x = (unsigned int*)A;
	int i;
	each(i, n) x[i] ^= INT_MIN;
	unsigned int cnt = lsd_radix_sort_mem_free(x, n);
	each(i, n) x[i] ^= INT_MIN;
	return cnt;
}

int main()
{
	double g = 9.8;
	int a = g;
	int n;
	do
	{
		std::cout << "size = ";
		std::cin >> n;
		std::cout << std::endl;
	} while (n < 1);
	int* M = new int[n];
	randomArray(M, n);
	std::cout << "perms1 = " << radixSort(M, n) << std::endl;
	std::cout << "perms2 = " << radixSort2(M, n) << std::endl;
	std::cout << "perms3 = " << radixSort3(M, n) << std::endl;
	return 0;
}

