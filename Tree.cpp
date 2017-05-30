//Expression Tree by ke shen, 3/14/2017 kinda late
//Builds an expression tree form a postfix expression
//Also traverses that expression tree in order to obtain
//prefix, infix, or postfix expressions.
#include<bits/stdc++.h>
#include "TreeNode.h"
#include <iostream>
using namespace std;


bool isOperator(char c);
int precedence(char c);
void inorder(TreeNode* head);
char* infix_to_postfix(char input[1000]);
TreeNode* constructTree(char postfix[]);
TreeNode* newNode(char* value);

int main() {
  cout << "Enter infix expression: " << flush;
  char* input = new char[80];

  cin.getline(input, 1000);
  cin.clear();

  char* postarray = new char[80];
  postarray = infix_to_postfix(input);
  cout << "post array: " << postarray << flush;
  bool done = false;

  TreeNode* root = constructTree(postarray);
  inorder(root);
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

TreeNode* newNode(char newvalue[])
{
    TreeNode* temp = new TreeNode();
    temp->left = temp->right = NULL;
    strcpy(temp->value, newvalue);
    return temp;
}

TreeNode* constructTree(char* postfix)
{
  stack<TreeNode *> st;
  TreeNode *t, *t1, *t2;
  bool done = false;
  while(!done) {
    char* temp = new char[80];
    int i = 0;
    //iterates through the input pointer to get a char* token;
    for(i; *postfix != '\0' && *postfix != ' '; i++, postfix++) {
        temp[i] = *postfix;
    }
    postfix++;
    if(*postfix == '\0') {
      done = true;
    }
    //if not an operator, just push it onto the stack
    else if(!isOperator(temp[0])) {
          t = new TreeNode();
          strcpy(t->value, temp);
          st.push(t);
    }
    //is an operator, take top two elements from the stack and attach them
    else if(isOperator(temp[0])) {
          t = new TreeNode();
          strcpy(t->value, temp);
          // Pop two top nodes
          t1 = st.top(); // Store top
          st.pop();      // Remove top
          t2 = st.top();
          st.pop();

          //  make them children
          t->right = t1;
          t->left = t2;

          // Add this subexpression to stack
          st.push(t);
    }
  }

  //Only element remaining will be root of expression tree
  t = st.top();
  st.pop();

  return t;
}

//iterates through the expression inorder;
void inorder(TreeNode* root)
{
    if(root)
    {
        inorder(root->left);
        cout << root->value << " " << flush;
        inorder(root->right);
    }
}

//utility function to check if something is an operator
bool isOperator(char c) {
 if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
     return true;
 }
 return false;
}
//converts an infix expression to postfix;
char* infix_to_postfix(char input[1000]){
  stack<char*> st;

  char* output = new char[1000];
  bool done = false;

  while(!done) {
        char* temp = new char[80];
    char* token = new char[80];
    char* token1 = new char[80];

    int i = 0;
    for(int i = 0; *input != ' ' && *input != '\0'; i++, input++) {
      token[i] = *input;
    }
    input++;
    //when the expression has been completely read
    //pops all the remaning operators in the stack into the output
    if(token[0] == '\0') {
      while(!st.empty()) {
            strncat(output, st.top(), strlen(st.top()));
            strncat(output, " ", 1);
            st.pop();
      }
      done = true;
    }
    //if token is an digit, ib mmediately adds it to the output
    else if(isdigit(token[0])) {
      strncat(output, token, strlen(token));
      strncat(output, " ", 1);
    }

    //if token is a left parentheses, push onto stack
    else if(token[0] == '(') {
      st.push(token);
    }
    //if token is a right parentheses, discard it, then print and pop stack
    //until a left parentheses is found.
    else if(token[0] == ')') {
        while(*(st.top()) != '(') {
          strncat(output, st.top(), strlen(st.top()));
          strncat(output, " ", 1);
          st.pop();
        }
        //gets rid of left parentheses.
        st.pop();
    }
    //if the stack is empty or contains a left parentheses on top, push operator
    else if(st.empty() || *(st.top()) == '(') {
      st.push(token);
    }
    //if token is an operator, pop the stack until the operator on top
    //has the same or higher precedence. Then pushes the operator
    else if(isOperator(token[0])) {
      while(precedence(token[0]) < precedence(*(st.top()))) {
        strncat(output, st.top(), strlen(st.top()));
        strncat(output, " ", 1);
        st.pop();
        //if head is now null, breka out of the loop
        if(st.empty()) {
          break;
        }
      }
      //cout << "direcly here already" << flush;
      st.push(token);
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
