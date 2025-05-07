#include<iostream>
using namespace std;

class Node {
	public:
	int data;
	Node* left;
	Node* right;
	
	Node(int val) {
		data = val;
		left = right = NULL;
	}
};

class BST {
public:
	Node* root;
		
	BST() {
		root = NULL;
	}
	
	//Insert
	void insert(int val) {
		Node* newNode = new Node(val);
		if(root == NULL) {
	    	root = newNode;
	    	return;
		}
		
		Node* current = root;
		while(true) {
			if(val < current->data) {
				if(current->left == NULL) {
					current->left = newNode;
					break;
				}
				current = current->left;
			} else if(val > current->data) {
				if(current->right == NULL) {
					current->right = newNode;
					break;
				}
				current = current->right;
			} else {
			    cout << "Duplicate entry not allowed";
			    return;
			}
		}
	}
	
	//Max Height
	int maxHeight(Node* node) {
	    if(node == NULL)
	        return 0;
	    return max(1+maxHeight(node->left) , 1+maxHeight(node->right));
	}
	
	//Min val
	int MinVal(Node* node) {
	    if(node == NULL) {
	        cout << "Tree is empty!" << endl;
	        return -1;
	    }
	    while(node->left != NULL) {
	        node = node->left;
	    }
	    return node->data;
	}
	
	void swap(Node* node) {
	    if(node == NULL)
	        return;
	    
	    Node* temp = node->left;
	    node->left = node->right;
	    node->right = temp;
	    
	    swap(node->left);
	    swap(node->right);
	}
	
	//search
	bool search(Node* node , int key) {
	    if(node==NULL) 
	        return false;
	    if(key == node->data) {
	            return true;
	    } 
	    else if(key < node->data) {
	        return search(node->left , key);
	    } 
	    else {
	        return search(node->right , key);
	    }
	}
	
	//Display
	void inorder(Node* node) {
	    if(node == NULL) 
	        return;
	    inorder(node->left);
	    cout << node->data << " ";
	    inorder(node->right);
	}
	
};

int main() {
	BST bst;
	int choise , val , key;
	
	do {
	    cout << "\nMenu\n";
	    cout << "1. Insert Node\n";
        cout << "2. Find Number of Nodes in Longest Path (Height)\n";
        cout << "3. Find Minimum Value in Tree\n";
        cout << "4. Swap Left and Right Pointers\n";
        cout << "5. Search a Value\n";
        cout << "6. Display Inorder Traversal\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choise;
        
        switch(choise) {
        case 1: 
            cout << "Enter value to insert: ";
            cin >> val;
            bst.insert(val);
            break;
            
        case 2:
            cout << "Number of nodes in longest path (Height): " << bst.maxHeight(bst.root) << endl;
            break;
            
        case 3:
            cout << "Minimum value in the tree: " << bst.MinVal(bst.root) << endl;
            break;
            
        case 4: 
            bst.swap(bst.root);
            cout << "Tree Swapped..." << endl;
            break;
            
        case 5: 
            cout << "Enter the value to search: ";
            cin >> key;
            if (bst.search(bst.root , key))
                cout << "Value found in the Tree" << endl;
            else
                cout << "Value not found in the Tree!" << endl;
            break;  
                
        case 6:
            cout << "Inorder Traversal: ";
            bst.inorder(bst.root);
            break;
            
        case 7:
            cout << "Exiting program..." << endl;
            return 0;

        default:
            cout << "Invalid choice! Please enter a valid option.\n";
        }
	} while(true);
	return 0;
}
