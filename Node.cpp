#include <iostream>
#include "Node.h"

using namespace std;
//constructs a new Node with data newData
Node::Node(char* newData) {
  data = newData;
  left = right = NULL;
}
//default constructor
Node::Node() {
  left = right = NULL;
}
//deletes the Node by pointing its next pointer to NULL
Node::~Node() {
  right = NULL;
  left = NULL;
}
//returns the data (character) in the Node
char* Node::getData() {
  return data;
}
//sets the left pointer to a Node.
void Node::setLeft(Node* newNode) {
  left = newNode;
}
//sets the right pointer to a Node.
void Node::setRight(Node* newNode) {
  right = newNode;
}

Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}
