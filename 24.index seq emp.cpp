#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Employee {
    int id;
    char name[50], designation[50];
    float salary;
};

void addEmployee() {
    Employee emp;
    ofstream fout("employee.txt", ios::app);
    ofstream index("index.txt", ios::app);

    cout << "Enter Employee ID: ";
    cin >> emp.id;
    cout << "Enter Name: ";
    cin >> emp.name;
    cout << "Enter Designation: ";
    cin >> emp.designation;
    cout << "Enter Salary: ";
    cin >> emp.salary;

    fout << emp.id << " " << emp.name << " " << emp.designation << " " << emp.salary << endl;
    index << emp.id << endl;

    fout.close();
    index.close();

    cout << "Employee record added successfully.\n";
}

void displayAll() {
    Employee emp;
    ifstream fin("employee.txt");

    cout << "\nID\tName\tDesignation\tSalary\n";
    cout << "------------------------------------------\n";

    while (fin >> emp.id >> emp.name >> emp.designation >> emp.salary) {
        cout << emp.id << "\t" << emp.name << "\t" << emp.designation << "\t\t" << emp.salary << endl;
    }

    fin.close();
}

void searchEmployee() {
    Employee emp;
    int searchID, found = 0;
    cout << "Enter Employee ID to search: ";
    cin >> searchID;

    ifstream fin("employee.txt");

    while (fin >> emp.id >> emp.name >> emp.designation >> emp.salary) {
        if (emp.id == searchID) {
            cout << "\nEmployee Found!\n";
            cout << "ID: " << emp.id << "\nName: " << emp.name;
            cout << "\nDesignation: " << emp.designation << "\nSalary: " << emp.salary << endl;
            found = 1;
            break;
        }
    }

    fin.close();
    if (!found)
        cout << "Employee not found.\n";
}

void deleteEmployee() {
    Employee emp;
    int delID, found = 0;
    cout << "Enter Employee ID to delete: ";
    cin >> delID;

    ifstream fin("employee.txt");
    ofstream temp("temp.txt");
    ofstream index("index.txt"); // rewrite index too

    while (fin >> emp.id >> emp.name >> emp.designation >> emp.salary) {
        if (emp.id != delID) {
            temp << emp.id << " " << emp.name << " " << emp.designation << " " << emp.salary << endl;
            index << emp.id << endl;
        } else {
            found = 1;
        }
    }

    fin.close();
    temp.close();
    index.close();

    remove("employee.txt");
    rename("temp.txt", "employee.txt");

    if (found)
        cout << "Employee deleted successfully.\n";
    else
        cout << "Employee not found.\n";
}

int main() {
    int choice;
    do {
        cout << "\n----- Employee Information System -----\n";
        cout << "1. Add Employee\n2. Display All Employees\n3. Search Employee\n4. Delete Employee\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayAll(); break;
            case 3: searchEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}

