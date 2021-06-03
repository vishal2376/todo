//-----------------------ToDo App-------------------------//
//-----------------Made by - vishal singh-------------//

// change system("clear") with system("cls") if you are using Windows

#include<iostream>
#include<fstream>
#include<string.h>
#include<cstdlib>
#include<cstdio>
#include<iomanip>

using namespace std;


void write_task();
void read_task(int);
void remove_task();
void modify_task(int);
void getch();
int ret_task_no();

class todo
{
	char task_name[80];
	int task_no = 0;
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
	cin.ignore();
	while (1)
	{
		system("clear");
		cout << "\n\n\t\tEnter task : ";
		cin.getline(task_name, 80);
		if (strlen(task_name) != 0)
			break;
		else
			cout << "\n\n\t\t!!! Task can't be empty !!!";
	}

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
	cout << "\n\n\t\t   Task No. \tTask title";
	cout << "\n\t\t  ==================================\n";
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
		cout << "\n\n\t\t\t======================";
		cout << "\n\t\t\tTotal Tasks ------ " << setw(2) << total;
		cout << "\n\t\t\tCompleted   ------ " << setw(2) << completed;
		cout << "\n\t\t\tRemaining   ------ " << setw(2) << total - completed;
		cout << "\n\t\t\t======================";
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

void remove_task(int n)
{
	todo td;
	fstream ifile, ofile;
	int flag = 0;

	ifile.open("tasks.dat", ios::binary | ios::in);
	ofile.open("temp.dat", ios::binary | ios::out);
	if (!ifile)
	{
		cout << "!!!! Error : Failed to open the file !!!!";
		return;
	}
	ifile.seekg(0, ios::beg);
	if (flag == 0)
		if (n == -1)
			while (ifile.read((char*)&td, sizeof(todo)))
			{	if (td.Rcheck() == -1)
				{
					ofile.write((char*)&td, sizeof(todo));
					flag = 1;
				}
			}
		else
			while (ifile.read((char*)&td, sizeof(todo)))
			{
				if (td.Rtask_no() != n)
				{
					ofile.write((char*)&td, sizeof(todo));
					flag = 1;
				}
			}
	ifile.close();
	ofile.close();
	remove("tasks.dat");
	rename("temp.dat", "tasks.dat");
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
		cout << "\n\n\t\t\t4.Remove Tasks";
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
				cout << "\n\n\tEnter [Task No.] to check/uncheck task ( 0 for exit): ";
				cin >> n;
				if (n > 0)
					modify_task(n);
			} while (n != 0);
			break;
		}
		case '4':
		{
			int n;

			do
			{
				system("clear");
				read_task();
				cout << "\n\n\t\t\t-1 ---- Remove completed tasks";
				cout << "\n\t\t\t-2 ---- Remove all tasks";
				cout << "\n\t\t\t 0 ---- Exit";
				cout << "\n\n\t\tEnter [Task No.] to remove tasks : ";
				cin >> n;
				if (n > 0 || n == -1)
					remove_task(n);
				else if (n == -2)
					remove("tasks.dat");
				else if (n == 0)
					break;
				else
					cout << "\n\n\t\t\t!!!!! Invalid input !!!!!";

			} while (n != -2);
			break;
		}
		case '5':
		{
			exit(0);
		}
		default:
			cout << "\n\t\t\t!!!!!! Invalid Input !!!!!!!";
		}
	} while (ch != '5');

	return 0;
}
