#ifndef CHARACTERS
#define CHARACTERS

#include <vector>
#include "SDL.h"
#include "controller.h"

using namespace std;

typedef enum character_name_t
{
    Pacman,
    Blinky,
    Inky,
    Pinky,
    Clyde,
}character_name_t;

//I want class named character

class Character
{
    protected:

        SDL_Point position;
        const character_name_t name;
        controller::direction_t direction;

    public:

        Character(SDL_Point position, const character_name_t name, controller::direction_t direction):position(position), name(name), direction(direction){};
        ~Character();

        //pure virtual function moove
        virtual void move() =0;

        //getters
        SDL_Point get_position() const {return position;};
        character_name_t get_name() const {return name;};
        controller::direction_t get_direction() const {return direction;};

        //setters
        void set_position(SDL_Point position) {this->position = position;};
        void set_direction(controller::direction_t direction) {this->direction = direction;};
        
};

class Ghost: public Character
{
    private:

    public:

        Ghost(SDL_Point position, const character_name_t name, controller::direction_t direction):Character(position, name, direction){};
        ~Ghost();
        
        void move();
        
};

class Red_Ghost: public Character
{
    private:

    public:

        Red_Ghost(SDL_Point position, const character_name_t name=Blinky, controller::direction_t direction=controller::none): Character(position, name, direction){};
        ~Red_Ghost();
        
        void move();
        
};

class Main_character: public Character
{
    private:

    public:

        Main_character(SDL_Point position, const character_name_t name=Pacman, controller::direction_t direction=controller::none): Character(position, name, direction){};
        ~Main_character();
        
        void move();
        
};



#endif