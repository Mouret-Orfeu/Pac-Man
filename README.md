# Pac-Man

A project by Orfeú Mouret and Maxime Drouhin

## Compilation

### Requirements for compilation

- SDL2 (`sudo apt-get install libsdl2-dev`)

### How to compile

We use CMake to configure and build the project.
To compile this projet, you might use the following:

```bash
mkdir build
cd build
cmake -S ../ -B ./
cmake --build ./
```

Alternatively, you can use `cmake --build ./ -j8` to enable cmake to use 8 cores for parallel compilation (change 8 to whatever the number of cores you want to use).

# Details & intended limits

Le nombre de points maximum prévu est 1 000 000

## Bug report
parfois pacman se fige apres avoir perdu une vie
parfois on ne frize quand on mange un fantome

# How to play

To move pacman use directional arrows.
To start press any directional arrow.

# How to quit
Just press escape.

