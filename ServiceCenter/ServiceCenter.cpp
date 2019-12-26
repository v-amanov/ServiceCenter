#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
#include <cctype>
#include <wchar.h>
#include <ctime>

using namespace std;

class Date
{
public:
	Date()
	{
		day = month = year = 0;
	}
	Date(int day, int month, int year)
	{
		this->day = day;
		this->month = month;
		this->year = year;
	}
	int day;
	int month;
	int year;
};

int Getdate(Date date)
{
	int datesum = date.day + (date.month * 30) + (date.year * 365);
	return datesum;
}

class Order
{
public:
	Order()
	{
		name = model = ownername = pnumber = status = "";
		cost = 0;
	}

	Order(string name, string model, string ownername, string pnumber, int cost, Date accdate, Date issuedate, string status)
	{
		this->name = name;
		this->model = model;
		this->ownername = ownername;
		this->pnumber = pnumber;
		this->cost = cost;
		this->accdate = accdate;
		this->issuedate = issuedate;
		this->status = status;
	}


	string name;
	string model;
	string ownername;
	string pnumber;
	int cost;
	Date accdate;
	Date issuedate;
	string status;
};

string upperCase(string input)
{
	string tempstr = input;
	for (int i = 0; i < tempstr.length(); i++)
	{
		tempstr[i] = toupper(tempstr[i]);
	}
	return tempstr;
}

ostream& operator << (ostream& os, const Date& date)
{
	os << date.day << " " << date.month << " " << date.year;
	return os;
}

istream& operator>> (istream& is, Date& date)
{
	is >> date.day >> date.month >> date.year;
	return is;
}

ostream& operator<<(ostream& os, const Order& order) //Возвращает ссыклу на объект типа ostream
{
	os << order.name << " " << order.model << " " << order.ownername << " " << order.pnumber << " "
		<< order.cost << " " << order.accdate << " " << order.issuedate << " " << order.status;

	return os;
}

istream& operator>> (istream& is, Order& order)
{
	is >> order.name >> order.model >> order.ownername >> order.pnumber >> order.cost >> order.accdate >> order.issuedate >> order.status;
	return is;
}

void IssDateSort(Order* ordmas, int stringscount)
{
	for (int j = 0; j < stringscount; j++)
	{
		for (int i = 0; i < stringscount - 1; i++)
		{
			if (Getdate(ordmas[i].issuedate) > Getdate(ordmas[i + 1].issuedate))
			{
				Order tempord;
				tempord = ordmas[i];
				ordmas[i] = ordmas[i + 1];
				ordmas[i + 1] = tempord;
			}
		}
	}
}

void AccDateSort(Order* ordmas, int stringscount)
{
	for (int j = 0; j < stringscount; j++)
	{
		for (int i = 0; i < stringscount - 1; i++)
		{
			if (Getdate(ordmas[i].accdate) > Getdate(ordmas[i + 1].accdate))
			{
				Order tempord;
				tempord = ordmas[i];
				ordmas[i] = ordmas[i + 1];
				ordmas[i + 1] = tempord;
			}
		}
	}
}

void StatusSort(Order* ordmas, int stringscount)
{
	for (int j = 0; j < stringscount; j++)
	{
		for (int i = 0; i < stringscount - 1; i++)
		{
			if (ordmas[i].status > ordmas[i + 1].status)
			{
				Order tempord;
				tempord = ordmas[i];
				ordmas[i] = ordmas[i + 1];
				ordmas[i + 1] = tempord;
			}
		}
	}
}

void NameSort(Order* ordmas, int stringscount)
{
	for (int j = 0; j < stringscount; j++)
	{
		for (int i = 0; i < stringscount - 1; i++)
		{
			if (ordmas[i].status > ordmas[i + 1].status)
			{
				Order tempord;
				tempord = ordmas[i];
				ordmas[i] = ordmas[i + 1];
				ordmas[i + 1] = tempord;
			}
		}
	}
}

