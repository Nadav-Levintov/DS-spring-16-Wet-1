/*
 * Troll.cpp
 *
 *  Created on: 1 áãöî 2015
 *      Author: Nir Diamant
 */
#include "troll.h"

Post* Troll::getMaxPost() {
	return PostTree->getBiggestData();
}
Troll* Troll::getNextTroll() {
	return nextTroll;
}
void Troll::setNextTroll(Troll* newTroll) {
	nextTroll = newTroll;
}
StatusType Troll::addPost(Post* p) {
	return PostTree->add(p);
}

