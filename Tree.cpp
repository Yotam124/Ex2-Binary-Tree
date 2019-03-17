/*
 * Tree.cpp
 *
 *  Created on: 13 Mar 2019
 *      Author: yotam dafna, tomer hazan, matti stern
 */

/* Sources we used for help:
 * https://stackoverflow.com/questions/40262794/c-delete-node-from-binary-search-tree
 * https://www.cprogramming.com/tutorial/lesson18.html
 */

#include <iostream>
#include "Tree.hpp"

using namespace std;

Tree::Tree(){
	this->Root = NULL;
}

//Help functions *********************************************

void insertHelper(int key, node *leaf){
	if(key < leaf->value){
		if(leaf->left != NULL){
			insertHelper(key, leaf->left);
		}
		else{
			leaf->left = new node;
			leaf->left->value = key;
			leaf->left->left = NULL;
			leaf->left->right = NULL;
			leaf->left->parent = leaf;
		}
	}
	else if(key > leaf->value){
		if(leaf->right != NULL){
			insertHelper(key, leaf->right);
		}
		else{
			leaf->right = new node;
			leaf->right->value = key;
			leaf->right->right = NULL;
			leaf->right->left = NULL;
			leaf->right->parent = leaf;
		}
	}
	else { //key == leaf->value
		throw std::invalid_argument("This value already exists in this tree");
	}
}

bool boolSearch(int key, node *leaf){
	if(leaf != NULL){
		if(key == leaf->value){
			return true;
		}
		if(key < leaf->value){
			return boolSearch(key, leaf->left);
		}
		else{
			return boolSearch(key, leaf->right);
		}
	}
	else{
		return false;
	}
}

node* nodeSearch(int key, node *leaf)
{
  if(leaf!=NULL)
  {
    if(key==leaf->value)
      return leaf;
    if(key<leaf->value)
      return nodeSearch(key, leaf->left);
    else
      return nodeSearch(key, leaf->right);
  }
  else return NULL;
}

void inorder_print(node *leaf){
	if(leaf != NULL){
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

node* findMin(node* root){ //Side function for removeHelper
    if(root == NULL) {
        cout << "\nThe tree is empty.";
        return root;
    }
    else {
        node* temp = root;
        while(temp->left != NULL)
            temp = temp->left;
        return temp;
    }
}

node* deleteNode(int key, node *root){
	if (key < root->value){
		deleteNode(key, root->left);
	}
	else if (key > root->value){
		deleteNode(key, root->right);
	}
	else{
		 if(root->left == NULL && root->right == NULL) {
		            delete root;
		            root = NULL;
		 }
		 else if(root->left == NULL){

		            node* temp = root;
		            root = root->right;
		            delete temp;
		 }
		 else if(root->right == NULL) {
		            node* temp = root;
		            root = root->left;
		            delete temp;
		 }
		 else {
		            node* temp = findMin(root->right);
		            root->value = temp->value;
		            root->right = deleteNode(temp->value, root->right);
		 }
	}
	return root;
}

//End of help functions ********************************************


Tree& Tree::insert(int i){
	Tree *tree = this;
	if((*tree).Root != NULL){
		insertHelper(i, (*tree).Root);
		(*tree).Size++;
		return *tree;
	}
	else{
		(*tree).Root = new node;
		(*tree).Root->value = i;
		(*tree).Root->left = NULL;
		(*tree).Root->right = NULL;
		(*tree).Size++;
		return *tree;
	}
}

Tree& Tree::remove(int key){
	Tree *tree = this;
	if (boolSearch(key, tree->Root) == true){
		(*tree).Root = deleteNode(key, (*tree).Root);
		tree->Size--;
		return *tree;
	}
	else{
		throw std::invalid_argument("This value isn't exists in this tree");
		return *this;
	}
}

int Tree::size(){
	return this->Size;
}

bool Tree::contains(int i){
	return boolSearch(i, Root);
}

int Tree::root(){
	return this->Root->value;
}

int Tree::parent(int i){
	node *sonNode = nodeSearch(i,Root);
	return (*sonNode).parent->value;
}

int Tree::left(int i){
	node *parentNode = nodeSearch(i,Root);
		return (*parentNode).left->value;
}

int Tree::right(int i){
	node *parentNode = nodeSearch(i,Root);
		return (*parentNode).right->value;
}

void Tree::print(){
	inorder_print(Root);
	cout << "\n";
}



