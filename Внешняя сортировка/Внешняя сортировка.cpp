// Естественное слияние

#include <iostream>
#include <fstream>
#include <ctime>

bool generate_file(int n, const char* fname)
{
	srand(unsigned int(time(0)));
	std::ofstream outFile(fname);
	if (!outFile) return false;
	int i = 0;
	while (n-- > 0) outFile << ' ' << rand() % 10000;
	outFile.close();
	return true;
}
//создание файла с n цифрами

bool isSorted_file(const char* fname)
{
	std::ifstream inFile(fname);
	if (!inFile) throw "Can not open the file";
	int last, current;
	bool answer = true;
	inFile >> last;
	while (inFile.peek() != EOF)
	{
		inFile >> current;
		if (current < last)
		{
			answer = false;
			break;
		}
		last = current;
	}
	inFile.close();
	return answer;
}
//проверка отсортирован ли файл

bool _Split_File(const char* fname, const char* tmp1, const char* tmp2, unsigned long long &c)
{
	std::ifstream inFile(fname);
	if (!inFile) throw "Can not read file";
	std::ofstream outFile[2];
	outFile[0].open(tmp1);
	if (!outFile[0])
	{
		inFile.close();
		throw "Can not write to file";
	}
	outFile[1].open(tmp2);
	if (!outFile[1])
	{
		inFile.close();
		throw "Can not write to file";
	}
	bool result = false;
	int current, last;
	unsigned char num = 0; // Номер файла, в который пишем
	inFile >> last;
	outFile[num] << last;
	while (inFile.peek() != EOF)
	{
		inFile >> current;
		++c;
		if (current < last)
		{
			num = !num;
			result = true;
		}
		outFile[num] << ' ' << current;
		last = current;
	}
	inFile.close();
	outFile[0].close();
	outFile[1].close();
	return result;
}
//разбиение на 2 файла

void _Merge_File(const char* fname, const char* tmp1, const char* tmp2, unsigned long long& c)
{
	std::ofstream outFile(fname);
	if (!outFile) throw "Can not write to file";
	std::ifstream inFile[2];
	inFile[0].open(tmp1);
	if (!inFile[0])
	{
		outFile.close();
		throw "Can not read file";
	}
	inFile[1].open(tmp2);
	if (!inFile[1])
	{
		inFile[0].close();
		outFile.close();
		throw "Can not read file";
	}
	int last, current[2];
	unsigned char num; // номер файла, из которого забираем число
	inFile[0] >> current[0]; 
	inFile[1] >> current[1];
	num = (current[1] < current[0]) ? 1 : 0;
	++c;
	outFile << current[num];
	last = current[num];
	while (inFile[num].peek() != EOF)
	{
		inFile[num] >> current[num];
		bool s1 = current[num] < last;
		bool s2 = current[!num] < last;
		c += 2;
		if (s1 == s2)
		{
			++c;
			num = (current[1] < current[0]) ? 1 : 0;
		}
		else
		{
			if (s1 == true) num = !num;
		}
		outFile << ' ' << current[num];
		last = current[num];
	}
	outFile << ' ' << current[!num];
	num = !num;
	while (inFile[num].peek() != EOF)
	{
		inFile[num] >> last;
		outFile << ' ' << last;
	}
	outFile.close();
	inFile[0].close();
	inFile[1].close();
}

int MergefileSorting(const char* fname, unsigned long long& c)
{
	char tmp1[] = "_temp_file_1.txt";
	char tmp2[] = "_temp_file_2.txt";
	int counter = 0;
	bool key;
	do
	{
		key = _Split_File(fname, tmp1, tmp2, c);
		if (key)
		{
			_Merge_File(fname, tmp1, tmp2, c);
		}
		++counter;
	} while (key);
	return counter;
}

int main()
{
	char fname[] = "data.txt";

	if (!generate_file(100000, fname))
	{
		std::cout << "Can not create file for the test!" << std::endl;
		return 1;
	}

	try
	{
		unsigned long long c = 0; //операции <, >
		int N = MergefileSorting(fname, c);
		if (isSorted_file(fname))
		{
			std::cout << fname << " is sorted" << std::endl;
			std::cout << "Total " << N << " splits" << std::endl;
			std::cout << c << " comparisons";
		}
		else
		{
			std::cout << "File " << fname << " is not sorted" << std::endl;
		}
	}catch(const char *error)
	{
		std::cout << "ERROR: " << *error << std::endl;
	}

	return 0;
}

