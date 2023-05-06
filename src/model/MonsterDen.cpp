#include "MonsterDen.h"
#include "GameModel.h"
#include "Ghost.h"

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

MonsterDen::MonsterDen(GameModel& game_model):game_model(game_model),
dot_limit_blinky(0),
dot_limit_pinky(0),
dot_limit_inky(30),
dot_limit_clyde(60)
{}
MonsterDen::~MonsterDen(){}


bool compareGhostType( Ghost::Type t1, Ghost::Type t2){
    // Define the priority order of directions
    std::unordered_map<Ghost::Type, int> priorityMap = {
        {Ghost::Type::PINKY, 3},
        {Ghost::Type::INKY, 2},
        {Ghost::Type::CLYDE, 1}
    };
    
    // Compare the priority of the directions
    return priorityMap[t1] > priorityMap[t2];
}

void MonsterDen::updateMonsterDen(){

    MonsterDen::setGhostsInDen();

    //set can_leave_den to true if the ghost in the den has eaten enough dots
    if(ghosts_in_den.size()>0){
        switch (ghosts_in_den[0])
        {
        case Ghost::Type::PINKY:
            if(count_eaten_dots_Pinky>=dot_limit_pinky){
                game_model.getGhosts()[(int)Ghost::Type::PINKY]->setCanLeaveDen(true);
            }
            break;
        case Ghost::Type::INKY:
            if(count_eaten_dots_Inky>=dot_limit_inky){
                game_model.getGhosts()[(int)Ghost::Type::INKY]->setCanLeaveDen(true);
            }
            break;
        case Ghost::Type::CLYDE:
            if(count_eaten_dots_Clyde>=dot_limit_clyde){
                game_model.getGhosts()[(int)Ghost::Type::CLYDE]->setCanLeaveDen(true);
            }
            break;
        default:
            std::cout << "Error updateMonsterDen(), no ghost in den" << std::endl;
            break;
        }
    }

    
    


}

void MonsterDen::setGhostsInDen()
{
    for(std::unique_ptr<Ghost>& ghost : game_model.getGhosts()){
        if(!ghost->isOutOfDen()){
            ghosts_in_den.push_back(ghost->getType());
        }
    }

    std::sort(ghosts_in_den.begin(), ghosts_in_den.end(), compareGhostType);
    
}

std::vector<Ghost::Type> MonsterDen::getGhostsInDen() const
{
    return ghosts_in_den;
}

void MonsterDen::incrementDotCounter()
{
    switch (ghosts_in_den[0])
    {
    case Ghost::Type::PINKY:
        count_eaten_dots_Pinky++;
        break;
    case Ghost::Type::INKY:
        count_eaten_dots_Inky++;
        break;
    case Ghost::Type::CLYDE:
        count_eaten_dots_Clyde++;
        break;
    default:
        std::cout << "Error incrementDotCounter(), no ghost in den" << std::endl;
        break;
    }
    
    
}

