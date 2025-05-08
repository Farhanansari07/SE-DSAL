/*
A Dictionary stores keywords and its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry.
Provide facility to display whole data sorted in ascending/ Descending order.
Also find how many maximum comparisons may require for finding any keyword.
Use Height balance tree and find the complexity for finding a keyword.
*/

#include <iostream>
#include <string>
using namespace std;

// Node structure
struct Node {
    string key, meaning;
    Node* left;
    Node* right;
    int height;
};

// Utility to get height
int height(Node* root) {
    return root ? root->height : 0;
}

// Utility to get balance factor
int getBalance(Node* root) {
    return root ? height(root->left) - height(root->right) : 0;
}

// Create new node
Node* createNode(string key, string meaning) {
    Node* node = new Node();
    node->key = key;
    node->meaning = meaning;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Right rotate
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotate
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

// Search node
Node* searchNode(Node* root, string key) {
    while (root) {
        if (key == root->key)
            return root;
        else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return NULL;
}

// Insert node
Node* insert(Node* root, string key, string meaning) {
    if (!root)
        return createNode(key, meaning);

    if (key < root->key)
        root->left = insert(root->left, key, meaning);
    else if (key > root->key)
        root->right = insert(root->right, key, meaning);
    else
        return root;  // Duplicate, no update here

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Update node
bool updateMeaning(Node* root, string key, string newMeaning) {
    Node* node = searchNode(root, key);
    if (node) {
        node->meaning = newMeaning;
        return true;
    }
    return false;
}

// Min value node
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left)
        current = current->left;
    return current;
}

// Delete node
Node* deleteNode(Node* root, string key) {
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp)
                temp = root, root = NULL;
            else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Display ascending
void ascending(Node* root) {
    if (root) {
        ascending(root->left);
        cout << root->key << " : " << root->meaning << endl;
        ascending(root->right);
    }
}

// Display descending
void descending(Node* root) {
    if (root) {
        descending(root->right);
        cout << root->key << " : " << root->meaning << endl;
        descending(root->left);
    }
}

// Search keyword with comparisons
int search(Node* root, string key, int& comparisons) {
    while (root) {
        comparisons++;
        if (key == root->key) {
            cout << "Found: " << root->meaning << endl;
            return 1;
        } else if (key < root->key)
            root = root->left;
        else
            root = root->right;
    }
    return 0;
}

// Main
int main() {
    Node* root = NULL;
    int choice;
    string key, meaning;

    do {
        cout << "\n--- Dictionary Menu ---";
        cout << "\n1. Add Keyword";
        cout << "\n2. Update Meaning";
        cout << "\n3. Delete Keyword";
        cout << "\n4. Display Ascending";
        cout << "\n5. Display Descending";
        cout << "\n6. Search Keyword";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter keyword to add: ";
            cin >> key;
            if (searchNode(root, key)) {
                cout << "Keyword already exists. Use Update option.\n";
            } else {
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                root = insert(root, key, meaning);
            }
            break;
        case 2:
            cout << "Enter keyword to update: ";
            cin >> key;
            cout << "Enter new meaning: ";
            cin.ignore();
            getline(cin, meaning);
            if (updateMeaning(root, key, meaning))
                cout << "Updated successfully.\n";
            else
                cout << "Keyword not found.\n";
            break;
        case 3:
            cout << "Enter keyword to delete: ";
            cin >> key;
            root = deleteNode(root, key);
            break;
        case 4:
            cout << "Dictionary (Ascending Order):\n";
            ascending(root);
            break;
        case 5:
            cout << "Dictionary (Descending Order):\n";
            descending(root);
            break;
        case 6:
            cout << "Enter keyword to search: ";
            cin >> key;
            {
                int comparisons = 0;
                if (!search(root, key, comparisons))
                    cout << "Keyword not found.\n";
                cout << "Comparisons made: " << comparisons << endl;
            }
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 7);

    return 0;
}

