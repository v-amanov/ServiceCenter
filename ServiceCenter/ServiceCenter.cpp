#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>
using namespace std;

class Order
{
public:
	Order()
	{
		name = model = ownername = pnumber = cost = accdate = issuedate = status = "";
	}

	Order(string name, string model, string ownername, string pnumber, string cost, string accdate, string issuedate, string status)
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

	/*void Print()
	{
		cout << "Наименование: " << name << "\tМодель: " << model << "\tФИО владельца: " << ownername << "\tНомер телефона владельца: " << pnumber << "\tЦена: " << cost << "\tДата приемки: " << accdate << "\tДата выдачи: " << issuedate << "\tСтатус: " << status << endl;
	}*/

	string name;
	string model;
	string ownername;
	string pnumber;
	string cost;
	string accdate;
	string issuedate;
	string status;
};



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
	cout << "Введите пароль";
	string password = "";
	cin >> password;
	if (password=="admin")
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
			switch (value)
			{
			case 1:
				cout << "Во избежании ошибок все словосочетания которые пишутся через пробел необходимо писать через нижнее подчёркиванеи!" << endl;
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
				cout << "\nСтатус: ";
				cin >> order.status;
				fs << order << "\n";
				break;

			case 2:
			{
				int sortvalue = 0;
				cout << "Выберите способ сортировки\n1.По дате приема\n2.По статусу\n3.По наименованию\n";
				cin >> sortvalue;
				int stringscount=0;

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
				int j = 0;
				for (int i = 0; i < stringscount; i++)
				{
					Order _ordmas;
					fs >> _ordmas;
					ordmas[i] = _ordmas;
		
				}
				/*while (true)
				{
					Order _order;
					fs >> _order;
					ordmas[j] = _order;
					if (fs.eof())
					{
						break;
					}
					j++;
				}*/
				//cout << stringscount;
				cout << "Отсортированные записи \n";
				switch (sortvalue)
				{

				case 1:

					for (int j = 0; j < stringscount; j++)
					{
						for (int i = 0; i < stringscount-1; i++)
						{
							if (ordmas[i].accdate>ordmas[i+1].accdate)
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
				break;

			default:
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

}

int main()
{
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
	
	//cin >> choise;
	return 0;
}

