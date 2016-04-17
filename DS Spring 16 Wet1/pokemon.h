/*
 * pokemon.h
 *
 *  Created on: 1 בדצמ 2015
 *      Author: Nir Diamant
 */

#ifndef POKEMON_H_
#define POKEMON_H_
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "Btree.h"
#include "treeNode.h"

class pokemon {
private:
	int id;
	int level;
	int myTrainer;
public:
	pokemon(int id = -1, int level = -1, int myTrainer=-1) :
			id(id), level(level), myTrainer(myTrainer) {
	}
	pokemon(pokemon* p) :
			id(p->id), level(p->level), myTrainer(p->myTrainer) {
	}
	int getLevel()
	{
		return level;
	}
	int getId()
		{
			return id;
		}
	friend void UpdateReorderPokemons(pokemon** list,int size,int stoneCode, int stoneFactor);

	int compare(pokemon* p2);
	void print();
	void setTrainer(int myTrainer)
	{
		this->myTrainer=myTrainer;
	}
	void setLevel(int myTrainer)
		{
			this->level=myTrainer;
		}
	void setId(int myTrainer)
		{
			this->id=myTrainer;
		}
	int GetMyTrainer()
	{
		return myTrainer;
	}

};

class pokemonById: public pokemon{
public:
	pokemonById(int id = -1, int level = -1, int myTrainer=-1) :
			pokemon(id,level,myTrainer){
	}
	pokemonById(pokemonById* p) :
		pokemon(p->getId(),p->getLevel(),p->GetMyTrainer()) {
	}

	int compare(pokemonById* p2);

	friend void UpdateLevelPokemonsById(pokemonById** list,int size,int stoneCode, int stoneFactor);
};

#endif /* POKEMON_H_ */
