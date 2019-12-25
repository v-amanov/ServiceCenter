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



void admin()
{
	cout << "Введите пароль\n";
	string password = "";
	cin >> password;
	if (password == "admin")
	{
		string path = "Database.txt";
		Order order;
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
			cout << "Введите 1 для записи в файл: " << endl;
			cout << "Введите 2 для считывания всех записей" << endl;
			cout << "Введите 3 для поиска записи" << endl;
			cin >> value;

			int stringscount = 0;

			while (true)
			{
				Order _order;
				fs >> _order;
				if (fs.eof())
				{
					break;
				}
				//cout << _order << endl;
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
				cout << "Во избежании ошибок все словосочетания которые пишутся через пробел необходимо писать через нижнее подчёркивание!" << endl;
				cout << "Введите данные" << endl;
				cout << "\nНаименование: ";
				cin >> order.name;
				cout << "\nМодель: ";
				cin >> order.model;
				cout << "\nФИО владельца: ";
				cin >> order.ownername;
				cout << "\nНомер владельца: ";
				cin >> order.pnumber;
				cout << "\nЦена: ";
				cin >> order.cost;
				cout << "\nДата приемки: ";
				cin >> order.accdate;
				cout << "\nДата выдачи: ";
				cin >> order.issuedate;
				cout << "\nГотов: ";
				cin >> order.status;
				fs << order << "\n";
				break;

			case 2:
			{

				int sortvalue = 0;
				cout << "Выберите способ сортировки\n1.По дате приема\n2.По статусу\n3.По наименованию\n";
				cin >> sortvalue;
			



				cout << "Отсортированные записи \n";
				switch (sortvalue)
				{

				case 1:

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

					for (int i = 0; i < stringscount; i++)
					{
						Order tempord;
						tempord = ordmas[i];
						cout << tempord << endl;
					}

					break;

				case 2:

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

					for (int i = 0; i < stringscount; i++)
					{
						Order tempord;
						tempord = ordmas[i];
						cout << tempord << endl;
					}

					break;

				case 3:

					for (int j = 0; j < stringscount; j++)
					{
						for (int i = 0; i < stringscount - 1; i++)
						{
							if (ordmas[i].name > ordmas[i + 1].name)
							{
								Order tempord;
								tempord = ordmas[i];
								ordmas[i] = ordmas[i + 1];
								ordmas[i + 1] = tempord;
							}
						}
					}

					for (int i = 0; i < stringscount; i++)
					{
						Order tempord;
						tempord = ordmas[i];
						cout << tempord << endl;
					}

					break;

				default:
					break;
				}


				break;

			}
			case 3:
				string search = "";
				string tmpstr = "";
				cout << "Введите фамилию для поиска\n";
				cin >> search;
				Order tempord;
				for (int i = 0; i < stringscount; i++)
				{
					tmpstr = ordmas[i].ownername;
					if ((upperCase(tmpstr).find(upperCase(search)) != tmpstr.npos)/*tmpstr.find(search)*/)
					{
						//tmpstr.find(search);
						tempord = ordmas[i];
						cout << tempord << endl;
					}
					tmpstr = "";
				}
				break;
			}

		}

		fs.close();
	}
	else
	{
		cout << "Неверный пароль!";
	}
}

void user()
{
	cout << "1.Вывести список заказов, невыполненных на текущий момент\n2.Вывести общий доход\n";
	int choise;
	cin >> choise;
	int stringscount = 0;
	string path = "Database.txt";
	Order order;
	fstream fs;
	fs.open(path, fstream::in | fstream::out | fstream::app);
	while (true)
	{
		Order _order;
		fs >> _order;
		if (fs.eof())
		{
			break;
		}
		//cout << _order << endl;
		stringscount++;
	}

	fs.clear();
	fs.seekg(0, ios_base::beg);
	Order* ordmas = new Order[stringscount];
	Order tempstatus;
	for (int i = 0; i < stringscount; i++)
	{
		Order _ordmas;
		fs >> _ordmas;
		ordmas[i] = _ordmas;

	}
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
	switch (choise)
	{
	case 1:
	{
		for (int i = 0; i < stringscount; i++)
		{
			if (ordmas[i].status == "Нет")
			{
				tempstatus = ordmas[i];
				cout << tempstatus << endl;
			}
		}
		break;
	}
	case 2:
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
		break;
	}
	default:
		break;
	}
}

int main()
{

	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int choise;
	cout << "Выберите режим работы\n1:Администратор\n2:Пользователь\n";
	cin >> choise;

	while (!choise == 1 || !choise == 2)
	{
		cout << "Неверный выбор!\nВыберите режим работы\n1:Администратор\n2:Пользователь\n";
		cin >> choise;
	}

	switch (choise)
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
//#pragma warning(disable : 4996)
//	time_t now = time(0);
//
//	cout << "Number of sec since January 1,1970:" << now << endl;
//
//	tm* ltm = localtime(&now);
//
//	// print various components of tm structure.
//	cout << "Year" << 1900 + ltm->tm_year << endl;
//	cout << "Month: " << 1 + ltm->tm_mon << endl;
//	cout << "Day: " << ltm->tm_mday << endl;
//	cout << "Time: " << 1 + ltm->tm_hour << ":";
//	cout << 1 + ltm->tm_min << ":";
//	cout << 1 + ltm->tm_sec << endl;
//#pragma warning(default : 4996)
	//cin >> choise;
	return 0;
}

