#include "doublylinkedlist.h"

DoublyLinkedList::DoublyLinkedList()
{

}

Node* DoublyLinkedList::InitFirstNode(Receipt value)
{
    Node* first_node = new Node;
    Node* head;
    first_node->data = value;
    first_node->next = nullptr;
    first_node->prev = nullptr;
    head = first_node;
    return head;
}

void DoublyLinkedList::InsertBegin(Node* &head, Receipt value)
{
    Node* insert_node = new Node;
    insert_node->data = value;
    insert_node->next = head;
    head->prev = insert_node;
    head = insert_node;
    insert_node->prev = nullptr;
}

void DoublyLinkedList::InsertEnd(Node* &tail, Receipt value)
{
    Node* insert_node = new Node;
    insert_node->data = value;
    insert_node->prev = tail;
    tail->next = insert_node;
    tail = insert_node;
    insert_node->next = nullptr;
}

void DoublyLinkedList::InsertMiddle(Receipt value, Node* &node_before, Node* &node_after)
{
    Node* insert_node = new Node;
    insert_node->data = value;
    insert_node->prev = node_before;
    insert_node->next = node_after;
    node_before->next = insert_node;
    node_after->prev = insert_node;
}

void DoublyLinkedList::ShowListStraight(Node* head)
{
    Node* temp = head;
    while(temp != nullptr)
    {
        //вывод temp->data
        temp = temp->next;
    }
    delete temp;
}

void DoublyLinkedList::ShowListReverse(Node* tail)
{
    Node* temp = tail;
    while(temp != nullptr)
    {
        //вывод temp->data
        temp = temp->prev;
    }
    delete temp;
}

void DoublyLinkedList::DeleteBegin(Node* &head)
{
    if(head == nullptr) return;
    Node* del = head;
    head = head->next;
    if(head != nullptr)
    {
        head->prev = nullptr;
    }
    delete del;
}

void DoublyLinkedList::DeleteEnd(Node* &tail)
{
    if(tail == nullptr) return;
    Node* del = tail;
    tail = tail->prev;
    if(tail != nullptr)
    {
        tail->next = nullptr;
    }
    delete del;
}

void DoublyLinkedList::DeleteMiddle(Node* &del)
{
    Node* node_to_delete = del;
    del = del->next;
    node_to_delete->prev->next = node_to_delete->next;
    node_to_delete->next->prev = node_to_delete->prev;
    delete node_to_delete;
}

Receipt DoublyLinkedList::NodeSearch(QString name, Node* head)
{
    Node* temp = head;
    while(temp!=nullptr)
    {
        if(temp->data.GetName()==name)
        {
            return temp->data;
        }
        temp = temp->next;
    }
    delete temp;
    Receipt nul;
    return nul;
}











