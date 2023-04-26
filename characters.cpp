#include "characters.h"
#include "controller.h"

Main_character::~Main_character()
{
    ;
}

Character::~Character()
{
    ;
}

void Main_character::move()
{
    switch (direction)
    {
        case controller::left:
            position.x--;
            break;
        case controller::right:
            position.x++;
            break;
        case controller::up:
            position.y--;
            break;
        case controller::down:
            position.y++;
            break;
        case controller::none:
            break;
    }
} 