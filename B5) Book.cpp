/*
A book consists of chapters, chapters consist of sections and sections consist of subsections.
Construct a tree and print the nodes. Find the time and space requirements of your method.
*/

#include <iostream>
#include <string>

using namespace std;

struct Node 
{
    string title;
    Node* firstChild;
    Node* nextSibling;

    Node(string t) : title(t), firstChild(NULL), nextSibling(NULL) {}
};

Node* addChild(Node* parent, const string& childTitle) 
{
    Node* child = new Node(childTitle);
    if (!parent->firstChild)
    {
        parent->firstChild = child;
    }
    else
    {
        Node* temp = parent->firstChild;
        while (temp->nextSibling) 
        {
            temp = temp->nextSibling;
        }
        temp->nextSibling = child;
    }
    return child;
}

void display(Node* node, int depth = 0) 
{
    if (node == NULL) return;
    for (int i = 0; i < depth; ++i) cout << "  ";
    cout << node->title << endl;
    display(node->firstChild, depth + 1);
    display(node->nextSibling, depth);
}

int main() {
    Node* book = new Node("Book");

    int numChapters;
    cout << "Enter number of chapters: ";
    cin >> numChapters;
    cin.ignore(); 
    for (int i = 0; i < numChapters; ++i)
    {
        string chapterTitle;
        cout << "Enter title of Chapter " << i + 1 << ": ";
        getline(cin, chapterTitle);
        Node* chapter = addChild(book, chapterTitle);

        int numSections;
        cout << "Enter number of sections in \"" << chapterTitle << "\": ";
        cin >> numSections;
        cin.ignore();

        for (int j = 0; j < numSections; ++j)
        {
            string sectionTitle;
            cout << "  Enter title of Section " << j + 1 << ": ";
            getline(cin, sectionTitle);
            Node* section = addChild(chapter, sectionTitle);

            int numSubsections;
            cout << "  Enter number of subsections in \"" << sectionTitle << "\": ";
            cin >> numSubsections;
            cin.ignore();

            for (int k = 0; k < numSubsections; ++k) 
            {
                string subsectionTitle;
                cout << "    Enter title of Subsection " << k + 1 << ": ";
                getline(cin, subsectionTitle);
                addChild(section, subsectionTitle);
            }
        }
    }

    cout << "\n--- Book Structure ---\n";
    display(book);

    return 0;
}

