#include <iostream>
#include <fstream>

struct student {
	int id;
	char surname[32], name[32];
	unsigned char marks[5];
};

void print(const student &st)
{
	std::cout << "st000" << st.id << ": ";
	std::cout << st.surname << " " << st.name << ". ";
	std::cout << "Marks: ";
	for (int i = 0; i < 5; ++i)
	{
		std::cout << (int)st.marks[i] << ' ';
	}
	std::cout << std::endl;
}

std::ostream& operator<< (std::ostream& out, const student& st)
{
	out << "st0" << st.id << ": ";
	out << st.surname << " " << st.name << ". ";
	out << "Marks: ";
	for (int i = 0; i < 5; ++i)
	{
		out << (int)st.marks[i] << ' ';
	}
	out << std::endl;
	return out;
}
std::istream& operator>> (std::istream& in, student& st)
{
	std::cout << "Enter st";
	in >> st.id; in.ignore();
	std::cout << "Surname: ";
	in.getline(st.surname, 32);
	std::cout << "Name: ";
	in.getline(st.name, 32);
	for (int i = 0; i < 5; ++i)
	{
		st.marks[i] = 0;
	}
	return in;
}

void setMark(student& st)
{
	std::cout << "Input 5 marks for student ";
	std::cout << st.surname << " " << st.name << ": ";
	int tmp;
	for (int i = 0; i < 5; ++i)
	{
		std::cin >> tmp;
		st.marks[i] = tmp;
		std::cin.ignore();
	}
}

int menu()
{
	for (int i = 0; i < 20; ++i) std::cout.put('*');
	std::cout << std::endl;
	std::cout << "1. Create database." << std::endl;
	std::cout << "2. Print database." << std::endl;
	std::cout << "3. Export to txt." << std::endl;
	std::cout << "4. Save DB." << std::endl;
	std::cout << "5. Read DB." << std::endl;
	std::cout << "0. Exit." << std::endl;
	int tmp;
	std::cin >> tmp;
	std::cin.ignore();
	return tmp;
}

struct DataBase
{
	int count;
	student* data;
};

void createDB(DataBase& DB)
{
	std::cout << "=========================Creating Data Base===============================";
	std::cout << std::endl;
	if (DB.data) delete[] DB.data;
	int tmp;
	std::cout << "Enter a count of students: ";
	std::cin >> tmp; std::cin.ignore();
	DB.count = tmp;
	DB.data = new student[tmp];
	for (int i = 0; i < tmp; ++i)
	{
		std::cin >> DB.data[i];
		setMark(DB.data[i]);
	}
}
void printDB(const DataBase& DB)
{
	std::cout << "=========================Print Data Base===============================";
	std::cout << std::endl;
	for (int i = 0; i < DB.count; ++i)
	{
		std::cout << DB.data[i] << std::endl;
	}
}
void txtExport(const DataBase& DB, const char* fname = "students.txt")
{
	std::cout << "=========================Exporting Data Base===============================";
	std::cout << std::endl;
	std::ofstream FileOut(fname);
	if (!FileOut) throw "Can not create or open the file";
	std::cout << "Exporting to file " << fname << " ...";
	std::cout << std::endl;
	for (int i = 0; i < DB.count; ++i)
	{
		FileOut << DB.data[i];
	}
	FileOut.close();
	std::cout << "Succsesfully!";
	std::cout << std::endl;
}
void saveDB(const DataBase& DB, const char* fname = "db.dat")
{
	std::cout << "=========================Save Data Base===============================";
	std::cout << std::endl;
	std::ofstream FileOut(fname, std::ios_base::binary);
	if (!FileOut) throw "Can not create or open the file";
	std::cout << "Saving to file " << fname << " ...";
	std::cout << std::endl;
	FileOut.write((const char*) & (DB.count), sizeof(DB.count));
	FileOut.write((const char*)DB.data, DB.count * sizeof(student));
	FileOut.close();
	std::cout << "Succesfully!";
	std::cout << std::endl;
}
void readDB(DataBase& DB, const char* fname = "db.dat")
{
	std::cout << "=========================Read Data Base===============================";
	std::cout << std::endl;
	std::ifstream FileIn(fname, std::ios_base::binary);
	if (!FileIn) throw "Can not read the file";
	std::cout << "Reading from file " << fname << " ...";
	std::cout << std::endl;
	FileIn.read((char*) & (DB.count), sizeof(DB.count));
	if (DB.data) delete[] DB.data;
	DB.data = new student[DB.count];
	FileIn.read((char*)DB.data, DB.count * sizeof(student));
	FileIn.close();
	std::cout << "Succesfully!";
	std::cout << std::endl;
}

int main()
{
	system("color 2");
	DataBase DB = { 0, nullptr };
	int action;
	do {
		action = menu();
		switch (action)
		{
		case 1: createDB(DB); break;
		case 2: printDB(DB); break;
		case 3: txtExport(DB); break;
		case 4: saveDB(DB); break;
		case 5: readDB(DB); break;
		}
	} while (action);
	if (DB.data) delete[] DB.data;

	std::cout << "Exiting...";
	return 0;
}