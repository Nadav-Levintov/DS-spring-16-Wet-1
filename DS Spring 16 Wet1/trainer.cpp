/*
 * trainer.cpp
 *
 *  Created on: 1 áãöî 2015
 *      Author: Nir Diamant
 */
#include "trainer.h"

pokemon* trainer::getMaxPokemon() {
	return PokemonTree->getBiggestData();
}
trainer* trainer::getNextTrainer() {
	return nextTrainer;
}
void trainer::setNextTrainer(trainer* newTrainer) {
	nextTrainer = newTrainer;
}
StatusType trainer::addPokemon(pokemon* p) {
	return PokemonTree->add(p);
}

