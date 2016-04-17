/*
 * DataStruct.cpp
 *
 *  Created on: 4 ???? 2015
 *      Author: user
 */

#include "DataStruct.h"
#include "troll.h"
#include "post.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

Post* DataStruct::getMaxPost() {
	return PostTree->getBiggestData();
}

StatusType DataStruct::addTroll(int id) {
	try {
		Troll* newTroll = new Troll(id);
		if (!(this->firstTroll)) {
			this->firstTroll = newTroll;
			return SUCCESS;
		} else {
			Troll* tempTroll = firstTroll;
			while (tempTroll) {
				if (tempTroll->getId() == id) {
					delete newTroll;
					return FAILURE;
				}
				tempTroll = tempTroll->getNextTroll();

			}
			tempTroll = firstTroll;
			while (tempTroll->getNextTroll()) {
				tempTroll = tempTroll->getNextTroll();
			}
			tempTroll->setNextTroll(newTroll);
			return SUCCESS;
		}
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

}

StatusType DataStruct::PublishPost(int PostID, int TrollID, int Likes) {
	StatusType stat;
	PostById newPostById(PostID, Likes, TrollID);
	Post newPost(PostID, Likes, TrollID);

	//check if Post exist in PostTreeById tree
	if (PostTreeById->isIn(&newPostById)) {
		return FAILURE;
	}
	//check if Troll exist
	Troll* TrollTemp = findTroll(TrollID);
	if(TrollTemp==NULL){
		return FAILURE;
	}
	//add new Post to two main trees and Troll's tree
	try {
		stat = PostTree->add(&newPost);
		assert(stat == SUCCESS);
		stat = PostTreeById->add(&newPostById);
		assert(stat == SUCCESS);
		stat = TrollTemp->addPost(&newPost);
		assert(stat == SUCCESS);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType DataStruct::DeletePost(int PostID) {

	PostById postById = PostById(PostID);

	//check if Post exists in PostTreeById tree
	if (!PostTreeById->isIn(&postById)) {
		return FAILURE;
	}

	//create Posts for finding them in trees
	PostById* postByIdOld = PostTreeById->getData(&postById);
	Post post = Post(PostID, postByIdOld->getLikes());

	//free Post from two main trees
	PostTree->remove(&post);
	PostTreeById->remove(&postById);

	//free Post from it's Troll's tree
	Troll* tempTroll = findTroll(postByIdOld->GetMyTroll());
	assert( tempTroll != NULL );
	tempTroll->getPostTree()->remove(&post);

	delete postByIdOld;	//release Post returned for knowing its Likes

	return SUCCESS;
}

StatusType DataStruct::FeedTroll(int PostID, int LikesIncrease) {

	PostById postOnlyId = PostById(PostID);

	//check if Post exists in PostTreeById tree
	if (!PostTreeById->isIn(&postOnlyId)) {
		return FAILURE;
	}

	try {
		//create Posts for remove and re-adding them with new Likes
		PostById* postByIdOld = PostTreeById->getData(&postOnlyId);
		Post postOld = Post(PostID, postByIdOld->getLikes(),postByIdOld->GetMyTroll());
		PostById newpostById(PostID, postByIdOld->getLikes() + LikesIncrease,postByIdOld->GetMyTroll());
		Post newPost(PostID, postOld.getLikes() + LikesIncrease, postOld.GetMyTroll());

		//remove Post with old Likes and add with new Likes to trees
		PostTreeById->remove(postByIdOld);
		PostTreeById->add(&newpostById);
		PostTree->remove(&postOld);
		PostTree->add(&newPost);

		//remove Post with old Likes and add with new Likes to Troll's tree
		Troll* tempTroll = findTroll(postByIdOld->GetMyTroll());
		assert( tempTroll != NULL );
		tempTroll->getPostTree()->remove(&postOld);
		tempTroll->getPostTree()->add(&newPost);

		delete postByIdOld;
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}


StatusType DataStruct::GetTopPost(int TrollID, int *PostID){
	assert(TrollID != 0);
	try {
		if (TrollID < 0) {	//for getting Posts from all Trolls
			Post* post = getMaxPost();//get max Post from main tree
			if(post == NULL)//in case no Post exist
			{
				*PostID=-1;
				return SUCCESS;
			}
			*PostID = post->getId();
			delete post;
			return SUCCESS;
		} else {	//for getting Posts from Troll
			assert(TrollID > 0);

			Troll* tempTroll = findTroll(TrollID);
			if(tempTroll == NULL){
				return FAILURE;
			}
			Post* post = tempTroll->getMaxPost();//get max Post from Troll
			if(post == NULL)//in case no Post exist in Troll
			{
				*PostID=-1;
				return SUCCESS;
			}
			*PostID = post->getId();
			delete post;
			return SUCCESS;
		}
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
	assert(false);
	return SUCCESS;
}

StatusType DataStruct::GetAllPostsByLikes(int TrollID, int **Posts,
		int *numOfPost) {
	tree<Post>* tree = NULL;
	if (TrollID > 0) {	//for getting Posts from specific Troll
		Troll* TrollTemp = findTroll(TrollID);
		if(TrollTemp==NULL){
			return FAILURE;
		}
		tree = TrollTemp->getPostTree();	//save pointer to Troll's tree
	} else {	//for getting Posts from all Trolls
		assert(TrollID < 0);
		tree = PostTree;	//save pointer to main tree
	}
	if (tree->getSize() == 0) {//in case there are no Post in tree
		*numOfPost = 0;
		*Posts = NULL;
		return SUCCESS;
	}
	int tempNum = 0;
	Post** pokArray = NULL;
	try {
		//get array of pointers to Posts in tree
		pokArray = tree->getAllDataInReverseOrder(&tempNum);
		//allocate array of Post id to return
		int* tempPtr = (int*) malloc(sizeof(int) * (tempNum));
		if (tempPtr == NULL) {
			return ALLOCATION_ERROR;
		}
		//fill array of Post id from array of Posts
		for (int i = 0; i < tempNum; i++) {
			tempPtr[i] = pokArray[i]->getId();
		}
		*numOfPost = tempNum;
		*Posts = tempPtr;
		delete[] pokArray;
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}

StatusType DataStruct::EvolvePost(int PostID, int evolvedID) {

	PostById temppostById = PostById(PostID);
	PostById tempEvolvepostById = PostById(evolvedID);

	//check if Post exist with old id and there is no Post with new id
	if (!PostTreeById->isIn(&temppostById) || PostTreeById->isIn(&tempEvolvepostById)) {
		return FAILURE;
	}
	StatusType stat;
	try {
		//get data of Post with the old id
		PostById* temppostOldTreeById = PostTreeById->getData(&temppostById);
		int Likes = temppostOldTreeById->getLikes();
		int myTrollId = temppostOldTreeById->GetMyTroll();
		delete temppostOldTreeById;

		//find Troll with the Post
		Troll* tempTroll = findTroll(myTrollId);
		assert(tempTroll!=NULL);

		//remove the Post from two main trees and Troll tree
		PostById postOldTreeById(PostID,Likes,myTrollId);
		Post postOldTree(PostID,Likes,myTrollId);
		stat = PostTree->remove(&postOldTree);
		assert(stat==SUCCESS);
		stat = PostTreeById->remove(&postOldTreeById);
		assert(stat==SUCCESS);
		stat = tempTroll->getPostTree()->remove(&postOldTree);
		assert(stat==SUCCESS);

		//add the Post with new id to the two main trees and Troll tree
		Post newPost(evolvedID, Likes, myTrollId);
		PostById newPostById(evolvedID, Likes, myTrollId);
		stat = PostTree->add(&newPost);
		assert(stat==SUCCESS);
		stat = PostTreeById->add(&newPostById);
		assert(stat==SUCCESS);
		stat = tempTroll->getPostTree()->add(&newPost);
		assert(stat==SUCCESS);

	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

void DataStruct::deleteTrolls() {
//delete Trolls:
	Troll* tempTroll = this->firstTroll;
	if (tempTroll == NULL) {
		return;
	}
	Troll* next = tempTroll->getNextTroll();
	if (tempTroll) {
		delete tempTroll;
	}
	while (next) {
		tempTroll = next;
		next = next->getNextTroll();
		delete tempTroll;
	}
}

StatusType DataStruct::UpdateLikes(int stoneCode, int stoneFactor) {
	int size;

	//
	Post** array = PostTree->getAllDataInReverseOrder(&size);
	UpdateReorderPosts(array, size, stoneCode, stoneFactor);
	delete[] array;

	PostById** arrayById = PostTreeById->getAllDataInReverseOrder(&size);
	UpdateLikesPostsById(arrayById, size, stoneCode, stoneFactor);
	delete[] arrayById;

	Troll* tempTroll = firstTroll;
	while (tempTroll) {
		array = tempTroll->getPostTree()->getAllDataInReverseOrder(&size);
		UpdateReorderPosts(array, size, stoneCode, stoneFactor);
		delete[] array;
		tempTroll = tempTroll->getNextTroll();
	}
	return SUCCESS;
}


tree<Post>* DataStruct::getTree() {
	return PostTree;
}

void DataStruct::printTrolls() {
	Troll* tempTroll = this->firstTroll;
	Post** pokArray = NULL;
	while (tempTroll) {
		int tempNum = 0;


		pokArray = tempTroll->getPostTree()->getAllDataInReverseOrder(
				&tempNum);
		if(tempNum == 0){
			tempTroll = tempTroll->getNextTroll();
			continue;
		}
		int* tempPtr = (int*) malloc(sizeof(int) * (tempNum));
		for (int i = 0; i < tempNum; i++) {
			tempPtr[i] = pokArray[i]->getId();
		}
		cout << "[Troll id: " << tempTroll->getId() << "] Posts Id's:[";
		for (int i = 0; i < tempNum; i++) {
			cout << tempPtr[i] << ", ";
		}
		cout << "]" << endl;
		free(tempPtr);
		delete[] pokArray;

		tempTroll = tempTroll->getNextTroll();
	}
}

Troll* DataStruct::findTroll(int TrollId){
	Troll* temp = firstTroll;
	while(temp!=NULL){
		if( temp->getId() == TrollId ){
			return temp;
		}
		temp = temp->getNextTroll();
	}
	return NULL;
}
