# Flappy Ship — A Space-Themed Flappy Bird Clone

A simple game made with C++ and SFML, inspired by Flappy Bird. You control a small spaceship and try to fly it through gaps between pipes without crashing.

This project is a great way to learn how a basic game is structured in C++ — things like game loops, states, and simple physics.

## What This Game Does

- Shows a start menu
- Lets you fly a spaceship by pressing a key
- Spawns pipes that move toward you
- Ends the game if you hit a pipe, the ground, or the ceiling
- Lets you restart without closing the game
- Plays background music

## What You Need to Run It

- A C++ compiler (like `g++`)
- SFML library installed on your computer

You do **not** need to download anything extra for images, fonts, or music — all of that is already included in the `assets/` folder in this repo.

## How to Run the Game

Open a terminal in the project folder and run this command to build it:

```bash
g++ main.cpp -o flappy -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
```

This creates a program called `flappy`. Run it like this:

```bash
./flappy
```

## Controls

`SPACE` => Start the game / Flap the ship / Restart after game over 

`ESC`  => Quit the game                                       

## Project Files

    main.cpp                # Where the program starts running
    In scripts/
        -Game.hpp              # Runs the whole game (menu, gameplay, game over)
        -Bird.hpp                # Controls the spaceship (movement, gravity, flapping)
        -PipeHandler.hpp         # Creates and manages all the pipes
        -Pipe.hpp                 # A single pipe obstacle

There's also an `assets/` folder with all the images, the font, and the music used in the game.

## How the Game Works 

Think of the game as running in a loop, over and over, many times per second. Each time through the loop, three things happen:

1. **Check for input** — Did the player press Space or Escape?
2. **Update everything** — Move the ship, move the pipes, check if anything crashed into anything else.
3. **Draw everything** — Show the background, the ship, the pipes, and any text on screen.

The game keeps track of what "state" it's in — either the **Menu**, **Playing**, or **Game Over** — and behaves differently depending on which state it's in. For example, pressing Space does something different in the menu than it does while playing.

### The Spaceship (`Bird.hpp`)

The ship is always falling because of gravity. Pressing Space gives it a quick boost upward (a "flap"). The ship also tilts up or down a bit depending on whether it's rising or falling, just to look nicer.

### The Pipes (`Pipe.hpp` and `PipeHandler.hpp`)

Each pipe has a top part and a bottom part, with a gap in between. `PipeHandler` is in charge of creating new pipes and moving all of them across the screen. It also checks whether the ship has crashed into any pipe.

### The Main Game Class (`Game.hpp`)

This is the "control center" of the game. It creates the window, loads the images/fonts/music, and runs the main loop described above.

### Where to Start Reading the Code

If you're new to this, a good order to read the files in is:

1. `main.cpp` — just a few lines, shows how the game starts
2. `Game.hpp` — the big picture of how everything connects
3. `Bird.hpp` — simple physics, good for understanding movement
4. `Pipe.hpp` — simple shapes and collision
5. `PipeHandler.hpp` — how multiple pipes are managed together

## A Note for this Repository

This code runs and mostly works, but it has a few small intentional issues hidden in it on purpose — as part of a fun debugging challenge. Try playing the game and check out the issues page. Do try to look up how actual flappy bird game's mechanics work and try to fix this game with those mechanics in mind. At the end of the day its all about learning.