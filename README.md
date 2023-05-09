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

Just copy paste this code in your terminal at the root of the project (Pac-Man folder)

Alternatively, you can use `cmake --build ./ -j8` to enable cmake to use 8 cores for parallel compilation (change 8 to whatever the number of cores you want to use).

# How to launch
Go to the build folder and execute PacMan with the command ./PacMan.

# Details & intended limits

The maximum displayable score is 1,000,000.

# How to play

To move pacman use directional arrows.
To start press any directional arrow.

# How to quit
Just press escape.

