#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include "receipt.h"
#include "tablework.h"

struct Node
{
  Receipt data;
  Node* next;
  Node* prev;
};

class DoublyLinkedList
{
private:
public:
    DoublyLinkedList();
    Node* InitFirstNode(Receipt value);
    void InsertBegin(Node* &head, Receipt value);
    void InsertEnd(Node* &tail, Receipt value);
    void ShowListStraight(Node* head);
    void ShowListReverse(Node* tail);
    void InsertMiddle(Receipt value, Node* &node_before, Node* &node_after);
    void DeleteBegin(Node* &head);
    void DeleteEnd(Node* &tail);
    void DeleteMiddle(Node* &del);
    void MergeSort();
    Receipt NodeSearch(QString name, Node* head);
    void NodeSearchByParameter();
};

#endif // DOUBLYLINKEDLIST_H
