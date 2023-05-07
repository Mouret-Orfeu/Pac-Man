#include "MonsterDen.h"
#include "GameModel.h"
#include "Ghost.h"

#include <vector>
#include <iostream>
#include <unordered_map>
#include <algorithm>

MonsterDen::MonsterDen(GameModel& game_model):game_model(game_model),
count_eaten_dots_Pinky(0),
count_eaten_dots_Inky(0),
count_eaten_dots_Clyde(0),
dot_limit_pinky(0),
dot_limit_inky(30),
dot_limit_clyde(60),
can_leave_den_Blinky(true),
can_leave_den_Pinky(false),
can_leave_den_Inky(false),
can_leave_den_Clyde(false)
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


void MonsterDen::setGhostsInDen()
{
    //DEBUG
    //std::cout << "set ghost in den: " <<std::endl;

    ghosts_in_den.clear(); // Clear the vector before filling it up with new values
    
    for(std::unique_ptr<Ghost>& ghost : game_model.getGhosts()){

        //DEBUG
        //ghost->printType(ghost->getType());
        //std::cout<<ghost->isOutOfDen() <<std::endl;

        //si out_of_den du fantome est false, et si son type n'est pas deja dans ghost_in_den, le rajouter
        if(!ghost->isOutOfDen()){
            if(std::find(ghosts_in_den.begin(), ghosts_in_den.end(), ghost->getType()) == ghosts_in_den.end()){
                ghosts_in_den.push_back(ghost->getType());

                //DEBUG
                //ghost->printType(ghost->getType());

                
            }
        }
        
    }
    //DEBUG
    //std::cout <<std::endl;

    std::sort(ghosts_in_den.begin(), ghosts_in_den.end(), compareGhostType);
    
}

void MonsterDen::updateMonsterDen(){

    MonsterDen::setGhostsInDen();

    //DEBUG
    //std::cout << "size ghost in den : " << ghosts_in_den.size() <<std::endl;
    //std::cout << "type ghost : " <<std::endl;
    //game_model.getGhosts()[(int)Ghost::Type::INKY]->printType(game_model.getGhosts()[(int)Ghost::Type::INKY]->getType());
    //Ghost::Type type= ghosts_in_den[0];
    //game_model.getGhosts()[(int)Ghost::Type::INKY]->printType(type);


    //set can_leave_den to true if the ghost in the den has eaten enough dots
    if(ghosts_in_den.size()>0){
        switch (ghosts_in_den[0])
        {
        case Ghost::Type::PINKY:
            if(count_eaten_dots_Pinky>=dot_limit_pinky){
                can_leave_den_Pinky=true;
            }
            break;
        case Ghost::Type::INKY:
            if(count_eaten_dots_Inky>=dot_limit_inky){
                can_leave_den_Inky=true;
            }
            break;
        case Ghost::Type::CLYDE:
            //DEBUG
            //std::cout << "count_eaten_dots_Clyde : " << count_eaten_dots_Clyde << std::endl;
            if(count_eaten_dots_Clyde>=dot_limit_clyde){
                can_leave_den_Clyde=true;
            }
            break;
        default:
            std::cout << "Error updateMonsterDen(), no ghost in den" << std::endl;
            break;
        }
    }

    
    


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

void MonsterDen::printCounterDot(Ghost::Type ghost_type) const
{
    switch (ghost_type)
    {
    case Ghost::Type::PINKY:
        std::cout << "Pinky: " << count_eaten_dots_Pinky << std::endl;
        break;
    case Ghost::Type::INKY:
        std::cout << "Inky: " << count_eaten_dots_Inky << std::endl;
        break;
    case Ghost::Type::CLYDE:
        std::cout << "Clyde: " << count_eaten_dots_Clyde << std::endl;
        break;
    default:
        std::cout << "Error printCounterDot(), no ghost in den" << std::endl;
        break;
    }
}

bool MonsterDen::getCanLeaveDen(Ghost::Type ghost_type) const
{
    switch (ghost_type)
    {
    case Ghost::Type::PINKY:
        return can_leave_den_Pinky;
        break;
    case Ghost::Type::INKY:
        //DEBUG
        //std::cout << "can leave den inky : " << can_leave_den_Inky << std::endl;
        return can_leave_den_Inky;
        break;
    case Ghost::Type::CLYDE:
        return can_leave_den_Clyde;
        break;
    case Ghost::Type::BLINKY:
        return true;
        break;
    default:
        std::cout << "Error getCanLeaveDenGhost(), wrong ghost type" << std::endl;
        exit(1);
        break;
    }
}




