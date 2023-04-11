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
    Node* ShowListStraight(Node* head, int i);
    void ShowListReverse(Node* tail);
    void InsertMiddle(Receipt value, Node* &node_before, Node* &node_after);
    void DeleteBegin(Node* &head);
    void DeleteEnd(Node* &tail);
    int DeleteMiddle(QString name, Node* head);
    Node* MergeSort(Node* head);
    Receipt NodeSearch(QString name, Node* head);
    void NodeSearchByParameter();
};

#endif // DOUBLYLINKEDLIST_H
