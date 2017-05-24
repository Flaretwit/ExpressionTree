#include "Node.h"
#include <iostream>
using namespace std;

/*
class -> Node
This class implements a stack using a LinkedList of Nodes
This will temporarily store the operands while building the expression tree
*/

//default construcsor
Node::Node() {
  next = NULL;
}

Node::Node(char* newData) {
  data = newData;
}
//deletes the Node by pointing its next pointer to NULL
Node::~Node() {
  next = NULL;
}
char * Node::getData(){
  return data;
}
//sets the next pointer to a Node.
void Node::setNext(Node* newNode) {
  next = newNode;
}
//returns next pointer
Node* Node::getNext() {
  return next;
}
