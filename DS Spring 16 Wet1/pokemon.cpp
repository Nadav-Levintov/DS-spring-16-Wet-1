/*
 * pokemon.cpp
 *
 *  Created on: 2 ???? 2015
 *      Author: user
 */

#include "pokemon.h"

int pokemon::compare(pokemon* p2){
	assert(p2 != NULL);
	if(id == p2->id){
		return 0;
	} else if(level == p2->level) {
		return p2->id - id;
	} else {
		return level - p2->level;
	}
}


void pokemon::print() {
	if(this){
		cout << "level: " << level << ", id: " << id;
	}
}


void UpdateReorderPokemons(pokemon** list,int size,int stoneCode, int stoneFactor){

	//allocate temporary arrays
	pokemon** changed = new pokemon*[size];
	pokemon** remained = new pokemon*[size];
	pokemon** organized = new pokemon*[size];
	for(int i = 0 ; i<size ; i++ ){
		changed[i] = new pokemon();
		remained[i] = new pokemon();
		organized[i] = new pokemon();
	}

	//fill temporary arrays
	int n1 = 0;
	int k1 = 0;
	for(int i=0; i<size ; i++){
		if( (list[i]->id)%stoneCode == 0){
//			pokemon* temp = changed[n1];
			changed[n1]->id = list[i]->id;
			changed[n1]->level = (list[i]->level) * stoneFactor;
			changed[n1]->myTrainer = (list[i]->myTrainer);
			n1++;
		} else {
//			pokemon* temp = remained[k1];
			remained[k1]->id = list[i]->id;
			remained[k1]->level = (list[i]->level);
			remained[k1]->myTrainer = (list[i]->myTrainer);
			k1++;
		}
	}

	//merge temporary arrays
	int n2 = 0;
	int k2 = 0;
	for(int i = 0 ; i<size ; i++ ){
		if(changed[n2]->compare(remained[k2])>0){
//			pokemon* temp = changed[n2];
//			pokemon* temp2 = remained[k2];
			organized[i]->id = changed[n2]->id;
			organized[i]->level = (changed[n2]->level);
			organized[i]->myTrainer = (changed[n2]->myTrainer);
			n2++;
		} else {
//			pokemon* temp = changed[n2];
//			pokemon* temp2 = remained[k2];
			organized[i]->id = remained[k2]->id;
			organized[i]->level = (remained[k2]->level);
			organized[i]->myTrainer = (remained[k2]->myTrainer);
			k2++;
		}
	}
	assert(n2==n1);
	assert(k1==k2);

	//update original list
	for(int i = 0 ; i<size ; i++ ){
		list[i]->id = organized[i]->id;
		list[i]->level = (organized[i]->level);
		list[i]->myTrainer = (organized[i]->myTrainer);
	}


	//free allocation
	for(int i = 0 ; i<size ; i++ ){
		delete changed[i];
		delete remained[i];
		delete organized[i];
	}
	delete[] changed;
	delete[] remained;
	delete[] organized;
}

void UpdateLevelPokemonsById(pokemonById** list,int size,int stoneCode, int stoneFactor){
	for(int i = 0 ; i<size ; i++ ){
		if(list[i]->getId() % stoneCode == 0){
			list[i]->setLevel( list[i]->getLevel() * stoneFactor );
		}
	}
}

int pokemonById::compare(pokemonById* p2){
	assert(p2 != NULL);
	return getId() - p2->getId();
}
