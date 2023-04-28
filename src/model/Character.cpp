#include "Character.h"
#include "view/GameView.h"

Character::Character(State state)
: state(state)
{}

Character::~Character() {}

Character::State Character::getState() const {
    return state;
}

void Character::setState(const State& state) {
    this->state = state;
}

Character::Direction Character::getDirection() const {
    return state.direction;
}

void Character::setDirection(Direction direction) {
    state.direction = direction;
}

SDL_Point Character::getCenterPosition() const {
    return state.center_position;
}

void Character::setCenterPosition(int x, int y) {
    state.center_position.x = x;
    state.center_position.y = y;
    state.tile_position.x = state.center_position.x/8;
    state.tile_position.y = state.center_position.y/8;
}

SDL_Point Character::computeTilePosition(SDL_Point center_position) {
    return {center_position.x/8, center_position.y/8};
}

SDL_Point Character::getTilePosition() const {
    return state.tile_position;
}

void Character::setTilePosition(int x, int y) {
    state.tile_position.x = x;
    state.tile_position.y = y;
    // TODO: update center_position
}

void Character::updatePosition () {
    switch (state.direction) {
        case Direction::UP:
            state.center_position.y -= 1;
            break;
        case Direction::DOWN:
            state.center_position.y += 1;
            break;
        case Direction::LEFT:
            state.center_position.x -= 1;
            break;
        case Direction::RIGHT:
            state.center_position.x += 1;
            break;
        default:
            break;
    }

    state.tile_position.x = state.center_position.x/8;
    state.tile_position.y = state.center_position.y/8;
}

SDL_Point Character::getCoordCenterTile(SDL_Point tile_pos) {
    return {tile_pos.x*8+4, tile_pos.y*8+4};
}

bool Character::isTileLegal (const SDL_Point& tile) const
{
    if(GameViewConstants::TILES[tile.x][tile.y]!=-1)
        return true;
    else
        return false;
}

SDL_Point Character::getNextTile(const SDL_Point& curent_tile, const Direction& direction) const
{
    SDL_Point next_tile = curent_tile;
    switch (direction) {
        case Direction::UP:
            next_tile.y -= 1;
            break;
        case Direction::DOWN:
            next_tile.y += 1;
            break;
        case Direction::LEFT:
            next_tile.x -= 1;
            break;
        case Direction::RIGHT:
            next_tile.x += 1;
            break;
        default:
            break;
    }
    return next_tile;
}

bool Character::isCenteredOnTile() const {
    return state.center_position.x%8==0 && state.center_position.y%8==0;
}
