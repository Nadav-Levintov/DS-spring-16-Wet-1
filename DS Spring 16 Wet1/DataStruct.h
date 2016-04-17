/*
 * DataStruct.h
 *
 *  Created on: 2 בדצמ 2015
 *      Author: Nir Diamant
 */

#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#include "Troll.h"

class DataStruct {
private:
	Troll* firstTroll;
	tree<Post>* PostTree;
	tree<PostById>* PostTreeById;
public:

	DataStruct() :
			firstTroll(NULL){
		PostTree = new tree<Post>();
		PostTreeById = new tree<PostById>();
	}
	~DataStruct() {
		deleteTrolls();
		delete PostTree;
		delete PostTreeById;
	}

	Post* getMaxPost();

	StatusType addTroll(int id);

	StatusType PublishPost(int PostID, int TrollID, int Likes);

	StatusType DeletePost(int PostID);

	StatusType FeedTroll(int PostID, int LikesIncrease);

	StatusType GetTopPost(int TrollID, int *PostID);

	StatusType EvolvePost(int PostID, int evolvedID);

	StatusType GetAllPostsByLikes(int TrollID, int **Posts,
			int *numOfPost);

	void printTrolls();

	void deleteTrolls();

	StatusType UpdateLikes(int stoneCode, int stoneFactor);

	tree<Post>* getTree();

	Troll* findTroll(int TrollId);
};

#endif /* DATASTRUCT_H_ */
