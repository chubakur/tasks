#include "btree.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

btree* btree_init(){
  btree* ptr = (btree*) calloc(1, sizeof(btree));
  return ptr;
}

btree_node* btree_add(btree* tree, char* value){
  if(tree->top == NULL){
    tree->top = (btree_node*) calloc(1, sizeof(btree_node));
    tree->top->value = value;
    tree->top->color = 'b'; //может только черный?
    return tree->top;
  }else{
    btree_node* current_node = tree->top;
    while(1){
      int comp = strcmp(value, current_node->value);
      if(comp == 0) return current_node;
      else if(comp < 0){
        if(current_node->left == NULL){
          current_node->left = (btree_node*) calloc(1, sizeof(btree_node));
          current_node->left->parent = current_node;
          current_node->left->value = value;
          current_node->left->color = 'r';
          btree_balancing(tree, current_node->left);
          return current_node->left;
        }else{
          current_node = current_node->left;
          continue;
        }
      }else{
        if(current_node->right == NULL){
          current_node->right = (btree_node*) calloc(1, sizeof(btree_node));
          current_node->right->parent = current_node;
          current_node->right->value = value;
          current_node->right->color = 'r';
          btree_balancing(tree, current_node->right);
          return current_node->right;
        }else{
          current_node = current_node->right;
          continue;
        }
      }
    }
  }
}

void btree_free(btree* tree){
  if(tree->top) btree_node_free(tree->top);
  free(tree);
}

void btree_node_free(btree_node* node){
  if(node->right) btree_node_free(node->right);
  if(node->left) btree_node_free(node->left);
  free(node->value);
  free(node);
}

bool btree_contains(btree* tree, char* value){
  btree_node* current_node = tree->top;
  while(current_node != NULL){
    int cmp = strcmp(value, current_node->value);
    if(cmp == 0) return 1;
    else if(cmp < 0) current_node = current_node->left;
    else current_node = current_node->right;
  }
  return 0;
}

void btree_balancing(btree* tree, btree_node* node){
  while(node != tree->top && node->parent->color == 'r'){
    //if(node->parent == NULL) puts("ALERT");
    btree_node* grandpa = node->parent->parent;
    if(node->parent == grandpa->left){
      //дядя справа
      btree_node* uncle = grandpa->right;
      if(uncle && uncle->color == 'r'){
        node->parent->color = 'b';
        uncle->color = 'b';
        grandpa->color = 'r';
        node = grandpa;
      }else{
        if(node == node->parent->right){
          //правый ребенок
          node = node->parent;
          btree_node_left_rotation(tree, node);
        }
        node->parent->color = 'b';
        node->parent->parent->color = 'r';
        btree_node_right_rotation(tree, node->parent->parent);
      }
    }else{
      btree_node* uncle = grandpa->left;
      if(uncle && uncle->color == 'r'){
        node->parent->color = 'b';
        uncle->color = 'b';
        grandpa->color = 'r';
        node = grandpa;
      }else{
        if(node == node->parent->left){
          //левый ребенок
          node = node->parent;
          btree_node_right_rotation(tree, node);
        }
        node->parent->color = 'b';
        node->parent->parent->color = 'r';
        btree_node_left_rotation(tree, node->parent->parent);
      }
    }
  }
  tree->top->color =  'b';
}

void btree_node_left_rotation(btree* tree, btree_node* x){
  btree_node* y = x->right;
  x->right = y->left;
  if (y->left != NULL) y->left->parent = x;
  if (y != NULL) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->left)
      x->parent->left = y;
    else
      x->parent->right = y;
  } else {
      tree->top = y;
  }

  y->left = x;
  if (x != NULL) x->parent = y;
}

void btree_node_right_rotation(btree* tree, btree_node* x){
  btree_node* y = x->left;
  x->left = y->right;
  if (y->right != NULL) y->right->parent = x;
  if (y != NULL) y->parent = x->parent;
  if (x->parent) {
    if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
  } else {
    tree->top = y;
  }
  y->right = x;
  if (x != NULL) x->parent = y;
}

void btree_print(btree* tree){
  printf("TOP:%s", tree->top->value);
}
