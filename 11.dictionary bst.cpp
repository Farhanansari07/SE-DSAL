#include <iostream>
#include <string>
using namespace std;

// Structure for a BST Node
struct Node {
    string keyword;
    string meaning;
    Node *left, *right;
};

// Function to create a new node
Node* createNode(string key, string mean) {
    Node* newNode = new Node();
    newNode->keyword = key;
    newNode->meaning = mean;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert a new keyword into the BST
Node* insert(Node* root, string key, string mean) {
    if (root == NULL)
        return createNode(key, mean);

    if (key < root->keyword)
        root->left = insert(root->left, key, mean);
    else if (key > root->keyword)
        root->right = insert(root->right, key, mean);
    else
        cout << "Keyword already exists!\n";

    return root;
}

// Search a keyword and count comparisons
int search(Node* root, string key, int &comparisons) {
    if (root == NULL) return -1;
    
    comparisons++;
    if (key == root->keyword) return 1;

    if (key < root->keyword)
        return search(root->left, key, comparisons);
    else
        return search(root->right, key, comparisons);
}

// Find minimum value node (for deletion)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete a keyword
Node* deleteNode(Node* root, string key) {
    if (root == NULL) return root;

    if (key < root->keyword)
        root->left = deleteNode(root->left, key);
    else if (key > root->keyword)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = minValueNode(root->right);
        root->keyword = temp->keyword;
        root->meaning = temp->meaning;
        root->right = deleteNode(root->right, temp->keyword);
    }
    return root;
}

// Update meaning of a keyword
void update(Node* root, string key, string newMean) {
    if (root == NULL) {
        cout << "Keyword not found!\n";
        return;
    }

    if (key < root->keyword)
        update(root->left, key, newMean);
    else if (key > root->keyword)
        update(root->right, key, newMean);
    else
        root->meaning = newMean;
}

// Inorder traversal (Ascending Order)
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->keyword << " : " << root->meaning << endl;
    inorder(root->right);
}

// Reverse Inorder traversal (Descending Order)
void reverseInorder(Node* root) {
    if (root == NULL) return;
    reverseInorder(root->right);
    cout << root->keyword << " : " << root->meaning << endl;
    reverseInorder(root->left);
}

// Main function
int main() {
    Node* root = NULL;
    int choice;
    string key, mean;
    
    do {
        cout << "\nDictionary using BST";
        cout << "\n1. Insert Keyword";
        cout << "\n2. Search Keyword";
        cout << "\n3. Delete Keyword";
        cout << "\n4. Update Meaning";
        cout << "\n5. Display (Ascending Order)";
        cout << "\n6. Display (Descending Order)";
        cout << "\n7. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline from previous input

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, mean);
                root = insert(root, key, mean);
                break;

            case 2:
                int comparisons;
                cout << "Enter keyword to search: ";
                getline(cin, key);
                comparisons = 0;
                if (search(root, key, comparisons) == 1)
                    cout << "Keyword found in " << comparisons << " comparisons\n";
                else
                    cout << "Keyword not found!\n";
                break;

            case 3:
                cout << "Enter keyword to delete: ";
                getline(cin, key);
                root = deleteNode(root, key);
                break;

            case 4:
                cout << "Enter keyword to update: ";
                getline(cin, key);
                cout << "Enter new meaning: ";
                getline(cin, mean);
                update(root, key, mean);
                break;

            case 5:
                cout << "Dictionary in Ascending Order:\n";
                inorder(root);
                break;

            case 6:
                cout << "Dictionary in Descending Order:\n";
                reverseInorder(root);
                break;

            case 7:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 7);

    return 0;
}

