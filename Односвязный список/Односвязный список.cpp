#include <iostream>
#include <fstream>

struct student {
	int number;
	char surname[32], name[32];
};
struct Node
{
	student data;
	Node* next;
};
struct List 
{
	Node* first, *last;
};

std::ostream& operator<< (std::ostream& out, const student& x)
{
	out << x.number << ". " << x.surname << " " << x.name << std::endl;
	return out;
}
std::istream& operator>> (std::istream& in, student& x)
{
	std::cout << "Student number: "; in >> x.number;
	in.ignore();
	std::cout << "Surname: "; in.getline(x.surname, 32);
	std::cout << "Name: "; in.getline(x.name, 32);
	return in;
}
std::ostream& operator<< (std::ostream& out, const List& m)
{
	Node* current = m.first;
	while (current != nullptr)
	{
		out << current->data;
		current = current->next;
	}
	return out;
}
bool operator< (const student& A, const student& B)
{
	int s = strcmp(A.surname, B.surname);
	if (s == 0)
		return strcmp(A.name, B.name);
	return s < 0;
}

void CreateList(List& M)
{
	M.first = nullptr;
	M.last = nullptr;
}
void push_back(List& M, const student& X)
{
	Node* current = new Node;
	current->data = X; //(*current).data = X
	current->next = nullptr;
	if (M.first == nullptr)
		M.first = M.last = current;
	else
	{
		M.last->next = current;
		M.last = current;
	}
}
void deleteList(List& M)
{
	Node* current;
	while (M.first != nullptr)
	{
		current = M.first;
		M.first = M.first->next;
		delete current;
	}
	M.first = M.last = nullptr;
}
void sort(List& M)
{
	if (M.first == M.last) return;
	bool isSorted = false;
	do
	{
		//split
		List tmp[2];
		unsigned char p = 0; // номер текущего списка, в который добавляем
		tmp[p].first = tmp[p].last = M.first;
		M.first = M.first->next;
		tmp[!p].first = tmp[!p].last = nullptr;
		while (M.first)
		{
			if (M.first->data < tmp[p].last->data)
				p = !p;
			if (!tmp[p].first)
				tmp[p].first = M.first;
			else
				tmp[p].last->next = M.first;
			tmp[p].last = M.first;
			M.first = M.first->next;
		}
		if (tmp[p].last) tmp[p].last->next = nullptr;
		if (tmp[!p].last) tmp[!p].last->next = nullptr;
		//merge
		if (tmp[!p].first) // Значит 2 списка
		{
			bool s1, s2;
			p = (tmp[0].first->data < tmp[1].first->data) ? 0 : 1;
			M.first = M.last = tmp[p].first;
			tmp[p].first = tmp[p].first->next;
			while (tmp[p].first)
			{
				s1 = (tmp[p].first->data < M.last->data);
				s2 = (tmp[!p].first->data < M.last->data);
				if (s1 == s2)
				{
					p = (tmp[0].first->data < tmp[1].first->data) ? 0 : 1;
				}
				else
					if (s1) p = !p;
				M.last->next = tmp[p].first;
				tmp[p].first = tmp[p].first->next;
				M.last = M.last->next;
			}
			M.last->next = tmp[!p].first;
			M.last = tmp[!p].last;
		}
		else // Получен только 1 список
		{
			isSorted = true;
			M.first = tmp[p].first;
			M.last = tmp[p].last;
		}
	} while (!isSorted);
}

int menu()
{
	std::cout << "---------------------------MENU-----------------------------------------------" << std::endl;
	std::cout << "1. Add new student" << std::endl;
	std::cout << "2. Show student's list" << std::endl;
	std::cout << "3. Search by surname" << std::endl;
	std::cout << "4. Sorting" << std::endl;
	std::cout << "5. Save to file" << std::endl;
	std::cout << "6. Read from file" << std::endl;
	std::cout << "0. Exit" << std::endl;
	int action;
	std::cin >> action; std::cin.ignore();
	return action;
}
void write2file(const List& M)
{
	std::cout << "Writing to file....." << std::endl;
	std::ofstream outFile("studenst.dat", std::ios_base::binary);
	if (!outFile) throw "Can not write to file students.dat";
	Node* current = M.first;
	while (current != nullptr)
	{
		outFile.write((char*) & (current->data), sizeof(student));
		current = current->next;
	}
	outFile.close();
}
void readFile(List& M)
{
	std::cout << "Reading file....." << std::endl;
	std::ifstream inFile("studenst.dat", std::ios_base::binary);
	if (!inFile) throw "Can not write to file students.dat";
	student tmp;
	while (inFile.peek() != EOF)
	{
		inFile.read((char*)&tmp, sizeof(tmp));
		push_back(M, tmp);
	}
	inFile.close();
}
Node* find(const List& M, const student& x)
{
	Node* current = M.first;
	while (current != nullptr)
	{
		if (strcmp(current->data.surname, x.surname) == 0) break;
		current = current->next;
	}
	return current;
}

int main()
{
	List Group;
	CreateList(Group);
	int action;
	do
	{
		action = menu();
		switch (action)
		{
		case 1:
		{
			student tmp;
			std::cin >> tmp;
			push_back(Group, tmp);
		}
			break;
		case 2:
			std::cout << Group;
			break;
		case 3:
		{
			student tmp;
			std::cout << "Surname: ";
			std::cin.getline(tmp.surname, 32);
			Node* current = find(Group, tmp);
			if (current != nullptr) std::cout << current->data << std::endl;
			else std::cout << "Student not found" << std::endl;
		}
			break;
		case 4:
			sort(Group);
			std::cout << "Sorting..." << std::endl;
			break;
		case 5:
			write2file(Group);
			break;
		case 6:
			readFile(Group);
			break;
		case 0:
			std::cout << "Exiting..." << std::endl;
			break;
		}
	} while (action > 0);
	deleteList(Group);
	return 0;
}
