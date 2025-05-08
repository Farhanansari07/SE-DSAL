/*
To create ADT that implement the "set" concept. 
a. Add (new Element) -Place a value into the set , 
b. Remove (element) Remove the value 
c. Contains (element) Return true if element is in collection, 
d. Size () Return number of values in collection Iterator () Return an iterator used to loop over collection, 
e. Intersection of two sets , 
f. Union of two sets, 
g. Difference between two sets, 
h. Subset
*/

#include <iostream>
#include <string>
using namespace std;

class Iterator {
    int *arr;   
    int arrSize; 
    int currentIndex;
	
	public:
    Iterator(int *inputArr, int inputSize) : arr(inputArr), arrSize(inputSize), currentIndex(0) {}

    bool hasNext() const {
        return currentIndex < arrSize;
    }

    int next() {
        if (hasNext()) {
            return arr[currentIndex++];
        } else {
            cout << "No more elements in the iterator";
        }
    }
    void reset() {
        currentIndex = 0;
    }
};

class SetManager {
    int list1[5], list2[5]; // Arrays for first and second lists
    int intersectionList[10]; // Intersection array
    int unionList[10]; // Union array
    int list1Size = 0, list2Size = 0; 

public:
    void addElements(int numElements, int listFlag) { 
        for (int i = 0; i < numElements;) {
            int element;
            cout << "Enter element: ";
            cin >> element;
            
            bool isUnique = true;
            
            if (listFlag == 0) {
            	for (int j = 0; j < list1Size; j++) {
            		if (list1[j] == element) {
            			cout << "\t*Duplicate element cannot be added*\n";
            			isUnique = false;
            			break;
					}
				}
				if (isUnique) {
					list1[list1Size] = element;
                	list1Size++;
                	i++;
				}
            } else {
                for (int j = 0; j < list2Size; j++) {
            		if (list2[j] == element) {
            			cout << "\t*Duplicate element cannot be added!!!*\n";
            			isUnique = false;
            			break;
					}
				}
				if (isUnique) {
					list2[list2Size] = element;
                	list2Size++;
                	i++;
				}
            }
        }
    }

    void removeElement(int &elementCount, int selectedList, int element) {
        int *targetList = (selectedList == 1) ? list1 : list2;
        int &currentSize = (selectedList == 1) ? list1Size : list2Size;
        bool isFound = false;

        for (int i = 0; i < currentSize; i++) {
            if (targetList[i] == element) {
                isFound = true;
                for (int j = i; j < currentSize - 1; j++) {
                    targetList[j] = targetList[j + 1]; 
                }
                currentSize--;
                break;
            }
        }
        if (isFound) {
            cout << "Element " << element << " removed successfully.\n";
        } else {
            cout << "Element " << element << " not found in the list.\n";
        }
    }

    void findElement(int selectedList, int searchElement) {                                                  
        int *targetList = (selectedList == 1) ? list1 : list2;
        int currentSize = (selectedList == 1) ? list1Size : list2Size;

        for (int i = 0; i < currentSize; i++) {
            if (targetList[i] == searchElement) {
                cout << "Element found at index " << i << " in the list.\n";
                return;
            }
        }
        cout << "The element is not present in the list.\n";
    }

    void listSize(int selectedList) {
        if (selectedList == 1) {
            cout << "Size of list 1: " << list1Size << endl;
        } else if (selectedList == 2) {
            cout << "Size of list 2: " << list2Size << endl;
        } else {
            cout << "Invalid list choice!\n";
        }
    }
    
    void findIntersection() {
    	int index = 0;
    	for (int i = 0; i < list1Size; i++) {
    		for (int j = 0; j < list2Size; j++) {
    			if (list1[i] == list2[j]) {
    				bool isAlreadyInList = false;
    				for (int x = 0; x < index; x++) {
    					if (intersectionList[x] == list1[i]) {
    						isAlreadyInList = true;
    						break;
						}
					}
					if (!isAlreadyInList) {
						intersectionList[index] = list1[i];
						index++;
					}
				}
			}
		}
		cout << "The intersection of list 1 and list 2 is: ";
    	for (int i = 0; i < index; i++) {
        	cout << intersectionList[i] << " ";
    	}
    	cout << endl;
	}
	
