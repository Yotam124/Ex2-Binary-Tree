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
		if(leaf->left != nullptr){
			insertHelper(key, leaf->left);
		}
		else{ //leaf->left == NULL
			node* newNode = new node;
			newNode->value = key;
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->parent = leaf;
			leaf->left = newNode;
		}
	}
	else if(key > leaf->value){
		if(leaf->right != nullptr){
			insertHelper(key, leaf->right);
		}
		else{
			node* newNode = new node;
			newNode->value = key;
			newNode->left = nullptr;
			newNode->right = nullptr;
			newNode->parent = leaf;
			leaf->right = newNode;
		}
	}
	else { //key == leaf->value
		throw std::invalid_argument("This value already exists in this tree");
	}
}

bool boolSearch(int key, node *leaf){
	if(leaf != nullptr){
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
  if(leaf!=nullptr)
  {
    if(key==leaf->value)
      return leaf;
    if(key<leaf->value)
      return nodeSearch(key, leaf->left);
    else
      return nodeSearch(key, leaf->right);
  }
  else return nullptr;
}

void inorder_print(node *leaf){
	if(leaf != nullptr){
		inorder_print(leaf->left);
		cout << leaf->value << ",";
		inorder_print(leaf->right);
	}
}

node* FindMax(node* root){
    if(root==nullptr){
    	return nullptr;
    }
    while(root->right != nullptr) {
        root = root->right;
    }
    return root;
}

void DeleteNode(node* &root,int data){

    if(root==nullptr){
    	return;
    }

    else if(data < root->value){

        DeleteNode(root->left, data);
    }

    else if (data > root->value){

        DeleteNode(root->right, data);
    }
    else {
        //No child
        if(root->right == nullptr && root->left == nullptr) {

        	delete root;
        	root = nullptr;
        }

        //One child
        else if(root->right == nullptr){

            node* temp = root;
            root= root->left;

            delete temp;
            temp = nullptr;

        }

        else if(root->left == nullptr) {

            node* temp = root;

            root= root->right;

            delete temp;
            temp = nullptr;
        }

        //two child

        else{

            node* temp = FindMax(root->left);

            root->value = temp->value;

            DeleteNode(root->left, temp->value);

        }

    }

}



void destroyTree(node* root){
	if (root != nullptr){
		destroyTree(root->left);
		destroyTree(root->right);
		delete root;

	}
}


//End of help functions ********************************************

Tree::Tree(){
	Size = 0;
	Root = nullptr;
}

Tree::~Tree(){
	destroyTree(Root);
}


Tree& Tree::insert(int i){
	if((*this).Root != nullptr){
		insertHelper(i, (*this).Root);
		(*this).Size++;
		return *this;
	}
	else{
		(*this).Root = new node;
		(*this).Root->value = i;
		(*this).Root->left = nullptr;
		(*this).Root->right = nullptr;
		(*this).Root->parent = nullptr;
		(*this).Size++;
		return *this;
	}
}

Tree& Tree::remove(int key){
	if (boolSearch(key, (*this).Root) == true){
		DeleteNode((*this).Root, key);
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
	if (Root != nullptr){
		return this->Root->value;
	}
	else {
		throw std::invalid_argument("This value isn't exists in this tree");
	}
}

int Tree::parent(int i){
	node *sonNode = nodeSearch(i,Root);
	if (sonNode->parent != nullptr){
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
	if (parentNode->left != nullptr){
		return (*parentNode).left->value;
	}
	else{
		throw std::invalid_argument("This value isn't exists in this tree");
	}
}

int Tree::right(int i){
	node *parentNode = nodeSearch(i,Root);
	if (parentNode->right != nullptr){
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



