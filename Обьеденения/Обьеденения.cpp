#include <iostream>

union BI
{
	int x;
	unsigned char b[4];
};
union bytecode
{
	unsigned char x;
	struct {
		unsigned char a0 : 1;
		unsigned char a1 : 1;
		unsigned char a2 : 1;
		unsigned char a3 : 1;
		unsigned char a4 : 1;
		unsigned char a5 : 1;
		unsigned char a6 : 1;
		unsigned char a7 : 1;

	}byte;
};
union code32
{
	int x;
	bytecode b[4];
};
union code64
{
	double x;
	code32 b[2];
};

void print(const BI& a)
{
	std::cout << a.x << ": ";
	for (int i = 0; i < 4; ++i)
	{
		std::cout << (int)a.b[i] << '.';
	}
	std::cout << std::endl;
}
void print(const bytecode& a)
{
	std::cout << (int)a.byte.a7 << (int)a.byte.a6 << (int)a.byte.a5 << (int)a.byte.a4 << (int)a.byte.a3 << (int)a.byte.a2 << (int)a.byte.a1 << (int)a.byte.a0;
}
void print(const code32& a)
{
	std::cout << a.x << ": ";
	for (int i = 3; i >= 0; --i)
	{
		std::cout << (int)a.b[i].x << ".";
	}
	std::cout << ": ";
	for (int i = 3; i >= 0; --i)
	{
		print(a.b[i]); std::cout << '.';
	}
	std::cout << std::endl;
}
void print(const code64& a)
{
	std::cout << a.x << ": ";
	std::cout << ": ";
	for (int i = 1; i >= 0; --i)
	{
		for(int j = 3; j >= 0; --j)
		print(a.b[i].b[j]);
	}
	std::cout << std::endl;
}



int main()
{
	BI ip;
	bytecode ch;

	ip.x = 255;
	ch.x = 255;
	print(ch);
	print(ip);

	code64 x;
	do {
		std::cout << "input nubmer:";
		std::cin >> x.x;
		print(x);
		std::cout << std::endl;
	} while (x.x != 0);
	return 0;
}