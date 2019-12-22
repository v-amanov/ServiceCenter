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
			switch (sortvalue)
			{

			case 1:
				break;

			case 2:
				break;

			case 3:
				break;

			default:
				break;
			}

			while (true)
			{
				Order _order;
				fs >> _order;
				if (fs.eof())
				{
					break;
				}
				cout << _order << endl;
			}
			break;
		}
		default:
			break;
		}

	}

	fs.close();
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

