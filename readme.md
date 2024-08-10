


#   Ping Pong Game - C++ 

A multiplayer and bot Ping Pong game developed using C++ and the Raylib library.

## Features

- Single-player mode against a CPU opponent
- Realistic ball physics and collision detection
- Player and CPU scoring system
- Smooth gameplay with intuitive controls

## Controls

- Move Paddle Up: `W` 'Upkey'
- Move Paddle Down: `S` 'DownKey'

## Installation

1. Ensure you have Raylib installed. Follow the instructions at [Raylib Installation Guide](https://github.com/raysan5/raylib#installation).
2. Clone the repository or download the source code.

```bash
git clone https://github.com/rabin20-04/III---Ping-Pong.git
```

3. Compile the game using your preferred C++ compiler.

```bash
g++ -o ping_pong pingpong_main.cpp -lraylib
```

4. Run the game.

```bash
./ping_pong
```

## Code Structure

- `ball` class: Manages the ball's movement, drawing, and collision logic.
- `paddle` class: Manages the player and CPU paddle movements and drawing.
- `cpu` class: Inherits from `paddle` and controls the CPU paddle behavior.

