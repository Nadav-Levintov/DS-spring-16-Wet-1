/*
 * DataStruct.cpp
 *
 *  Created on: 4 ???? 2015
 *      Author: user
 */

#include "DataStruct.h"
#include "trainer.h"
#include "pokemon.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

pokemon* DataStruct::getMaxPokemon() {
	return PokemonTree->getBiggestData();
}

StatusType DataStruct::addTrainer(int id) {
	try {
		trainer* newTrainer = new trainer(id);
		if (!(this->firstTrainer)) {
			this->firstTrainer = newTrainer;
			return SUCCESS;
		} else {
			trainer* tempTrainer = firstTrainer;
			while (tempTrainer) {
				if (tempTrainer->getId() == id) {
					delete newTrainer;
					return FAILURE;
				}
				tempTrainer = tempTrainer->getNextTrainer();

			}
			tempTrainer = firstTrainer;
			while (tempTrainer->getNextTrainer()) {
				tempTrainer = tempTrainer->getNextTrainer();
			}
			tempTrainer->setNextTrainer(newTrainer);
			return SUCCESS;
		}
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

}

StatusType DataStruct::CatchPokemon(int pokemonID, int trainerID, int level) {
	StatusType stat;
	pokemonById newPokemonById(pokemonID, level, trainerID);
	pokemon newPokemon(pokemonID, level, trainerID);

	//check if pokemon exist in PokemonTreeById tree
	if (PokemonTreeById->isIn(&newPokemonById)) {
		return FAILURE;
	}
	//check if trainer exist
	trainer* trainerTemp = findTrainer(trainerID);
	if(trainerTemp==NULL){
		return FAILURE;
	}
	//add new pokemon to two main trees and trainer's tree
	try {
		stat = PokemonTree->add(&newPokemon);
		assert(stat == SUCCESS);
		stat = PokemonTreeById->add(&newPokemonById);
		assert(stat == SUCCESS);
		stat = trainerTemp->addPokemon(&newPokemon);
		assert(stat == SUCCESS);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

StatusType DataStruct::FreePokemon(int pokemonID) {

	pokemonById pokeById = pokemonById(pokemonID);

	//check if pokemon exists in PokemonTreeById tree
	if (!PokemonTreeById->isIn(&pokeById)) {
		return FAILURE;
	}

	//create pokemons for finding them in trees
	pokemonById* pokeByIdOld = PokemonTreeById->getData(&pokeById);
	pokemon poke = pokemon(pokemonID, pokeByIdOld->getLevel());

	//free pokemon from two main trees
	PokemonTree->remove(&poke);
	PokemonTreeById->remove(&pokeById);

	//free pokemon from it's trainer's tree
	trainer* tempTrainer = findTrainer(pokeByIdOld->GetMyTrainer());
	assert( tempTrainer != NULL );
	tempTrainer->getPokemonTree()->remove(&poke);

	delete pokeByIdOld;	//release pokemon returned for knowing its level

	return SUCCESS;
}

StatusType DataStruct::LevelUp(int pokemonID, int levelIncrease) {

	pokemonById PokeOnlyId = pokemonById(pokemonID);

	//check if pokemon exists in PokemonTreeById tree
	if (!PokemonTreeById->isIn(&PokeOnlyId)) {
		return FAILURE;
	}

	try {
		//create pokemons for remove and re-adding them with new level
		pokemonById* pokeByIdOld = PokemonTreeById->getData(&PokeOnlyId);
		pokemon pokeOld = pokemon(pokemonID, pokeByIdOld->getLevel(),pokeByIdOld->GetMyTrainer());
		pokemonById newPokeById(pokemonID, pokeByIdOld->getLevel() + levelIncrease,pokeByIdOld->GetMyTrainer());
		pokemon newPokemon(pokemonID, pokeOld.getLevel() + levelIncrease, pokeOld.GetMyTrainer());

		//remove pokemon with old level and add with new level to trees
		PokemonTreeById->remove(pokeByIdOld);
		PokemonTreeById->add(&newPokeById);
		PokemonTree->remove(&pokeOld);
		PokemonTree->add(&newPokemon);

		//remove pokemon with old level and add with new level to trainer's tree
		trainer* tempTrainer = findTrainer(pokeByIdOld->GetMyTrainer());
		assert( tempTrainer != NULL );
		tempTrainer->getPokemonTree()->remove(&pokeOld);
		tempTrainer->getPokemonTree()->add(&newPokemon);

		delete pokeByIdOld;
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}


StatusType DataStruct::GetTopPokemon(int trainerID, int *pokemonID){
	assert(trainerID != 0);
	try {
		if (trainerID < 0) {	//for getting pokemons from all trainers
			pokemon* poke = getMaxPokemon();//get max pokemon from main tree
			if(poke == NULL)//in case no pokemon exist
			{
				*pokemonID=-1;
				return SUCCESS;
			}
			*pokemonID = poke->getId();
			delete poke;
			return SUCCESS;
		} else {	//for getting pokemons from trainer
			assert(trainerID > 0);

			trainer* tempTrainer = findTrainer(trainerID);
			if(tempTrainer == NULL){
				return FAILURE;
			}
			pokemon* poke = tempTrainer->getMaxPokemon();//get max pokemon from trainer
			if(poke == NULL)//in case no pokemon exist in trainer
			{
				*pokemonID=-1;
				return SUCCESS;
			}
			*pokemonID = poke->getId();
			delete poke;
			return SUCCESS;
		}
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
	assert(false);
	return SUCCESS;
}

StatusType DataStruct::GetAllPokemonsByLevel(int trainerID, int **pokemons,
		int *numOfPokemon) {
	tree<pokemon>* tree = NULL;
	if (trainerID > 0) {	//for getting pokemons from specific trainer
		trainer* trainerTemp = findTrainer(trainerID);
		if(trainerTemp==NULL){
			return FAILURE;
		}
		tree = trainerTemp->getPokemonTree();	//save pointer to trainer's tree
	} else {	//for getting pokemons from all trainers
		assert(trainerID < 0);
		tree = PokemonTree;	//save pointer to main tree
	}
	if (tree->getSize() == 0) {//in case there are no pokemon in tree
		*numOfPokemon = 0;
		*pokemons = NULL;
		return SUCCESS;
	}
	int tempNum = 0;
	pokemon** pokArray = NULL;
	try {
		//get array of pointers to pokemons in tree
		pokArray = tree->getAllDataInReverseOrder(&tempNum);
		//allocate array of pokemon id to return
		int* tempPtr = (int*) malloc(sizeof(int) * (tempNum));
		if (tempPtr == NULL) {
			return ALLOCATION_ERROR;
		}
		//fill array of pokemon id from array of pokemons
		for (int i = 0; i < tempNum; i++) {
			tempPtr[i] = pokArray[i]->getId();
		}
		*numOfPokemon = tempNum;
		*pokemons = tempPtr;
		delete[] pokArray;
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}

	return SUCCESS;
}

StatusType DataStruct::EvolvePokemon(int pokemonID, int evolvedID) {

	pokemonById tempPokeById = pokemonById(pokemonID);
	pokemonById tempEvolvePokeById = pokemonById(evolvedID);

	//check if pokemon exist with old id and there is no pokemon with new id
	if (!PokemonTreeById->isIn(&tempPokeById) || PokemonTreeById->isIn(&tempEvolvePokeById)) {
		return FAILURE;
	}
	StatusType stat;
	try {
		//get data of pokemon with the old id
		pokemonById* tempPokeOldTreeById = PokemonTreeById->getData(&tempPokeById);
		int level = tempPokeOldTreeById->getLevel();
		int myTrainerId = tempPokeOldTreeById->GetMyTrainer();
		delete tempPokeOldTreeById;

		//find trainer with the pokemon
		trainer* tempTrainer = findTrainer(myTrainerId);
		assert(tempTrainer!=NULL);

		//remove the pokemon from two main trees and trainer tree
		pokemonById pokeOldTreeById(pokemonID,level,myTrainerId);
		pokemon pokeOldTree(pokemonID,level,myTrainerId);
		stat = PokemonTree->remove(&pokeOldTree);
		assert(stat==SUCCESS);
		stat = PokemonTreeById->remove(&pokeOldTreeById);
		assert(stat==SUCCESS);
		stat = tempTrainer->getPokemonTree()->remove(&pokeOldTree);
		assert(stat==SUCCESS);

		//add the pokemon with new id to the two main trees and trainer tree
		pokemon newPokemon(evolvedID, level, myTrainerId);
		pokemonById newPokemonById(evolvedID, level, myTrainerId);
		stat = PokemonTree->add(&newPokemon);
		assert(stat==SUCCESS);
		stat = PokemonTreeById->add(&newPokemonById);
		assert(stat==SUCCESS);
		stat = tempTrainer->getPokemonTree()->add(&newPokemon);
		assert(stat==SUCCESS);

	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
	return SUCCESS;
}

void DataStruct::deleteTrainers() {
//delete Trainers:
	trainer* tempTrainer = this->firstTrainer;
	if (tempTrainer == NULL) {
		return;
	}
	trainer* next = tempTrainer->getNextTrainer();
	if (tempTrainer) {
		delete tempTrainer;
	}
	while (next) {
		tempTrainer = next;
		next = next->getNextTrainer();
		delete tempTrainer;
	}
}

StatusType DataStruct::UpdateLevels(int stoneCode, int stoneFactor) {
	int size;

	//
	pokemon** array = PokemonTree->getAllDataInReverseOrder(&size);
	UpdateReorderPokemons(array, size, stoneCode, stoneFactor);
	delete[] array;

	pokemonById** arrayById = PokemonTreeById->getAllDataInReverseOrder(&size);
	UpdateLevelPokemonsById(arrayById, size, stoneCode, stoneFactor);
	delete[] arrayById;

	trainer* tempTrainer = firstTrainer;
	while (tempTrainer) {
		array = tempTrainer->getPokemonTree()->getAllDataInReverseOrder(&size);
		UpdateReorderPokemons(array, size, stoneCode, stoneFactor);
		delete[] array;
		tempTrainer = tempTrainer->getNextTrainer();
	}
	return SUCCESS;
}


tree<pokemon>* DataStruct::getTree() {
	return PokemonTree;
}

void DataStruct::printTrainers() {
	trainer* tempTrainer = this->firstTrainer;
	pokemon** pokArray = NULL;
	while (tempTrainer) {
		int tempNum = 0;


		pokArray = tempTrainer->getPokemonTree()->getAllDataInReverseOrder(
				&tempNum);
		if(tempNum == 0){
			tempTrainer = tempTrainer->getNextTrainer();
			continue;
		}
		int* tempPtr = (int*) malloc(sizeof(int) * (tempNum));
		for (int i = 0; i < tempNum; i++) {
			tempPtr[i] = pokArray[i]->getId();
		}
		cout << "[Trainer id: " << tempTrainer->getId() << "] pokemons Id's:[";
		for (int i = 0; i < tempNum; i++) {
			cout << tempPtr[i] << ", ";
		}
		cout << "]" << endl;
		free(tempPtr);
		delete[] pokArray;

		tempTrainer = tempTrainer->getNextTrainer();
	}
}

trainer* DataStruct::findTrainer(int trainerId){
	trainer* temp = firstTrainer;
	while(temp!=NULL){
		if( temp->getId() == trainerId ){
			return temp;
		}
		temp = temp->getNextTrainer();
	}
	return NULL;
}
