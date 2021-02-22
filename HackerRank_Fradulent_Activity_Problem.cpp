// Link: https://www.hackerrank.com/challenges/fraudulent-activity-notifications/problem
// So far incomplete

#include <iostream>
using namespace std;

class Node{
  public:
  Node* left;
  Node* right;
  Node* parent;
  int value;
  Node(int v){
    value = v;
    left = NULL;
    right = NULL;
    parent = NULL;
  }
};

class BinaryTree{
  public:
  Node* root;
  void removeNode(Node* curr, int value){
    if(curr->value == value){
      if(curr->right == NULL && curr->left == NULL){
        curr = NULL;
        return;
      }

      while(true){
        if(curr->right != NULL){
          curr = curr->right;
        }else if(curr->left != NULL){
          curr = curr->left;
        }else{
          break;
        }
      }
    }else{
      if(curr->value < value){
        removeNode(curr->right, value);
      }else{
        removeNode(curr->left, value);
      }
    }
  }

  void addNode(Node* curr, int value){
    Node* child = findChild(curr, value);
    
    Node* save = child;

    while(child != NULL && child->value <= value){
      child = child->parent;
    }

    if(save == child){
      child->left = new Node(value);
      child->left->parent = child;
    }else{
      int formerValue = (*child).value;
      (*child).value = value;

      (*save).value = formerValue;
    }
  }

  Node* findChild(Node* curr, int value){
    if(curr->left == NULL && curr->right == NULL){
      return curr;
    }

    if(curr->value <= value){
      return findChild(curr->left, value);
    }else{
      return findChild(curr->right, value);
    }
  }
};