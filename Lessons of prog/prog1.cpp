#include <fstream>

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	std::ifstream FileIn;
	std::ofstream FileOut;
	FileIn.open(argv[1]);
	char* s = new char[81];
	char* s1;
	FileOut.open(argv[2]);
	while (!FileIn.eof())
	{
		s1 = new char[81];
		FileIn.getline(s, 81);
		int i = 0;
		int sp = 0;
		while (s[i])
		{
			if (s[i] == ' ') ++sp;
			++i;
		}
		if (sp == 0)
		{
			FileOut << s << std::endl;
			continue;
		}
		if (i == 80)
		{
			FileOut << s << std::endl;
			continue;
		}
		int k = (80 - i + sp) / sp;
		int ost = 80 - (k-1) * sp - i;
		i = 0;
		int j = 0;
		while (s[i])
		{
			if (s[i] == ' ')
			{
				for (int i = 0; i < k; ++i)
					s1[j++] = ' ';
				if (ost > 0)
				{
					s1[j++] = ' ';
					--ost;
				}
				++i;
			}
			else
			{
				s1[j++] = s[i++];
			}
		}
		s1[j] = s[i];
		FileOut << s1 << std::endl;
	}
}