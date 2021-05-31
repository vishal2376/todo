// tick mark ✓

#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

using namespace std;

void write_task();
void read_task();

class todo
{
	string task_name;
	int task_no;
	string task_checkbox = "[ ]";

public:
	void create_task();
	void show_task();
};

void todo::create_task()
{

}

void todo::show_task()
{

}

void write_task()
{
	system("clear");
}

void read_task()
{
	system("clear");
}

void check_task()
{
	system("clear");
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
		cout << "\n\n\t\t\t3.Exit";
		cout << "\n\n\n\t\t\tChoose Option(1-3) :  ";
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
			break;
		}
		case '3':
		{
			check_task();
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