	void findUnion() {
		int unionIndex = 0;
		
		for (int i = 0; i < list1Size; i++) {
			unionList[unionIndex] = list1[i];
			unionIndex++;
		}
		
		for (int i = 0; i < list2Size; i++) {
			bool isAlreadyInUnion = false;
			for (int x = 0; x < unionIndex; x++) {
				if (list2[i] == unionList[x]) {
					isAlreadyInUnion = true;
					break;
				}
			}
			if (!isAlreadyInUnion) {
				unionList[unionIndex] = list2[i];
				unionIndex++;
			}
		}
		cout << "The union of list 1 and list 2 is: ";
    	for (int i = 0; i < unionIndex; i++) {
        	cout << unionList[i] << " ";
    	}
    	cout << endl;	
	}
	
	void findDifference() {
		int differenceList[5];
		int diffIndex = 0;
		for (int i = 0; i < list1Size; i++) {
			
			bool isInList2 = false;
			for (int j = 0; j < list2Size; j++) {
				if (list1[i] == list2[j]) {
					isInList2 = true;
					break;
				}
			}
			if (!isInList2) {
				differenceList[diffIndex] = list1[i];
				diffIndex++;
			}
		}
		
		for (int i = 0; i < diffIndex; i++) {
			cout << differenceList[i] << " ";
		}
	}

	void isSubset() {
	    bool subsetFlag = true;
	    for (int i = 0; i < list1Size; i++) {
	        bool isInList2 = false;
	        for (int j = 0; j < list2Size; j++) {
	            if (list1[i] == list2[j]) {
	                isInList2 = true;
	                break;
	            }
	        }
	        if (!isInList2) {
	            subsetFlag = false;
	            break;
	        }
	    }
	    if (subsetFlag) {
	        cout << "List 1 is a subset of List 2.\n";
	    } else {
	        cout << "List 1 is NOT a subset of List 2.\n";
	    }
	}

    void displayList(int selectedList) {
        int currentSize = (selectedList == 1) ? list1Size : list2Size;
        int *targetList = (selectedList == 1) ? list1 : list2;

        Iterator iterator(targetList, currentSize);
        while (iterator.hasNext()) {
            cout << iterator.next() << " ";
        }
        cout << endl;
    }
};

int main() {
    int menuChoice, inputElement, listChoice, searchElement, numElementsList1, numElementsList2;
    string continueChoice;
    SetManager manager;

    cout << "Enter number of elements to add in List 1: ";
    cin >> numElementsList1;
    cout << "\nAdd elements to List 1 (each element must be unique as it's a set):" << endl;
    manager.addElements(numElementsList1, 0);

    cout << "\nEnter number of elements to add in List 2: ";
    cin >> numElementsList2;
    cout << "\nAdd elements to List 2 (each element must be unique as it's a set):" << endl;
    manager.addElements(numElementsList2, 1);

    do {
        cout << "\nMenu:";
        cout << "\n1. Display List 1";
        cout << "\n2. Display List 2";
        cout << "\n3. Remove element";
        cout << "\n4. Find element";
        cout << "\n5. Find size of list";
        cout << "\n6. Find Intersection";
        cout << "\n7. Find Union";
        cout << "\n8. Find Difference (List1 - List2)";
        cout << "\n9. Check if List1 is a subset of List2";
        cout << "\n10. Exit";
        cout << "\nEnter your choice: ";
        cin >> menuChoice;

        switch (menuChoice) {
            case 1:
                cout << "List 1 elements are: ";
                manager.displayList(1);
                break;

            case 2:
                cout << "List 2 elements are: ";
                manager.displayList(2);
                break;

            case 3:
                cout << "Enter list number (1 or 2): ";
                cin >> listChoice;
                cout << "Enter element to remove: ";
                cin >> inputElement;
                manager.removeElement(numElementsList1, listChoice, inputElement);
                break;

            case 4:
                cout << "Enter list number to search (1 or 2): ";
                cin >> listChoice;
                cout << "Enter element to find: ";
                cin >> searchElement;
                manager.findElement(listChoice, searchElement);
                break;

            case 5:
                cout << "Enter list number to find size (1 or 2): ";
                cin >> listChoice;
                manager.listSize(listChoice);
                break;
                
            case 6:
            	manager.findIntersection();
            	break;
            	
            case 7:
            	manager.findUnion();
            	break;
            	
            case 8:
            	manager.findDifference();
            	break;
            	
            case 9:
            	manager.isSubset();
            	break;
            	
            case 10:
                cout << "Thank you for using the software.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
                break;
        }

        if (menuChoice != 10) {
            cout << "\nDo you want to continue? (y/n): ";
            cin >> continueChoice;
        } else {
            continueChoice = "n";
        }
    } while (continueChoice == "y");
    return 0;
}

