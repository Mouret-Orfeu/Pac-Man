
#include "Tile.h"

Tile::Tile(int i, int j) : i(i), j(j) {}
Tile::Tile() : i(0), j(0) {}

bool Tile::operator==(const Tile& other) const {
        return (i == other.i && j == other.j);
}