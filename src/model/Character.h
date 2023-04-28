#pragma once

#include "GameObject.h"

#include <SDL.h>

class Character : public GameObject {
public:
    enum class Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        NONE
    };

    struct State {
        Direction direction;
        SDL_Point center_position;
        SDL_Point tile_position;
    };

    Character(State state);
    virtual ~Character();

    /**
    * @brief Traite la logique de déplacement des personnages et met à jour leur position
    *
    * @param count est un compteur qui sert pour l'instant à boucler le mouvement du fantome
    */
    virtual void move(const int count) = 0;

    /**
    * @brief Sous fonction de move, ne sert qu'à changer top_left_position et center_position en fonction de la direction calculée dans move
    *
    *
    */
    void updatePosition ();

    bool isTileLegal (const SDL_Point& tile) const;

    bool isCenteredOnTile() const;

    SDL_Point getNextTile(const SDL_Point& curent_tile, const Direction& direction) const;

    State getState() const;
    void setState(const State& state);

    Direction getDirection() const;
    void setDirection(Direction direction);

    SDL_Point getTopLeftPosition() const;
    void setTopLeftPosition(int x, int y);

    SDL_Point getPosition() const;
    void setCenterPosition(int x, int y);

    SDL_Point computeTilePosition(SDL_Point center_position);

    SDL_Point getTilePosition() const;
    void setTilePosition(int x, int y);

    SDL_Point getTilePositionFromCenter() const;
    void setTilePositionFromCenter(int x, int y);

    SDL_Point getCoordCenterTile(SDL_Point tile_pos);


protected:
    State state;
};
