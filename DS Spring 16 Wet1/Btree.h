/*
 * Btree.h
 *
 *  Created on: 28 ???? 2015
 *      Author: user
 */

#ifndef BTREE_H_
#define BTREE_H_

#include "treeNode.h"



/*	class T must contain:
bool compare(T*)
print()
constructor for pointer
*/
template<class T>
class tree {
private:
	node<T>* root;
	T* biggestData;
	int numOfNodes;
public:

	tree() : root(NULL), biggestData(NULL), numOfNodes(0) {}
	~tree(){
		empty();
	}
	void printInOrder();
	void printAllPreOrder();
	void printAllInOrder();
	StatusType add(T* data);
	StatusType remove(T* data);
	T* getBiggestData();
	void empty();
	bool isIn(T* data);
	T* getData(T* key);
	T** getAllDataInReverseOrder(int* size);
	int getSize(){
		return numOfNodes;
	}


};

template<class T>
void tree<T>::printInOrder() {
	if(root){
		root->printInOrder();

	}
	else
	{
		cout<<"empty tree";
	}
	cout<<endl;
}

template<class T>
void tree<T>::printAllInOrder() {
	if(root){
		root->printAllInOrder();
	}
	else
	{
		cout<<"empty tree";
	}
	cout<<endl;
}

template<class T>
void tree<T>::printAllPreOrder() {
	if(root){
		root->printAllPreOrder();
	}
	else
	{
		cout<<"empty tree";
	}
	cout<<endl;
}

template<class T>
StatusType tree<T>::remove(T* data) {
	if (!root) {
		return FAILURE;
	}
	if(!isIn(data)){
		return FAILURE;
	}
	if (data->compare(root->GetData()) == 0) {
		if (root->height == LOWEST_HEIGHT) //	case for removal of root
		{
			delete root;
			root = NULL;
			this->biggestData=root->GetMaxNode();
			numOfNodes--;
			return SUCCESS;
		}

		if (!root->getLeft()) {
			node<T>* temp = root->getRight();
			delete root;
			root = temp;
			temp->setFather(NULL);
			this->biggestData=root->GetMaxNode();
			numOfNodes--;
			return SUCCESS;

		}
		else if(!root->getRight()) {
			node<T>* temp = root->getLeft();
			delete root;
			root = temp;
			temp->setFather(NULL);
			this->biggestData=root->GetMaxNode();
			numOfNodes--;
			return SUCCESS;
		}



	}
	StatusType stat = root->removeNode(data);
	if(stat==SUCCESS){
		this->biggestData=root->GetMaxNode();
		numOfNodes--;
	}
	return stat;
}

template<class T>
StatusType tree<T>::add(T* data) {
	StatusType stat;
	if(isIn(data)){
		return FAILURE;
	}
	if (root == NULL) {
		root = new node<T>(data,&root);
		this->biggestData=root->GetMaxNode();
		numOfNodes++;
		return SUCCESS;
	}
	stat = root->add(data,&root);
	if(stat==SUCCESS){
		this->biggestData=root->GetMaxNode();
		numOfNodes++;
	}
	return stat;
}


template<class T>
T* tree<T>::getBiggestData(){
	if(biggestData==NULL)
	{
		return NULL;
	}
	return new T(biggestData);
}

template<class T>
void tree<T>::empty(){
	if(root){
		root->destroySubtree();
		root = NULL;
		biggestData = NULL;
		numOfNodes = 0;
	}
}

template<class T>
bool tree<T>::isIn(T* data){
	if(root){
		return root->isIn(data);
	}
	return false;
}

template<class T>
T** tree<T>::getAllDataInReverseOrder(int* size){
	if(numOfNodes == 0){
		*size = 0;
		return NULL;
	}
	T** arr = new T*[numOfNodes];
	root->getAllDataInReverseOrder(arr,numOfNodes);
	*size = numOfNodes;
	return arr;
}

template<class T>
T* tree<T>::getData(T* key){
	if(root){
		return root->getData(key);
	}
	return NULL;
}

#endif /* BTREE_H_ */
