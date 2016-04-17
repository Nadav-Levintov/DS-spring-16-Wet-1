/*
 * treeNode.h
 *
 *  Created on: 28 ???? 2015
 *      Author: user
 */

#ifndef TREENODE_H_
#define TREENODE_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#include "library1.h"
#define LOWEST_HEIGHT 0
template<class T>
class node {
private:
	T* data;
	node** ptrRoot;
	node* father;
	node* right;
	node* left;


public:
	int height;
	node(T* newData, node** newRoot, node* newFather = NULL) :
			ptrRoot(newRoot), father(newFather), right(NULL), left(NULL), height(
			LOWEST_HEIGHT) {
		data = new T(newData);
	}
	node(const node& old) :
			ptrRoot(old->root), father(old->Father), right(old->right), left(
					old->left), height(old->height) {
		data = new T(old->data);
	}
	~node() {
		delete data;
	}
	node& operator=(const node& old) {
		T* temp = new T(old.data);
		delete data;
		data = temp;
		ptrRoot = old.ptrRoot;
		father = old.father;
		right = old.right;
		left = old.left;
		height = old.height;
		return *this;
	}

	node* getRight() {
		return right;
	}
	node* getLeft() {
		return left;
	}
	T* GetData();
	T* GetCopyData(); //create
	T* GetLeftData() {
		return this->left->GetData();
	}
	T* GetRightData() {
		return this->right->GetData();
	}
	int GetLeftHeight();
	int GetRightHeight();
	void setLeft(node* left) {
		this->left = left;
	}
	void setRight(node* right) {
		this->right = right;
	}
	void setFather(node* father) {
		this->father = father;
	}
	void setHeight(int height) {
		this->height = height;
	}
	int getBF() {
		return (this->GetLeftHeight()) - (this->GetRightHeight());
	}
	int isUnbalanced();
	void roll();
	void LLroll();
	void LRroll();
	void RRroll();
	void RLroll();
	void printData() {
		cout << GetData() << " ";
	}
	void printAll();
	void printAllLess();
	StatusType add(T* data, node** ptrRoot);
	void printInOrder();
	void printAllInOrder();
	void printAllPreOrder();
	void setHeight();
	template<class U>
	friend void setHeight(node<U>*);
	template<class U>
	friend void swapNodes(node<U>* n1, node<U>* n2);
	template<class U>
	friend StatusType removeLeaf(node<U>* n);
	template<class U>
	friend StatusType removeSandwich(node<U>* n);
	template<class U>
	friend node<U>* find_w(node<U>* n);
	StatusType removeNode(T* data);
	T* GetMaxNode();
	void destroySubtree();
	bool isIn(T* data);
	void getAllDataInReverseOrder(T** arr, int limit);
	T* getData(T* key);
};

using std::max;

template<class T>
T* node<T>::GetData() {
	if (!this) {
		return NULL;
	}
	return this->data;
}

//returns height of left son
template<class T>
int node<T>::GetLeftHeight() {
	if (!this->left) {
		return LOWEST_HEIGHT - 1;
	}
	return this->left->height;
}

//returns height of right son
template<class T>
int node<T>::GetRightHeight() {
	if (!this->right) {
		return LOWEST_HEIGHT - 1;
	}
	return this->right->height;
}

//update height of node according to height of sons
template<class T>
void node<T>::setHeight() {
	if(!this) return;
	int R = LOWEST_HEIGHT - 1;
	int L = LOWEST_HEIGHT - 1;
	if (right) {
		R = right->height;
	}
	if (left) {
		L = left->height;
	}
	height = 1 + ((R < L) ? L : R);
}

//update height of node according to height of sons
template<class T>
void setHeight(node<T>* n) {
	int R = LOWEST_HEIGHT - 1;
	int L = LOWEST_HEIGHT - 1;
	if (n->right) {
		R = n->right->height;
	}
	if (n->left) {
		L = n->left->height;
	}
	n->height = 1 + ((R < L) ? L : R);

}

//prints all parameters of node
template<class T>
void node<T>::printAll() {
	//change if
	if (left && right) {
		cout << "data: ";
		GetData()->print();
		cout << ", height: " << height << ", left son data: ";
		GetLeftData()->print();
		cout << " left son height: " << GetLeftHeight() << " right son data: ";
		GetRightData()->print();
		cout << " right son height: " << GetRightHeight() << " BF: " << getBF() << endl;
	}
}

//prints some of the parameters of the node
template<class T>
void node<T>::printAllLess() {
	cout << "data: ";
	GetData()->print();
	if (height == 0) {
		cout << ", is leaf" << endl;
		assert(!left);
		assert(!right);
		return;
	} else {
		if (left) {
			cout << " Left: ";
			GetLeftData()->print();
		} else {
			cout << " Left: -- ";
		}
		if (right) {
			cout << " Right: ";
			GetRightData()->print();
		} else {
			cout << " Right: -- ";
		}
		cout << ", height: " << height << ", BF: " << getBF();
		cout << endl;
	}
}

