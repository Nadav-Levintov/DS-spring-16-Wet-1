/*
 * DataStruct.h
 *
 *  Created on: 2 בדצמ 2015
 *      Author: Nir Diamant
 */

#ifndef DATASTRUCT_H_
#define DATASTRUCT_H_

#include "trainer.h"

class DataStruct {
private:
	trainer* firstTrainer;
	tree<pokemon>* PokemonTree;
	tree<pokemonById>* PokemonTreeById;
public:

	DataStruct() :
			firstTrainer(NULL){
		PokemonTree = new tree<pokemon>();
		PokemonTreeById = new tree<pokemonById>();
	}
	~DataStruct() {
		deleteTrainers();
		delete PokemonTree;
		delete PokemonTreeById;
	}

	pokemon* getMaxPokemon();

	StatusType addTrainer(int id);

	StatusType CatchPokemon(int pokemonID, int trainerID, int level);

	StatusType FreePokemon(int pokemonID);

	StatusType LevelUp(int pokemonID, int levelIncrease);

//	pokemon* GetTopPokemon(int trainerID, int *pokemonID);

	StatusType GetTopPokemon(int trainerID, int *pokemonID);

	StatusType EvolvePokemon(int pokemonID, int evolvedID);

	StatusType GetAllPokemonsByLevel(int trainerID, int **pokemons,
			int *numOfPokemon);

	void printTrainers();

	void deleteTrainers();

	StatusType UpdateLevels(int stoneCode, int stoneFactor);

	tree<pokemon>* getTree();

	trainer* findTrainer(int trainerId);
};

#endif /* DATASTRUCT_H_ */
