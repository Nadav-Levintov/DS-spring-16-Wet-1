/*
 * library1.cpp
 *
 *  Created on: 2 בדצמ 2015
 *      Author: Nir Diamant
 */
#include "DataStruct.h"
#include"library1.h"
void* Init() {
	try {
		DataStruct* ds = new DataStruct();
		return ds;
	} catch (std::bad_alloc& e) {
		return NULL;
	}
}

StatusType AddTrainer(void *DS, int trainerID) {
	if (!DS || trainerID <= 0) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->addTrainer(trainerID);
}

StatusType CatchPokemon(void *DS, int pokemonID, int trainerID, int level) {
	if (!DS || pokemonID <= 0 || trainerID <= 0 || level <= 0) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->CatchPokemon(pokemonID, trainerID, level);

}

StatusType FreePokemon(void *DS, int pokemonID) {
	if (pokemonID <= 0 || DS == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->FreePokemon(pokemonID);
}

StatusType LevelUp(void *DS, int pokemonID, int levelIncrease) {
	if (levelIncrease <= 0 || pokemonID <= 0 || DS == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->LevelUp(pokemonID, levelIncrease);
}

StatusType GetTopPokemon(void *DS, int trainerID, int *pokemonID) {
	if (trainerID == 0 || pokemonID == NULL || DS == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->GetTopPokemon(trainerID,pokemonID);
}

StatusType GetAllPokemonsByLevel(void *DS, int trainerID, int **pokemons, int *numOfPokemon){
	if(trainerID == 0 || pokemons == NULL || DS == NULL || numOfPokemon == NULL) {
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->GetAllPokemonsByLevel(trainerID,pokemons,numOfPokemon);
}

StatusType EvolvePokemon(void *DS, int pokemonID, int evolvedID)
{
	if(evolvedID <=0 || pokemonID <=0 || DS==NULL)
	{
		return INVALID_INPUT;
	}
	DataStruct* ourStruct = (DataStruct*) DS;
	return ourStruct->EvolvePokemon(pokemonID, evolvedID);
}
void Quit(void **DS)
{
	if(DS == NULL) return;
	if((*DS)==NULL) return;
	DataStruct* ourStruct = (DataStruct*) *DS;
	delete ourStruct;
	*DS = NULL;
}

StatusType UpdateLevels(void *DS, int stoneCode, int stoneFactor){
	if(stoneFactor <1 || stoneCode <1 || DS==NULL)
	{
		return INVALID_INPUT;
	}
	try{
		DataStruct* ourStruct = (DataStruct*) DS;
		return ourStruct->UpdateLevels(stoneCode,stoneFactor);
	} catch (std::bad_alloc& e) {
		return ALLOCATION_ERROR;
	}
}