//prints data of subtree in order
template<class T>
void node<T>::printInOrder() {
	if (left) {
		left->printInOrder();
	}
	printData();
	if (right) {
		right->printInOrder();
	}
}

//prints all parameters of node for subtree in order
template<class T>
void node<T>::printAllInOrder() {
	if (left) {
		left->printAllInOrder();
	}
	static int counter=0;
	counter++;
	printAll();
	if (right) {
		right->printAllInOrder();
	}
}

//prints all parameters of node for subtree in pre-order
template<class T>
void node<T>::printAllPreOrder() {
	printAllLess();
	if (left) {
		left->printAllPreOrder();
	}
	if (right) {
		right->printAllPreOrder();
	}
}

//returns indication for if a roll is needed
template<class T>
int node<T>::isUnbalanced() {
	int bf = this->getBF();
	if (bf == -1 || bf == 0 || bf == 1) {
		return 0;
	} else {
		assert(bf == 2 || bf == -2);

		return bf;
	}
}

//updates the node and performs a roll if necessary
template<class T>
void node<T>::roll() {
	setHeight();
	if (isUnbalanced() == 2) {
		if (left->getBF() >= 0) {
			LLroll(); ////////////////LL
		} else {
			assert(left->getBF() == -1);
			LRroll(); ///////////////LR
		}

	}
	if (isUnbalanced() == -2) {
		if (right->getBF() <= 0) {
			RRroll(); //////////////RR
		} else {
			assert(right->getBF() == 1);
			RLroll(); ///////////////RL
		}
	}
	setHeight();
}

//add a node with the data to the subtree
template<class T>
StatusType node<T>::add(T* newData, node<T>** ptrRoot) {
//	add if data is null
	StatusType stat;
	if (data->compare(newData)>0) {
		if (left != NULL) {
			stat = left->add(newData, ptrRoot);
			if (stat == SUCCESS) {
				roll();

			}
			return stat;
		} else {
			left = new node<T>(newData, ptrRoot, this);
			setHeight();
			return SUCCESS;
		}
	}
	if (data->compare(newData) < 0) {
		if (right != NULL) {
			stat = right->add(newData, ptrRoot);
			if (stat == SUCCESS) {
				roll();

			}
			return stat;
		} else {
			right = new node<T>(newData, ptrRoot, this);
			setHeight();
			return SUCCESS;
		}
	}
//	if node has the new data
	assert(data->compare(newData) == 0);
	return FAILURE;

}

//swaps the pointers of data between two nodes
template<class T>
void swapNodes(node<T>* n1, node<T>* n2) {
	T* temp = n1->data;
	n1->data = n2->data;
	n2->data = temp;
}

//performs LL roll
template<class T>
void node<T>::LLroll() {

	bool isRoot = false;

	node<T>* b = this;
	node<T>* a = this->left;
	node<T>* f = this->father;

	if (!b->father) {
		isRoot = true;
	}
	if (   b->father && (b->GetData()->compare(b->father->GetData()) ) < 0) { //which son am I
		f->left = a;
	} else if ( b->father && (b->GetData()->compare(b->father->GetData())>0) ) {
		f->right = a;
	}
	if (!isRoot) {
		f = b->father;
	} else { //if root than update pointer to root
		*ptrRoot = a;
	}
	b->father = a;
	node<T>* aRight = a->right;
	a->right = b;
	b->left = aRight;
	if (aRight)
		aRight->father = b;
	if (!isRoot) {
		a->father = f;
	} else {
		a->father = NULL;
	}

}

//performs RR roll
template<class T>
void node<T>::RRroll() {

	bool isRoot = false;

	node<T>* b = this;
	node<T>* a = this->right;
	node<T>* f = this->father;

	if (!b->father) {
		isRoot = true;
	}
	if ( b->father && (b->GetData()->compare(b->father->GetData()) < 0) ) { //which son am I
		f->left = a;
	} else if (b->father && (b->GetData()->compare(b->father->GetData()) > 0) ) {
		f->right = a;
	}
	if (!isRoot) {
		f = b->father;
	} else { //if root than update pointer to root
		*ptrRoot = a;
	}
	b->father = a;
	node<T>* aLeft = a->left;
	a->left = b;
	b->right = aLeft;
	if (aLeft)
		aLeft->father = b;
	if (!isRoot) {
		a->father = f;
	} else {
		a->father = NULL;
	}

}

