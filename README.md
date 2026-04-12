*This project has been created as part of the 42 curriculum by cacesar- and clados-s.*

# Cub3D

## Description
Cub3D is a graphical project developed in C that implements a 3D perspective within a 2D map using the **Raycasting** technique. Inspired by the legendary 1992 game *Wolfenstein 3D*, this project explores the fundamentals of computer graphics, window management, and mathematical projections.

The program reads a configuration file (with a `.cub` extension) containing map data and texture paths, then renders a navigable environment where the user can move through a maze-like structure.

## Features
- **3D Rendering**: Real-time rendering using raycasting logic.
- **Texture Support**: Different textures for North, South, East, and West walls.
- **Environment Colors**: Custom colors for the floor and ceiling.
- **Movement**: Smooth player movement (forward, backward, strafing) and rotation.
- **Map Validation**: Robust parsing to ensure the map is closed, contains a valid player start, and uses proper identifiers.
- **Minimap**: A real-time 2D overlay showing the player's position and orientation.

## Instructions

### Prerequisites
The project requires the following libraries:
- `X11`
- `Xext`
- `m` (math library)

On Debian-based systems, you can install them via:
```bash
sudo apt-get install libx11-dev libxext-dev
```

### Compilation
To compile the project, use the provided `Makefile`:
```bash
make
```
This will compile the `libft`, `minilibx`, and finally the `cub3D` executable.

### Execution
Run the program by passing a valid map file as an argument:
```bash
./cub3D srcs/maps/default.cub
```
```bash
./cub3D srcs/maps/arena.cub
```

### Controls
- **W / S**: Move forward / backward.
- **A / D**: Strafe left / right.
- **Left / Right Arrows**: Rotate the camera.
- **ESC / Window Close Button**: Exit the application safely.

## Resources
- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html): Fundamental guide for the raycasting algorithm.
- [Wolfenstein 3D Engine Architecture](http://fabiensanglard.net/wolf3d/): Historical and technical deep dive.
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx.html): Reference for the 42 graphical library.

### AI Usage
AI was utilized during the project for the following tasks:
- **Documentation**: Structuring and generating the `README.md` file according to curriculum requirements.
- **Research**: Clarifying mathematical concepts related to vector rotation and DDA (Digital Differential Analyzer) algorithms.
- **Code Optimization**: Identifying opportunities for refactoring and ensuring adherence to the 42 Norminette standards.
- **Debugging**: Assisting in the identification of edge cases in map parsing and memory management.
