#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *next;
};

class LinkedList
{
private:
    Node *head;

public:
    LinkedList()
    {
        head = nullptr;
    }

    void insertAtBeginning(int value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = head;
        head = newNode;
        cout << value << " inserted at the beginning." << endl;
    }

    void insertAtEnd(int value)
    {
        Node *newNode = new Node;
        newNode->data = value;
        newNode->next = nullptr;
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = newNode;
        }
        cout << value << " inserted at the end." << endl;
    }

    void deleteFromBeginning()
    {
        if (head == nullptr)
        {
            cout << "List is empty. Cannot delete from beginning." << endl;
            return;
        }
        Node *temp = head;
        int deletedValue = temp->data;
        head = head->next;
        delete temp;
        cout << deletedValue << " deleted from the beginning." << endl;
    }

    void deleteFromEnd()
    {
        if (head == nullptr)
        {
            cout << "List is empty. Cannot delete from end." << endl;
            return;
        }
        if (head->next == nullptr)
        {
            int deletedValue = head->data;
            delete head;
            head = nullptr;
            cout << deletedValue << " deleted from the end." << endl;
            return;
        }
        Node *current = head;
        Node *previous = nullptr;
        while (current->next != nullptr)
        {
            previous = current;
            current = current->next;
        }
        int deletedValue = current->data;
        delete current;
        previous->next = nullptr;
        cout << deletedValue << " deleted from the end." << endl;
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "List is empty." << endl;
            return;
        }
        cout << "Linked List elements: ";
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main()
{
    LinkedList list;

    list.insertAtBeginning(10);
    list.insertAtEnd(20);
    list.insertAtEnd(30);
    list.display();

    list.deleteFromEnd();
    list.deleteFromBeginning();
    list.display();

    list.deleteFromBeginning(); // Trying to delete from an empty list
    list.deleteFromEnd();       // Trying to delete from an empty list

    return 0;
}