void Input(Order& order, fstream& fs)
{
	cout << "Во избежании ошибок все словосочетания которые пишутся через пробел необходимо писать через нижнее подчёркивание!" << endl;
	cout << "Введите данные\n";
	cout << "\nНаименование:";
	cin >> order.name;
	cout << "\nМодель:";
	cin >> order.model;
	cout << "\nФИО владельца:";
	cin >> order.ownername;
	cout << "\nНомер владельца:";
	cin >> order.pnumber;
	cout << "\nЦена:";
	cin >> order.cost;
	cout << "\nДата приемки дд мм гг:";
	cin >> order.accdate;
	cout << "\nДата выдачи дд мм гг:";
	cin >> order.issuedate;
	cout << "\nГотов:";
	cin >> order.status;
	fs << order << "\n";
}

void Output(Order* ordmas, int stringscount)
{
	for (int i = 0; i < stringscount; i++)
	{
		Order tempord;
		tempord = ordmas[i];
		cout << i << ":" << tempord << endl;
	}
}

void Search(Order* ordmas, int stringscount)
{
	string search = "";
	string tmpstr = "";
	cout << "Введите фамилию для поиска\n";
	cin >> search;
	Order tempord;
	int counter = 0;
	for (int i = 0; i < stringscount; i++)
	{
		tmpstr = ordmas[i].ownername;
		if ((upperCase(tmpstr).find(upperCase(search)) != tmpstr.npos))
		{
			tempord = ordmas[i];
			cout << tempord << endl;
			counter++;
		}
		tmpstr = "";
	}
	if (counter == 0)
	{
		cout << "Ничего не найдено!\n";
	}
}

void ShowNotReady(Order* ordmas, int stringscount)
{
	Order tempstatus;
	cout << "Не готовые заказы:\n";
	for (int i = 0; i < stringscount; i++)
	{
		if (ordmas[i].status == "Нет")
		{
			tempstatus = ordmas[i];
			cout << tempstatus << endl;
		}
	}
}

void Calculate(Order* ordmas, int stringscount)
{
	Date firstdate;
	Date seconddate;
	cout << "Введите дату начала интервала в формате дд мм гг\n";
	cin >> firstdate;
	cout << "Введите дату конца интервала в формате дд мм гг\n";
	cin >> seconddate;
	int sum = 0;
	for (int i = 0; i < stringscount; i++)
	{
		if (Getdate(ordmas[i].issuedate) >= Getdate(firstdate) && Getdate(ordmas[i].issuedate) <= Getdate(seconddate))
		{
			sum += ordmas[i].cost;
		}
	}
	cout << "Сумма:" << sum << endl;
}

