#pragma once

class Tile {
public:
    int i;
    int j;

    Tile(int i, int j);
    Tile();

    bool operator==(const Tile& other) const;

};