/*
 * post.h
 *
 *  Created on: 1 בדצמ 2015
 *      Author: Nir Diamant
 */

#ifndef POST_H_
#define POST_H_
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Btree.h"
#include "treeNode.h"

class Post {
private:
	int id;
	int likes;
	int myTroll;
public:
	Post(int id = -1, int likes = -1, int myTroll=-1) :
			id(id), likes(likes), myTroll(myTroll) {
	}
	Post(Post* p) :
			id(p->id), likes(p->likes), myTroll(p->myTroll) {
	}
	int getlikes()
	{
		return likes;
	}
	int getId()
		{
			return id;
		}
	friend void UpdateReorderPosts(Post** list,int size,int stoneCode, int stoneFactor);

	int compare(Post* p2);
	void print();
	void setTrainer(int myTroll)
	{
		this->myTroll=myTroll;
	}
	void setlikes(int myTroll)
		{
			this->likes=myTroll;
		}
	void setId(int myTroll)
		{
			this->id=myTroll;
		}
	int GetmyTroll()
	{
		return myTroll;
	}

};

class PostById: public Post{
public:
	PostById(int id = -1, int likes = -1, int myTroll=-1) :
			Post(id,likes,myTroll){
	}
	PostById(PostById* p) :
		Post(p->getId(),p->getlikes(),p->GetmyTroll()) {
	}

	int compare(PostById* p2);

	friend void UpdatelikesPostsById(PostById** list,int size,int stoneCode, int stoneFactor);
};

#endif /* POST_H_ */
