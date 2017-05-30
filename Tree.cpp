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
void inorder(TreeNode* root);
void preorder(TreeNode* root);
void postorder(TreeNode* root);
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
  cout << "Postarray: " << postarray << endl;
  bool done = false;


  TreeNode* root = constructTree(postarray);
  cout << "Inorder traveral: " << endl;
  inorder(root);
  cout << endl;

  cout << "Preorder traveral: " << endl;
  preorder(root);
  cout << endl;

  cout << "Postorder traveral: " << endl;
  postorder(root);

}

TreeNode* newNode(char newvalue[])
{
    TreeNode* temp = new TreeNode();
    temp->left = temp->right = NULL;
    strcpy(temp->value, newvalue);
    return temp;
}

TreeNode* constructTree(char postfix[])
{
  stack<TreeNode *> st;
  TreeNode *t, *t1, *t2;
  bool done = false;
  char token[80] = "";

  int length = strlen(postfix);
  for(int i = 0; i < length; i++) {
    if (postfix[i] == ' '){
        //if not an operator, just push it onto the stack
        if(!isOperator(token[0])) {
              t = new TreeNode();
              strcpy(t->value, token);
              st.push(t);
        }
        //is an operator, take top two elements from the stack and attach them
        else {
              t = new TreeNode();
              strcpy(t->value, token);
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
        token[0] = '\0';
    }
    else {
      strncat(token, &(postfix[i]), 1);
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

void preorder(TreeNode* root)
{
    if(root)
    {
        cout << root->value << " " << flush;
        inorder(root->left);
        inorder(root->right);
    }
}

void postorder(TreeNode* root)
{
    if(root)
    {
        inorder(root->left);
        inorder(root->right);
        cout << root->value << " " << flush;
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
    char* token = new char[80];
    int i = 0;
    for(i; *input != ' ' && *input != '\0'; i++, input++) {
      token[i] = *input;
    }
    input++;
    token[i] = '\0';
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
