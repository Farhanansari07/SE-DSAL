/*
Read the marks obtained by students of second year in an online examination of particular subject. 
Find out maximum and minimum marks obtained in that subject. Use heap data structure. Analyze the algorithm.
*/

#include <iostream>
using namespace std;

void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void minHeapify(int arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(arr[i], arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

void buildMaxHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void buildMinHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

int main() {
    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    int marks[n];
    cout << "Enter the marks of students: ";
    for (int i = 0; i < n; i++)
        cin >> marks[i];

    // Create Max Heap for Maximum Marks
    buildMaxHeap(marks, n);
    cout << "Maximum Marks: " << marks[0] << endl;

    // Create Min Heap for Minimum Marks
    buildMinHeap(marks, n);
    cout << "Minimum Marks: " << marks[0] << endl;

    return 0;
}

