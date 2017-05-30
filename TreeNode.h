#include <iostream>

#ifndef TREENODE_H
#define TREENODE_H

class TreeNode{
 public:
  TreeNode();
  TreeNode(char* );
  ~TreeNode();
  TreeNode* getRight();
  TreeNode* getLeft();
  void setLeft(TreeNode* newLeft);
  void setRight(TreeNode* newRight);
  TreeNode* getNext();
  void setNext(TreeNode* newNext);
  char* getValue();
  void setValue(char newValue[100]);
  TreeNode* left;
  TreeNode* right;
  char value[100];
};

#endif
