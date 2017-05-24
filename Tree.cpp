//Expression Tree by ke shen, 3/14/2017 kinda late
//Builds an expression tree form a postfix expression
//Also traverses that expression tree in order to obtain
//prefix, infix, or postfix expressions.
#include<bits/stdc++.h>
#include "Node.h"
#include "TreeNode.h"
#include <iostream>

using namespace std;

Node* pop(Node*& head);
void push(Node*& head, Node* node);
bool isOperator(char c);
int precedence(char c);
void inorder(Node* head);
char* infix_to_postfix(char input[1000]);

int main() {
  cout << "Enter infix expression: " << flush;
  char* input = new char[80];

  cin.getline(input, 1000);
  cin.clear();

  char* postarray = new char[80];
  postarray = infix_to_postfix(input);
  cout << "post array: " << postarray << flush;
  bool done = false;

  Node* head = new Node();
  //Hea
  while(!done) {
    char token[80];
    int i = 0;
    //iterates through the input pointer to get a char* token;
    for(i; *input != '\0', *input == ' '; i++, input++) {
        token[i] = *input;
    }
    input++;
    if(*input == '\0') {
      done = true;
    }
    else if(!isOperator(token[0])) {
          TreeNode* temp = new TreeNode();
          temp->setValue(token);
          Node* ntemp = new Node();
          ntemp->tn = temp;
          push(head, ntemp);
    }
    else if(isOperator(token[0])) {
          TreeNode* temp = new TreeNode();
          temp->setValue(token);
          TreeNode* temp2 = pop(head)->tn;
          TreeNode* temp3 = pop(head)->tn;
          temp->setRight(temp2);
          temp->setLeft(temp3);
          cout << "temp" << temp->getValue() << endl;
          Node* ntemp = new Node();
          ntemp->tn = temp;
          push(head, ntemp);
    }
  }
  cout << "Done inputting stuff to the stack" << endl;
  /*
  cout << "Stack top" << st.top()->getData();
  Node* node = st.top();
  cout << node->getData() << endl;
  cout << node->getLeft()->getData() << endl;
  cout << node->getRight()->getData() << endl;
  inorder(st.top());
  return 0;
  */

}
/*
//iterates through the expression inorder;
void inorder(Node* head)
{
    if(head)
    {
        inorder(head->getLeft());
        cout << head->getData() << " " << flush;
        inorder(head->getRight());
    }
}
*/
//utility function to check if something is an operator
bool isOperator(char c) {
 if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
     return true;
 }
 return false;
}

char* infix_to_postfix(char input[1000]){
  Node* head = new Node();
  char* output = new char[1000];
  bool done = false;
  while(!done) {
    char* token = new char[80];
    int i = 0;
    for(int i = 0; *input != ' ' && *input != '\0'; i++, input++) {
      token[i] = *input;
    }
    input++;
    //cout << "Token: (" << token[0] << ")" << endl;
    //when the expression has been completely read
    //pops all the remaning operators in the stack into the output
    if(token[0] == '\0') {
      while(head != NULL) {
            strncat(output, head->getData(), strlen(head->getData()));
            pop(head);
      }
      done = true;
    }
    //if token is an digit, immediately adds it to the output
    else if(isdigit(token[0])) {
      //cout << "Is a digit." << endl;
      strncat(output, token, strlen(token));
    }
    //if token is a left parentheses, push onto stack
    else if(token[0] == '(') {
        Node* node = new Node(token);
        push(head, node);
    }
    //if token is a right parentheses, discard it, then print and pop stack
    //until a left parentheses is found.
    else if(token[0] == ')') {
        while(*(head->getData()) != '(') {
          strncat(output, head->getData(), strlen(head->getData()));
          pop(head);
        }
        //gets rid of left parentheses.
        pop(head);
    }
    //if the stack is empty or contains a left parentheses on top, push operator
    else if(head == NULL || *(head->getData()) == '(') {
      //cout << "First time?" << flush;
      Node* node = new Node(token);
      push(head, node);
    }
    //if token is an operator, pop the stack until the operator on top
    //has the same or higher precedence. Then pushes the operator
    else if(isOperator(token[0])) {
      while(precedence(token[0]) < precedence(*(head->getData()))) {
        strncat(output, head->getData(), strlen(head->getData()));
        pop(head);
        //if head is now null, breka out of the loop
        if(head == NULL) {
          break;
        }
      }
      //cout << "direcly here already" << flush;
      Node* node = new Node(token);
      push(head, node);
    }
  }
  return output;
}
//returns the precednece of the character
int precedence(char c) {
  if(c == '+' || c == '-') {
    return 1;
  }
  if(c == '*' || c == '/') {
    return 2;
  }
  if(c == '^') {
    return 3;
  }
}

//deletes and returns the current inserted node while setting head to
Node* pop(Node*& head) {
  Node* current = head;
  head = head->getNext();
  return current;
}
//adds a node to the top of the stack (implemented as a Linkedlist)
void push(Node*& head, Node* node) {
  node->setNext(head);
  head = node;
}
