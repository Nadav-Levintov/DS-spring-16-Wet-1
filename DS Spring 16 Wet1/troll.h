/*
 * troll.h
 *
 *  Created on: 1 ���� 2015
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

class trainer {
private:
	const int id;
	trainer* nextTrainer;
	tree<pokemon>* PokemonTree;

public:
	trainer(const int id, trainer* nextTrainer, pokemon* maxPokemon = NULL,
			int numOfPokemons = 0, tree<pokemon>* pokemonTree = NULL) :
			id(id), nextTrainer(nextTrainer), PokemonTree(pokemonTree) {
	}
	trainer(int id) : id(id), nextTrainer(NULL){
		PokemonTree=new tree<pokemon>();
	}
	~trainer() {
		delete PokemonTree;
	}

	pokemon* getMaxPokemon();
	trainer* getNextTrainer();
	tree<pokemon>* getPokemonTree() {
		return PokemonTree;
	}
	void setNextTrainer(trainer* newTrainer);
	int getId() {
		return id;
	}

	StatusType addPokemon(pokemon* p);
};

#endif /* TROLL_H_ */