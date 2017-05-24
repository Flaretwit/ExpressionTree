#include "Node.h";
#include "BinaryNode.h"
#include <iostream>
using namespace std;

/*
class -> Node
This class implements a stack using a LinkedList of Nodes
This will temporarily store the operands while building the expression tree

*/
using namespace std;
//constructs a new Node with data newData
Node::Node(char* newData) {
  data = newData;
  next = NULL;
}
//default constructor
Node::Node() {
  next = NULL;
}
//deletes the Node by pointing its next pointer to NULL
Node::~Node() {
  next = NULL;
}
//returns the data (character) in the Node
char* Node::getData() {
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