void admin()
{
	cout << "Введите пароль\n";
	string password = "";
	cin >> password;
	string choise = "";
	while (choise != "N" && choise != "n")
	{
		if (password == "admin")
		{
			string path = "Database.txt";
			fstream fs;
			fs.open(path, fstream::in | fstream::out | fstream::app);
			if (!fs.is_open())
			{
				cout << "Ошибка отркрытия файла!" << endl;
			}
			else
			{

				int value;
				cout << "Файл открыт!" << endl;
				cout << "Введите 1 для записи в файл" << endl;
				cout << "Введите 2 для считывания всех записей" << endl;
				cout << "Введите 3 для поиска записи" << endl;
				cout << "Введите 4 для удаления записи" << endl;
				cin >> value;

				int stringscount = 0;
				Order order;
				while (true)
				{
					Order _order;
					fs >> _order;
					if (fs.eof())
					{
						break;
					}
					cout << stringscount << ":" << _order << endl;
					stringscount++;
				}
				Order* ordmas = new Order[stringscount];
				fs.clear();
				fs.seekg(0, ios_base::beg);

				for (int i = 0; i < stringscount; i++)
				{
					Order _ordmas;
					fs >> _ordmas;
					ordmas[i] = _ordmas;

				}

				switch (value)
				{
				case 1:
				{
					fs.close();
					fs.open(path, fstream::in | fstream::out | fstream::app);
					Input(order, fs);
					break;
					fs.close();
				}
				case 2:
				{

					int sortvalue = 0;
					cout << "Выберите способ сортировки\n1.По дате приема\n2.По статусу\n3.По наименованию\n";
					cin >> sortvalue;
					cout << "Отсортированные записи \n";
					switch (sortvalue)
					{

					case 1:
					{
						AccDateSort(ordmas, stringscount);
						Output(ordmas, stringscount);
						fs.close();
						break;
					}
					case 2:
					{
						StatusSort(ordmas, stringscount);
						Output(ordmas, stringscount);
						fs.close();
						break;
					}
					case 3:
					{
						NameSort(ordmas, stringscount);
						Output(ordmas, stringscount);
						fs.close();
						break;
					}
					default:
						break;
					}

					break;

				}
				case 3:
				{
					Search(ordmas, stringscount);
					break;
				}
				case 4:
				{
					fs.close();
					ofstream filerewrite;
					filerewrite.open(path);
					cout << "Введите строку для удаления" << endl;
					int strnumber = 0;
					cin >> strnumber;
					Order temporder;
					for (int i = 0; i < stringscount; i++)
					{
						if (i != strnumber)
						{
							temporder = ordmas[i];
							filerewrite << temporder << endl;
						}
					}
					filerewrite.close();
					break;
				}
				}

			}
			cout << "Хотите продолжить работу? Y/N\n";
			cin >> choise;
			fs.close();
		}
		else
		{
			cout << "Неверный пароль!\n";
			cin >> password;
		}
	}
}

void user()
{
	string choise;
	while (choise != "N" && choise != "n")
	{
		choise = "n";
		cout << "1.Вывести список заказов, невыполненных на текущий момент\n2.Вывести общий доход\n";
		int value;
		cin >> value;
		int stringscount = 0;
		string path = "Database.txt";
		Order order;
		fstream fs;
		fs.close();
		fs.clear();
		fs.seekg(0, ios_base::beg);
		fs.open(path, fstream::in | fstream::out | fstream::app);
		while (true)
		{
			Order _order;
			fs >> _order;
			if (fs.eof())
			{
				break;
			}
			cout << _order << endl;
			stringscount++;
		}

		fs.clear();
		fs.seekg(0, ios_base::beg);
		Order* ordmas = new Order[stringscount];
		for (int i = 0; i < stringscount; i++)
		{
			Order _ordmas;
			fs >> _ordmas;
			ordmas[i] = _ordmas;

		}
		//for (int j = 0; j < stringscount; j++)
		//{
		//	for (int i = 0; i < stringscount - 1; i++)
		//	{
		//		if (Getdate(ordmas[i].issuedate) > Getdate(ordmas[i + 1].issuedate))
		//		{
		//			Order tempord;
		//			tempord = ordmas[i];
		//			ordmas[i] = ordmas[i + 1];
		//			ordmas[i + 1] = tempord;
		//		}
		//	}
		//}
		IssDateSort(ordmas, stringscount);
		switch (value)
		{
		case 1:
		{
			ShowNotReady(ordmas, stringscount);
			break;
		}
		case 2:
		{
			Calculate(ordmas, stringscount);
			break;
		}
		default:
			break;
		}

		cout << "Хотите продолжить работу? Y/N\n";
		cin >> choise;
		fs.close();
	}
}

int main()
{

	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int mode;
	cout << "Выберите режим работы\n1:Администратор\n2:Пользователь\n";
	cin >> mode;

	while (mode != 1 && mode != 2)
	{
		cout << "Неверный выбор!\nВыберите режим работы\n1:Администратор\n2:Пользователь\n";
		cin >> mode;
	}

	switch (mode)
	{
	case 1:
		admin();
		break;

	case 2:
		user();
		break;

	default:
		cout << "Неверный выбор";
		break;

	}

	return 0;
}

