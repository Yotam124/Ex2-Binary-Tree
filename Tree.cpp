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
using namespace ariel;


//Help functions *********************************************

void insertHelper(int key, node *leaf){
	if(key < leaf->value){
		if(leaf->left != NULL){
			insertHelper(key, leaf->left);
		}
		else{ //leaf->left == NULL
			node* newNode = new node;
			newNode->value = key;
			newNode->left = NULL;
			newNode->right = NULL;
			newNode->parent = leaf;
			leaf->left = newNode;
		}
	}
	else if(key > leaf->value){
		if(leaf->right != NULL){
			insertHelper(key, leaf->right);
		}
		else{
			node* newNode = new node;
			newNode->value = key;
			newNode->left = NULL;
			newNode->right = NULL;
			newNode->parent = leaf;
			leaf->right = newNode;
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

node* deleteNode(node* root, int k)
{
    // Base case
    if (root->right == NULL && root->left == NULL){
        delete root;
    	return NULL;
    }
    // Recursive calls for ancestors of
    // node to be deleted
    if (root->value > k) {
        root->left = deleteNode(root->left, k);
        return root;
    }
    else if (root->value < k) {
        root->right = deleteNode(root->right, k);
        return root;
    }

    // We reach here when root is the node
    // to be deleted.

    // If one of the children is empty
    if (root->left == NULL) {
        node* temp = root->right;
        temp->parent = root->parent;
        if (temp->value > temp->parent->value){
                	temp->parent->right = temp;
        }
        else{
        	temp->parent->left = temp;
        }
        delete root;
        return temp;
    }
    else if (root->right == NULL) {
        node* temp = root->left;
        temp->parent = root->parent;
        if (temp->value > temp->parent->value){
        	temp->parent->right = temp;
        }
        else{
        	temp->parent->left = temp;
        }
        delete root;
        return temp;
    }

    // If both children exist
    else {

        node* tempParent = root->right;

        // Find successor
        node *temp = root->right;
        while (temp->left != NULL) {
            tempParent = temp;
            temp = temp->left;
        }

        // Delete successor.  Since successor
        // is always left child of its parent
        // we can safely make successor's right
        // right child as left of its parent.
        tempParent->left = temp->right;
        if (temp->right != NULL){
        	temp->right->parent = tempParent;
        }
        // Copy Successor Data to root
        root->value = temp->value;

        // Delete Successor and return root
        delete temp;
        return root;
    }
}

void destroyTree(node* root){
	if (root != NULL){
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;

	}
}


//End of help functions ********************************************

Tree::Tree(){
	Size = 0;
	Root = NULL;
}

Tree::~Tree(){
	destroyTree(Root);
}


Tree& Tree::insert(int i){
	if((*this).Root != NULL){
		insertHelper(i, (*this).Root);
		(*this).Size++;
		return *this;
	}
	else{
		(*this).Root = new node;
		(*this).Root->value = i;
		(*this).Root->left = NULL;
		(*this).Root->right = NULL;
		(*this).Root->parent = NULL;
		(*this).Size++;
		return *this;
	}
}

Tree& Tree::remove(int key){
	if (boolSearch(key, (*this).Root) == true){
		node* nothing = deleteNode((*this).Root, key);
		this->Size--;
		return *this;
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
	if (Root != NULL){
		return this->Root->value;
	}
	else {
		throw std::invalid_argument("This value isn't exists in this tree");
	}
}

int Tree::parent(int i){
	node *sonNode = nodeSearch(i,Root);
	if (sonNode->parent != NULL){
		return (*sonNode).parent->value;
	}
	else{
		throw std::invalid_argument("This value isn't exists in this tree");
	}
}

int Tree::left(int i){
	if (boolSearch(i,this->Root) == false){
		throw std::invalid_argument("This value isn't exists in this tree");
	}
	node *parentNode = nodeSearch(i,Root);
	if (parentNode->left != NULL){
		return (*parentNode).left->value;
	}
	else{
		throw std::invalid_argument("This value isn't exists in this tree");
	}
}

int Tree::right(int i){
	node *parentNode = nodeSearch(i,Root);
	if (parentNode->right != NULL){
		return (*parentNode).right->value;
	}
	else{
		throw std::invalid_argument("This value isn't exists in this tree");
	}
}

void Tree::print(){
	inorder_print(Root);
	cout << "\n";
}



