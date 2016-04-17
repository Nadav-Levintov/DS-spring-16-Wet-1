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
	pokemon(int id = -1, int likes = -1, int myTroll=-1) :
			id(id), likes(likes), myTroll(myTroll) {
	}
	pokemon(pokemon* p) :
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
	friend void UpdateReorderPokemons(pokemon** list,int size,int stoneCode, int stoneFactor);

	int compare(pokemon* p2);
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

class pokemonById: public pokemon{
public:
	pokemonById(int id = -1, int likes = -1, int myTroll=-1) :
			pokemon(id,likes,myTroll){
	}
	pokemonById(pokemonById* p) :
		pokemon(p->getId(),p->getlikes(),p->GetmyTroll()) {
	}

	int compare(pokemonById* p2);

	friend void UpdatelikesPokemonsById(pokemonById** list,int size,int stoneCode, int stoneFactor);
};

#endif /* POST_H_ */