//performs LR roll
template<class T>
void node<T>::LRroll() {
	this->left->RRroll(); //RR PART
	this->left->setHeight();
	this->left->left->setHeight();
	this->setHeight();

	this->LLroll(); // LL PART
	this->setHeight();
	this->father->setHeight();
}

//performs RL roll
template<class T>
void node<T>::RLroll() {
	this->right->LLroll(); //LL PART
	this->right->setHeight();
	this->right->right->setHeight();
	this->setHeight();

	this->RRroll(); // RR PART
	this->setHeight();
	this->father->setHeight();
}

//delete the node from tree in case its a leaf
template<class T>
StatusType removeLeaf(node<T>* n) {
	if (n == n->father->left) {
		n->father->left = NULL;

		delete n;
		return SUCCESS;
	} else {
		n->father->right = NULL;
		delete n;
		return SUCCESS;
	}
}

//delete the node from tree in case it has one son
template<class T>
StatusType removeSandwich(node<T>* n) {
	if (!n->left && n->right != NULL) { //have only right son

		if (n == n->father->left) { // the node is a left son itself
			n->father->setLeft(n->right);
			n->right->setFather(n->father);
			delete n;
			return SUCCESS;
		}
		// need to update heights when going back on recursive calls//
		else { //the node is a right son itself
			n->father->right = n->right;
			n->right->father = n->father;
			delete n;
			return SUCCESS;
			// need to update heights when going back on recursive calls//
		}
	} else if (!n->right && n->left != NULL) { // have only left son
		if (n == n->father->left) { // the node is a left son itself
			n->father->left = n->left;
			n->left->father = n->father;
			delete n;
			return SUCCESS;
			// need to update heights when going back on recursive calls//
		} else { //the node is a right son itself
			n->father->right = n->left;
			n->left->father = n->father;
			delete n;
			return SUCCESS;
			// need to update heights when going back on recursive calls//
		}
	}
	//assert(false);
	return SUCCESS;
}

//finds the next node in order
template<class T>
node<T>* find_w(node<T>* n) {
	n = n->right;
	while (n->left) {
		n = n->left;
	}
	//n->printData();
	return n;
}

template<class T>
T* node<T>::GetMaxNode() {

	node<T>* p = this;

	if (!this) {
		return NULL;
	} else {
		if(!right){
			return data;
		}
		while (p->right) {
			p = p->right;
		}
	}
	return p->data;
}

template<class T>
StatusType node<T>::removeNode(T* data) {
	StatusType stat;
	if (!this) { // don't exist
		return FAILURE;

	}

	else if (GetData()->compare(data) == 0) { // found it

		if (height == LOWEST_HEIGHT) { // leaf
			removeLeaf(this);

		}

		// need to update heights when going back on recursive calls//
		else if ((!left && right != NULL) //has only one son
		|| (!right && left != NULL)) {
			removeSandwich(this);
		} else { //has two sons
			node<T>* w = find_w(this);
			swapNodes(this, w);
			right->removeNode(w->GetData());
			roll();
//			if (w->height == LOWEST_HEIGHT) {
//				removeLeaf(w);
//			} else if ((!w->left && w->right != NULL)
//			|| (!w->right && w->left != NULL)) {
//				removeSandwich(w);
//			}
		}
	} else if (data->compare(GetData()) < 0) //Temporarily not using compare func
			{
		stat = left->removeNode(data);

		roll();
		return stat;

	} else if (data->compare(GetData()) > 0) {
		stat = right->removeNode(data);

		roll();
		return stat;

	}

	return SUCCESS;
}

template<class T>
void node<T>::destroySubtree(){
	if(left) left->destroySubtree();
	if(right) right->destroySubtree();
	if(this) delete this ;
}

template<class T>
bool node<T>::isIn(T* reqData){
	if(!this){
		return false;
	}
	if(data->compare(reqData)==0){
		return true;
	} else if(data->compare(reqData) < 0) {
		return right->isIn(reqData);
	} else {
		return left->isIn(reqData);
	}
}

template<class T>
T* node<T>::getData(T* key){
	if(!this){
		return NULL;
	}
	if(data->compare(key)==0){
		return new T(data);
	} else if(data->compare(key) < 0) {
		return right->getData(key);
	} else {
		return left->getData(key);
	}
}

template<class T>
void node<T>::getAllDataInReverseOrder(T** arr, int limit){
	static int iterator = 0;
	if(!this){
		return ;
	}
//	assert(iterator <= limit);
	if(right){
		right->getAllDataInReverseOrder(arr,limit);
	}
	arr[iterator] = data;
	iterator++;
	if(left){
		left->getAllDataInReverseOrder(arr,limit);
	}
	if(iterator==limit){
		iterator = 0;
	}
}



#endif /* TREENODE_H_ */
