#include "Ghost.h"


Ghost::Ghost(SDL_Point init_pos_center_ghost)
:Character({CharacterDirection::RIGHT, init_pos_center_ghost})
{
    // Initialize Ghost-specific data here
}

Ghost::~Ghost() {
    // Clean up Ghost-specific data here
}

void Ghost::move(int count) {
    // Update the direction based on the count value
    switch (count / 128) {
        case 0:
            state.direction = CharacterDirection::RIGHT;
            state.top_left_position.x++;
            break;
        case 1:
            state.direction = CharacterDirection::DOWN;
            state.top_left_position.y++;
            break;
        case 2:
            state.direction = CharacterDirection::LEFT;
            state.top_left_position.x--;
            break;
        case 3:
            state.direction = CharacterDirection::UP;
            state.top_left_position.y--;
            break;
    }
}
