// tick mark ✓

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<iomanip>

using namespace std;

void write_task();
void read_task(int);
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
	int Rcheck() {return check;}
};

void todo::create_task()
{
	cout << "\n\n\t\tEnter task : ";
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
	cout << "\t\t    " << setw(2) << task_no << task_checkbox << "---- " << task_name << "\n";
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

void read_task(int s = 0)
{
	todo td;
	ifstream file;
	int total, completed;
	total = completed = 0;
	file.open("tasks.dat", ios::binary);
	system("clear");
	cout << "\n\n";
	while (file.read((char*)&td, sizeof(todo)))
	{
		td.show_task();
		total++;
		if (td.Rcheck() == 1)
			completed++;
	}
	file.close();
	if (s == 1)
	{
		cout << "\n\n\t\t\t=======================";
		cout << "\n\t\t\t Total Tasks ------ " << setw(2) << total;
		cout << "\n\t\t\t Completed   ------ " << setw(2) << completed;
		cout << "\n\t\t\t Remaining   ------ " << setw(2) << total - completed;
		cout << "\n\t\t\t=======================";
	}

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
	cout << "\n";
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
		cout << "\n\n\t\t\t4.Remove All Tasks";
		cout << "\n\n\t\t\t5.Exit";
		cout << "\n\n\n\t\t\tChoose Option(1-5) :  ";
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
			read_task(1);
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
				cout << "\n\n\t\t\t[✓] ---- Completed";
				cout << "\n\t\t\t[ ] ---- Not Completed";
				cout << "\n\n\tEnter task number to check/uncheck task ( 0 for quit): ";
				cin >> n;
				if (n != 0)
					modify_task(n);
			} while (n != 0);
			break;
		}
		case '4':
		{
			char ch;
			do
			{
				cout << "\n\n\t\tDo you want to remove all tasks?(y/n) : ";
				cin >> ch;
				if (ch == 'y')
					remove("tasks.dat");

			} while (ch != 'y' || ch != 'n');
			break;
		}
		case '5':
		{
			exit(0);
		}
		default:
			cout << "\n\t\t\t!!!!!! Invalid Input !!!!!!!";
		}
	} while (ch != '4');

	return 0;
}