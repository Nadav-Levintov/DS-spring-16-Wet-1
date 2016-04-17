/*
 * Post.cpp
 *
 *  Created on: 2 ???? 2015
 *      Author: user
 */

#include "Post.h"

int Post::compare(Post* p2){
	assert(p2 != NULL);
	if(id == p2->id){
		return 0;
	} else if(likes == p2->likes) {
		return p2->id - id;
	} else {
		return likes - p2->likes;
	}
}


void Post::print() {
	if(this){
		cout << "likes: " << likes << ", id: " << id;
	}
}


void UpdateReorderPosts(Post** list,int size,int postsCode, int postsFactor){

	//allocate temporary arrays
	Post** changed = new Post*[size];
	Post** remained = new Post*[size];
	Post** organized = new Post*[size];
	for(int i = 0 ; i<size ; i++ ){
		changed[i] = new Post();
		remained[i] = new Post();
		organized[i] = new Post();
	}

	//fill temporary arrays
	int n1 = 0;
	int k1 = 0;
	for(int i=0; i<size ; i++){
		if( (list[i]->id)%postsCode == 0){
//			Post* temp = changed[n1];
			changed[n1]->id = list[i]->id;
			changed[n1]->likes = (list[i]->likes) * postsFactor;
			changed[n1]->myTroll = (list[i]->myTroll);
			n1++;
		} else {
//			Post* temp = remained[k1];
			remained[k1]->id = list[i]->id;
			remained[k1]->likes = (list[i]->likes);
			remained[k1]->myTroll = (list[i]->myTroll);
			k1++;
		}
	}

	//merge temporary arrays
	int n2 = 0;
	int k2 = 0;
	for(int i = 0 ; i<size ; i++ ){
		if(changed[n2]->compare(remained[k2])>0){
//			Post* temp = changed[n2];
//			Post* temp2 = remained[k2];
			organized[i]->id = changed[n2]->id;
			organized[i]->likes = (changed[n2]->likes);
			organized[i]->myTroll = (changed[n2]->myTroll);
			n2++;
		} else {
//			Post* temp = changed[n2];
//			Post* temp2 = remained[k2];
			organized[i]->id = remained[k2]->id;
			organized[i]->likes = (remained[k2]->likes);
			organized[i]->myTroll = (remained[k2]->myTroll);
			k2++;
		}
	}
	assert(n2==n1);
	assert(k1==k2);

	//update original list
	for(int i = 0 ; i<size ; i++ ){
		list[i]->id = organized[i]->id;
		list[i]->likes = (organized[i]->likes);
		list[i]->myTroll = (organized[i]->myTroll);
	}


	//free allocation
	for(int i = 0 ; i<size ; i++ ){
		delete changed[i];
		delete remained[i];
		delete organized[i];
	}
	delete[] changed;
	delete[] remained;
	delete[] organized;
}

void UpdateLikesPostsById(PostById** list,int size,int postsCode, int postsFactor){
	for(int i = 0 ; i<size ; i++ ){
		if(list[i]->getId() % postsCode == 0){
			list[i]->setLikes( list[i]->getLikes() * postsFactor );
		}
	}
}

int PostById::compare(PostById* p2){
	assert(p2 != NULL);
	return getId() - p2->getId();
}
