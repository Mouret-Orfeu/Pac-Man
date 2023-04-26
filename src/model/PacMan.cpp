#include "PacMan.h"
#include "Character.h"

PacMan::PacMan(CharacterState state)
:Character(state)
{
    // Initialize PacMan-specific data here
}

PacMan::~PacMan() {
    // Clean up PacMan-specific data here
}

// Implement PacMan-specific methods here
void PacMan::updatePosition(int count) {
    // Update the position based on the count value
    (void)count;
}
