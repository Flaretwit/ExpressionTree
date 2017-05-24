//Expression Tree by ke shen, 3/14/2017 kinda late
//Builds an expression tree form a postfix expression
//Also traverses that expression tree in order to obtain
//prefix, infix, or postfix expressions.
#include<bits/stdc++.h>
#include "Node.h"
#include <iostream>

using namespace std;

bool isOperator(char c);
void inorder(Node* head);

int main() {
  cout << "Enter postfix expression: " << flush;
  char* input = new char[80];
  cin >> input;
  bool done = false;
  stack<Node*> st;
  //Head pointer of the stack, also will become the roto node of the tree.

  while(!done) {
    char* token = new char[80];
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
          Node* temp = new Node(token);
          st.push(temp);
    }
    else if(isOperator(token[0])) {
          Node* temp = new Node(token);
          Node* temp2 = st.top();
          Node* temp3 = st.top();
          st.pop();
          st.pop();
          temp->setRight(temp2);
          temp->setLeft(temp3);
          cout << "temp" << temp->getData() << endl;
          st.push(temp);
    }
  }
  cout << "Done inputting stuff to the stack" << endl;
  cout << st.size() << endl;
  cout << "Stack top" << st.top()->getData();
  Node* node = st.top();
  cout << node->getData() << endl;
  cout << node->getLeft()->getData() << endl;
  cout << node->getRight()->getData() << endl;
  inorder(st.top());
  return 0;

}

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

//utility function to check if something is an operator
bool isOperator(char c) {
 if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
     return true;
 }
 return false;
}

char* infix_to_postfix(char input[1000]){
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
            cout << pop(head)->getData() << flush;
      }
      done = true;
    }
    //if token is an digit, immediately prints it
    else if(isdigit(token[0])) {
      //cout << "Is a digit." << endl;
      cout << token[0] << flush;
    }
    //if token is a left parentheses, push onto stack
    else if(token[0] == '(') {
        Node* node = new Node(token[0]);
        push(head, node);
    }
    //if token is a right parentheses, discrd it, then print and pop stack
    //until a left parentheses is found.
    else if(token[0] == ')') {
        while(head->getData() != '(') {
          cout << pop(head)->getData() << flush;
        }
        //gets rid of left parentheses.
        pop(head);
    }
    //if the stack is empty or contains a left parentheses on top, push operator
    else if(head == NULL || head->getData() == '(') {
      //cout << "First time?" << flush;
      Node* node = new Node(token[0]);
      push(head, node);
    }
    //if token is an operator, pop the stack until the operator on top
    //has the same or higher precedence. Then pushes the operator
    else if(isOperator(token[0])) {
      while(precedence(token[0]) < precedence(head->getData())) {
        cout << pop(head)->getData() << flush;
        //if head is now null, breka out of the loop
        if(head == NULL) {
          break;
        }
      }
      //cout << "direcly here already" << flush;
      Node* node = new Node(token[0]);
      push(head, node);
    }

}
}
