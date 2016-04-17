/*
 * troll.h
 *
 *  Created on: 1 בדצמ 2015
 *      Author: Nir Diamant
 */

#ifndef TROLL_H_
#define TROLL_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Btree.h"
#include "post.h"

class Troll {
private:
	const int id;
	Troll* nextTroll;
	tree<Post>* PostTree;

public:
	Troll(const int id, Troll* nextTroll, Post* maxPost = NULL,
			int numOfPosts = 0, tree<Post>* PostTree = NULL) :
			id(id), nextTroll(nextTroll), PostTree(PostTree) {
	}
	Troll(int id) : id(id), nextTroll(NULL){
		PostTree=new tree<Post>();
	}
	~Troll() {
		delete PostTree;
	}

	Post* getMaxPost();
	Troll* getNextTroll();
	tree<Post>* getPostTree() {
		return PostTree;
	}
	void setNextTroll(Troll* newTroll);
	int getId() {
		return id;
	}

	StatusType addPost(Post* p);
};

#endif /* TROLL_H_ */
