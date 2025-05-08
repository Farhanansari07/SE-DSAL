/*
Department maintains a student information. The file contains roll number, name, division and address. 
Allow user to add, delete information of student. Display information of particular employee. 
If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details. 
Use sequential file to main the data.
*/

#include <iostream>
#include <fstream>
#include <iomanip>
// #include <string>

using namespace std;

void outputData(string rn, string name, string div, string add)
{
	ofstream filestream("db.txt", ios::app);
	filestream << left << setw(20) << rn << setw(20) << name << setw(20) << div << setw(20) << add << endl;
	filestream.close();
}

void addStudent()
{
	ifstream f("db.txt");
	string rn, name, div, add;
	cout << "Enter Student Roll No.: ";
	cin >> rn;
	cout << "Enter Student Name: ";
	cin >> name;
	cout << "Enter Student Division: ";
	cin >> div;
	cout << "Enter Student Address: ";
	cin >> add;
	outputData(rn, name, div, add);
	cout << "Added Data Sucessfully!\n";
	f.close();
}

void deleteStudent()
{

	string rn;
	cout << "Enter Student Roll No. to Delete: ";
	cin >> rn;

	fstream f("db.txt");
	string line;
	string fileData;
	while (getline(f, line))
	{
		if (line.find(rn) == string::npos)
		{
			fileData += line;
			fileData += "\n";
		}
	}
	f.close();

	f.open("db.txt", ios::out);
	f << fileData;
	f.close();
}

void searchStudent()
{

	string rn;
	cout << "Enter Student Roll No. to Search: ";
	cin >> rn;
    
    bool found = false;    
        
	ifstream f("db.txt" );
	string line;
	while (getline(f, line))
	{
		if (line.find(rn) != string::npos)
		{
			cout << "Student Details:\n" << endl;
			cout << line << endl;
			found = true;
			break;
		}
	}
	f.close();
	if(!found) {
	    cout << "Student does not exist.\n";
	}
}

void printData()
{
	ifstream f("db.txt");
	cout << "\nPrinting File Data: \n";
	string line;
	while (getline(f, line))
	{
		cout << line << endl;
	}
	cout << "File Data Completed!\n";
	f.close();
}

int main()
{
	fstream f("db.txt", ios::out);
	f.close();
	outputData("Roll No.", "Name", "Division", "Address");


	int choice;
	while (choice != 5)
	{
		cout << "\nEnter Your Choice:\n1. Add Student Data\n2. Delete Student Data\n3. Search Student Data\n4. Print File\n5. Exit\n--->";
		cin >> choice;
		switch (choice)
		{
		case 1:
			addStudent();
			break;
		case 2:
			deleteStudent();
			break;
		case 3:
			searchStudent();
			break;
		case 4:
			printData();
			break;
		case 5:
			return 0;
			break;
		default:
			cout << "Invalid choice!" << endl;
			break;
		}
	}
}
