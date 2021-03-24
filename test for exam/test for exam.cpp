#include <iostream>

int main(int argc, char* argv[])
{
	char FileInName[50] = "input.txt";
	char FileOutName[50] = "output.txt";
	if (argc > 0)
	{
		strcpy_s(FileInName, argv[1]);
		strcpy_s(FileOutName, argv[2]);
	}

	std::cout << FileInName << std::endl << FileOutName;
}

