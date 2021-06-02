// tick mark ✓

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstdio>

using namespace std;

void write_task();
void read_task();
void getch();
int ret_task_no();

class todo
{
	char task_name[80];
	int task_no;
	int check;

public:
	void create_task();
	void show_task();
	void check_task();
	int Rtask_no() {return task_no;}
};

void todo::create_task()
{
	cout << "\n\n\t\t\tEnter task : ";
	cin.ignore();
	cin.getline(task_name, 80);
	task_no = ret_task_no() + 1;
	check = -1;
}

void todo::show_task()
{
	string task_checkbox = " [ ] ";
	if (check == 1)
		task_checkbox = " [✓] ";
	cout << task_no << task_checkbox << task_name << "\n";
}

void todo::check_task()
{
	check = (-1) * check;
}

void write_task()
{
	todo td;
	ofstream file;

	system("clear");
	td.create_task();
	file.open("tasks.dat", ios::app | ios::binary);

	file.write((char*)&td, sizeof(todo));

	file.close();

}

int ret_task_no()
{
	todo td;
	ifstream file;

	int tasknum;

	file.open("tasks.dat", ios::binary);

	if (!file)
	{
		tasknum = 0;
	}
	else
	{
		while (file.read((char*)&td, sizeof(todo)))
		{
			tasknum = td.Rtask_no();
		}
	}
	file.close();
	return tasknum;
}

void read_task()
{
	todo td;
	ifstream file;
	file.open("tasks.dat", ios::binary);

	while (file.read((char*)&td, sizeof(todo)))
	{
		td.show_task();
	}
	file.close();

}

void modify_task(int n)
{
	todo td;
	fstream file;
	int flag = 0;

	file.open("tasks.dat", ios::binary | ios::out | ios::in);
	if (!file)
	{
		cout << "!!!! Error : Failed to open the file !!!!";
		return;
	}

	while (file.read((char*)&td, sizeof(todo)) && flag == 0 )
	{
		if (td.Rtask_no() == n)
		{
			td.check_task();
			int pos = (-1) * sizeof(todo);
			file.seekp(pos, ios::cur);
			file.write((char*)&td, sizeof(todo));
			flag = 1;
		}
	}
	file.close();
	if (flag == 0)
	{
		cout << "\n\n\t\t\t!!!!!!Not Found!!!!!!";
		getch();
	}

}

void getch()
{
	char ch;
	cin.ignore();
	ch = getchar();
}

int main()
{

	char ch;

	do
	{
		system("clear");
		cout << "\n\n\t\t\t\tMain Menu";
		cout << "\n\n\t\t\t1.Add Task";
		cout << "\n\n\t\t\t2.Show Tasks";
		cout << "\n\n\t\t\t3.Manage Tasks";
		cout << "\n\n\t\t\t4.Exit";
		cout << "\n\n\n\t\t\tChoose Option(1-4) :  ";
		cin >> ch;

		switch (ch)
		{
		case '1':
		{
			write_task();
			break;
		}
		case '2':
		{
			read_task();
			getch();
			break;
		}
		case '3':
		{
			int n;
			do
			{
				system("clear");
				read_task();
				cout << "\n\n\t\t Enter task number to check/uncheck task ( 0 for quit): ";
				cin >> n;
				if (n != 0)
					modify_task(n);
			} while (n != 0);
			break;
		}
		case '4':
		{
			exit(0);
		}
		default:
			cout << "\n\t\t\t!!!!!! Invalid Input !!!!!!!";
		}
	} while (ch != '4');

	return 0;
}