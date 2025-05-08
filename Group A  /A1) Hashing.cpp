/*
Consider telephone book database of N clients. Make use of a hash 
table implementation to quickly look up client‘s telephone number. Make use of 
two collision handling techniques and compare them using number of comparisons 
required to find a set of telephone numbers
*/

#include <iostream>
#include <string>
using namespace std;

class EntryNode {
public:
    string contactName;
    int phoneNumber;
    EntryNode* nextNode;

    EntryNode(string cname, int phone) {
        contactName = cname;
        phoneNumber = phone;
        nextNode = NULL;
    }
};

class PhoneHashTable {
    EntryNode* chainingTable[10] = {NULL}; // Chaining Table

    struct LinearEntry {  // Structure for Linear Probing Table
        string contactName;
        int phoneNumber;
        bool isOccupied = false;
    } linearProbingArray[10];

public:
    PhoneHashTable() {
        for (int i = 0; i < 10; i++) {
            linearProbingArray[i].phoneNumber = -1; // -1 represents empty slot
            linearProbingArray[i].isOccupied = false;
        }
    }

    // Insert using Separate Chaining
    void addChaining(string cname, int phone) {
        EntryNode* newNode = new EntryNode(cname, phone);
        int index = phone % 10;
        if (chainingTable[index] == NULL) {
            chainingTable[index] = newNode;
        } else {
            EntryNode* current = chainingTable[index];
            while (current->nextNode != NULL) {
                current = current->nextNode;
            }
            current->nextNode = newNode;
        }
    }

    // Insert using Linear Probing (Without Replacement)
    void addLinearProbing(string cname, int phone) {
        int index = phone % 10;
        int initialIndex = index;

        while (linearProbingArray[index].isOccupied) {
            index = (index + 1) % 10; // Move to next index (circular)
            if (index == initialIndex) {
                cout << "Hash Table Full! Cannot insert " << cname << " - " << phone << endl;
                return;
            }
        }

        linearProbingArray[index].contactName = cname;
        linearProbingArray[index].phoneNumber = phone;
        linearProbingArray[index].isOccupied = true;
    }

    // Search using Separate Chaining
    void findChaining(int phone) {
        int index = phone % 10;
        EntryNode* current = chainingTable[index];
        int steps = 0;

        while (current != NULL) {
            steps++;
            if (current->phoneNumber == phone) {
                cout << "Found in Separate Chaining with " << steps << " comparisons.\n";
                cout << "Name: " << current->contactName << ", Phone: " << current->phoneNumber << endl;
                return;
            }
            current = current->nextNode;
        }
        cout << "Not found in Separate Chaining. Comparisons: " << steps << endl;
    }

    // Search using Linear Probing
    void findLinearProbing(int phone) {
        int index = phone % 10;
        int initialIndex = index;
        int steps = 0;

        while (linearProbingArray[index].isOccupied) {
            steps++;
            if (linearProbingArray[index].phoneNumber == phone) {
                cout << "Found in Linear Probing with " << steps << " comparisons.\n";
                cout << "Name: " << linearProbingArray[index].contactName << ", Phone: " << linearProbingArray[index].phoneNumber << endl;
                return;
            }
            index = (index + 1) % 10; // Move to next index (circular)
            if (index == initialIndex) {
                break; // Full cycle, number not found
            }
        }
        cout << "Not found in Linear Probing. Comparisons: " << steps << endl;
    }

    // Display all data
    void showTables() {
        cout << "\n--- Chaining Table ---\n";
        for (int i = 0; i < 10; i++) {
            cout << "Index " << i << ": ";
            EntryNode* current = chainingTable[i];
            while (current != NULL) {
                cout << "[" << current->contactName << " - " << current->phoneNumber << "] -> ";
                current = current->nextNode;
            }
            cout << "NULL\n";
        }

        cout << "\n--- Linear Probing Table ---\n";
        for (int i = 0; i < 10; i++) {
            if (linearProbingArray[i].isOccupied)
                cout << "Index " << i << ": " << linearProbingArray[i].contactName << " - " << linearProbingArray[i].phoneNumber << "\n";
            else
                cout << "Index " << i << ": EMPTY\n";
        }
    }
};

int main() {
    PhoneHashTable phoneTable;
    char choice;

    while (true) {
        cout << "\n1. Add Entry (Chaining) \n2. Add Entry (Linear Probing) \n3. Search Entry (Chaining) \n4. Search Entry (Linear Probing) \n5. Display Tables \n6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == '1') {
            string cname;
            int phone;
            cout << "Enter Name: ";
            cin >> cname;
            cout << "Enter Phone Number: ";
            cin >> phone;
            phoneTable.addChaining(cname, phone);
        } else if (choice == '2') {
            string cname;
            int phone;
            cout << "Enter Name: ";
            cin >> cname;
            cout << "Enter Phone Number: ";
            cin >> phone;
            phoneTable.addLinearProbing(cname, phone);
        } else if (choice == '3') {
            int phone;
            cout << "Enter the phone number to search: ";
            cin >> phone;
            phoneTable.findChaining(phone);
        } else if (choice == '4') {
            int phone;
            cout << "Enter the phone number to search: ";
            cin >> phone;
            phoneTable.findLinearProbing(phone);
        } else if (choice == '5') {
            phoneTable.showTables();
        } else if (choice == '6') {
            cout << "Exiting..." << endl;
            break;
        } else {
            cout << "Invalid Choice" << endl;
        }
    }

    return 0;
}

