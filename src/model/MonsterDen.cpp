#include "MonsterDen.h"
#include "GameModel.h"

#include <vector>
#include <iostream>

MonsterDen::MonsterDen(GameModel& gameModel):gameModel(gameModel){}
MonsterDen::~MonsterDen(){}

void MonsterDen::setGhostsInDen()
{
    for(std::unique_ptr<Ghost>& ghost : gameModel.getGhosts()){
        if(!ghost->isOutOfDen()){
            ghosts_in_den.push_back(ghost->getType());
        }
    }
    
}

void MonsterDen::updateMonsterDen(){

}