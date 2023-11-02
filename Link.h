//Connor Sullivan
//This file is used to define Linked list prototypes and node struct

//Headers
#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

#ifndef LINK_h
#define LINK_h

//Struct
//Nodes that make up the linled list
struct Node {
	int itemNum;
	char itemName[40];
	double unit;
	double unitPrice;
	double tax;
	double subTotal;
	Node* next;
};

//Prototypes
Node* insertNode(Node* &head, int itemNumber, char itemName[], char u, char t, double price, double subTotal);

void printList(Node* head);

Node* searchNode(Node *head, int id);

Node* deleteItem(Node* &head, int id);

void destroyList(Node* head);

void saveList(Node* head);

#endif
