#include <iostream>
#include <fstream>
//-----------------------------------------------------------------------------------------------------
char Base64Aplhabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
//-----------------------------------------------------------------------------------------------------
char Base64Char(unsigned char b)
{
	b &= 0x3F;
	//return Base64Aplhabet[b];
	if (b < 26) return 'A' + b;
	else if (b < 52) return 'a' + (b - 26);
	else if (b < 62) return '0' + (b - 52);
	else if (b == 62) return '+';
	else return '/';
}
//------------------------------------------------------------------------------------------------------
int Base64Encode(char* InStr, int len, char* OutStr)
{
	// Function returns количество символос в строке OutStr
	int i = 0, j = 0; // i - index InStr, j - index OutStr
	unsigned char a1, a2, a3;
	unsigned char b1, b2, b3, b4;
	for (i = 0; i < len; i += 3)
	{
		a1 = a2 = a3 = 0;
		a1 = InStr[i];
		if (i + 1 < len) a2 = InStr[i + 1];
		if (i + 2 < len) a3 = InStr[i + 2];
		b1 = a1 >> 2;
		b2 = ((a1 & 0x3) << 4) | (a2 >> 4);
		b3 = ((a2 & 0xF) << 2) | (a3 >> 6);
		b4 = a3 & 0x3F;
		OutStr[j++] = Base64Char(b1);
		OutStr[j++] = Base64Char(b2);
		OutStr[j++] = (i + 1 < len) ? Base64Char(b3) : '=';
		OutStr[j++] = (i + 2 < len) ? Base64Char(b4) : '=';

	}
	return j;
}
//-------------------------------------------------------------------------------------------------------------
void EncodeFile2Base64(std::ifstream& FileIn, std::ofstream& FileOut)
{
	char inStr[3], outStr[4];
	int s, count = 0;
	while (FileIn.peek() != EOF)
	{
		FileIn.read(inStr, 3); // Try to read 3 bytes
		s = FileIn.gcount(); // Сколько было прочитано при попытке прочитать
		s = Base64Encode(inStr, s, outStr);
		FileOut.write(outStr, s);
		count += s;
		if (count >= 80)
		{
			FileOut << std::endl;
			count = 0;
		}
	}
}
//-----------------------------------------------------------------------------------------------------
unsigned char Base64Code(char c)
{
	if (c >= 'A' && c <= 'Z') return c - 'A';
	else if (c >= 'a' && c <= 'z') return c - 'a' + 26;
	else if (c >= '0' && c <= '9') return c - '0' + 52;
	else if (c == '+') return 62;
	else if (c == '/') return 63;
	else return 64;
}
//----------------------------------------------------------------------------------------------------
bool isBase64(char c)
{
	if (c >= 'A' && c <= 'Z') return true;
	else if (c >= 'a' && c <= 'z') return true;
	else if (c >= '0' && c <= '9') return true;
	else if (c == '+') return true;
	else if (c == '/') return true;
	else if (c == '=') return true;
	else return false;
}
//-----------------------------------------------------------------------------------------------------
int Base64Decode(char* inStr, int len, char* outStr)
{
	if (len % 4 > 0) return 0;
	int j = 0; // actual position of output string
	int lishnee = 0;
	for (int i = 0; i < len; i += 4)
	{
		unsigned char b1, b2, b3, b4;
		b1 = Base64Code(inStr[i]);
		b2 = Base64Code(inStr[i+1]);
		b3 = Base64Code(inStr[i+2]);
		b4 = Base64Code(inStr[i+3]);
		if (b3 == 64)
		{
			b3 = 0;
			b4 = 0;
			lishnee = 2;
		}
		else if (b4 == 64)
		{
			b4 = 0;
			lishnee = 1;
		}
		outStr[j++] = (b1 << 2) | (b2 >> 4);
		outStr[j++] = (b2 << 4) | (b3 >> 2);
		outStr[j++] = (b3 << 6) | b4;
		if (lishnee) break;
	}
	return j - lishnee;
}
//------------------------------------------------------------------------------------------------------
void DecodeFileFromBase64(std::ifstream& FileIn, std::ofstream& FileOut)
{
	char inStr[4], outStr[3];
	int cnt = 0, ch, s;
	while ((ch = FileIn.get()) != EOF)
	{
		if (isBase64(ch))
		{
			inStr[cnt++] = ch;
			if (cnt == 4)
			{
				s = Base64Decode(inStr, 4, outStr);
				FileOut.write(outStr, s);
				cnt = 0;
			}
		}
	}
}
//-----------------------------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
	char test[] = "test string";
	char* out = new char[128];
	std::cout << test << std::endl;
	int len = Base64Encode(test, strlen(test), out);
	out[len] = '\0';
	std::cout << out << std::endl;
	char* out2 = new char[128];
	int len2 =  Base64Decode(out, len, out2);
	out2[len2] = '\0';
	std::cout << out2 << std::endl;
	
	try
	{
		if (argc < 4) throw 1;

		std::ifstream FileIn;
		std::ofstream FileOut;

		if (strcmp(argv[1], "-e") == 0)
		{
			//encode
			FileIn.open(argv[2], std::ios_base::binary);
			if (!FileIn) throw 2;

			FileOut.open(argv[3]);
			if (!FileOut)
			{
				FileIn.close();
				throw 3;
			}
			EncodeFile2Base64(FileIn, FileOut);
		}
		else if (strcmp(argv[1], "-d") == 0)
		{
			//decode
			FileIn.open(argv[2]);
			if (!FileIn) throw 2;

			FileOut.open(argv[3], std::ios_base::binary);
			if (!FileOut)
			{
				FileIn.close();
				throw 3;
			}
			DecodeFileFromBase64(FileIn, FileOut);
		}
		else throw 1;
		FileIn.close();
		FileOut.close();
	}
	catch (int error)
	{
		switch (error)
		{
		case 1:
			std::cout << "Use " << argv[0] << " -e inputFileName outputFileName" << std::endl;
			std::cout << "Use " << argv[0] << " -d inputFileName outputFileName" << std::endl;
			return 1;
		case 2:
			std::cout << "Can not open file " << argv[2] << std::endl;
			return 2;
		case 3:
			std::cout << "Can not open file " << argv[3] << std::endl;
			return 3;
		}
	}
	return 0;
}
