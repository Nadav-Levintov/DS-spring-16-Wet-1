/*
 * library1.cpp
 *
 *  Created on: 2 בדצמ 2015
 *      Author: Nir Diamant
 */
#include "DataStruct.h"
#include"library1.h"
#include <exception>

void* Init() {
	try {
		DataStruct* ds = new DataStruct();
		return ds;
	} catch (std::bad_alloc& e) {
		return NULL;
	}
}

StatusType AddTroll(void *DS, int trollID) {
	if (!DS || trollID <= 0) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->addTroll(trollID);
}

StatusType PublishPost(void *DS, int PostID, int TrollID, int Likes) {
	if (!DS || PostID <= 0 || TrollID <= 0 || Likes < 0) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->PublishPost(PostID, TrollID, Likes);

}

StatusType DeletePost(void *DS, int PostID) {
	if (PostID <= 0 || DS == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->DeletePost(PostID);
}

StatusType FeedTroll(void *DS, int PostID, int LikesIncrease) {
	if (LikesIncrease <= 0 || PostID <= 0 || DS == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->FeedTroll(PostID, LikesIncrease);
}

StatusType GetTopPost(void *DS, int TrollID, int *PostID) {
	if (TrollID == 0 || PostID == NULL || DS == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->GetTopPost(TrollID,PostID);
}

StatusType GetAllPostsByLikes(void *DS, int TrollID, int **Posts, int *numOfPost){
	if(TrollID == 0 || Posts == NULL || DS == NULL || numOfPost == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->GetAllPostsByLikes(TrollID,Posts,numOfPost);
}

void Quit(void **DS)
{
	if(DS == NULL) return;
	if((*DS)==NULL) return;
	DataStruct* ourStruct = (DataStruct*) *DS;
	delete ourStruct;
	*DS = NULL;
}

StatusType UpdateLikes(void *DS, int stoneCode, int stoneFactor){
	if(stoneFactor <1 || stoneCode <1 || DS==NULL)
	{
		return INVALID_INPUT;
	}
	try{
		DataStruct* ourStruct = (DataStruct*) DS;
		return ourStruct->UpdateLikes(stoneCode,stoneFactor);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}
