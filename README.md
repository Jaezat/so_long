# So_long
so_long is a small 2D game project designed to work with the MiniLibX library. The goal is to create a simple top-down game where a player collects items and reaches an exit while navigating a map and avoiding obstacles.

## Usage
After compiling the project with make, run the program by passing a map file (with the .ber extension) as an argument:

./so_long maps/level1.ber

The game will open a window and display the map. Use the following controls to play:
* W or Up Arrow: Move Up
* A or Left Arrow: Move Left
* S or Down Arrow: Move Down
* D or Right Arrow: Move Right
* ESC: Close the game

## Available Operations
Key Feature Description
**Map Parsing** Reads .ber files and validates the rectangular shape and components
**MLX Window** Initializes the graphical window and handles the main loop
**Sprite Rendering** Loads .xpm images and draws them onto the screen grid
**Event Hooking** Captures keyboard inputs and window close events
**Movement Logic** Updates player coordinates and checks for wall collisions
**Move Counter** Displays the current number of steps in the terminal or window

## Implementation Choice
This project was implemented using a tile-based coordinate system and the MiniLibX library. The decision to use this approach was based on several factors:

* **Event-Driven Programming:** Using hooks allows the program to remain idle until a key is pressed, saving CPU resources.
* **XPM Management:** Loading textures into image pointers ensures fast rendering without re-reading files during every frame.
* **Strict Validation:** The implementation uses a flood-fill algorithm to ensure the map is playable before the game even starts.
* **Memory Safety:** Every MLX pointer and map tile is tracked to ensure a clean exit with no memory leaks.
* **Grid-Based Logic:** Using a 2D array for the map makes collision detection and collectible tracking straightforward.



## How It Works
The so_long implementation follows these steps:
1. **Map Validation**: Checks if the map is surrounded by walls, is rectangular, and contains 1P, 1E, and at least 1C.
2. **Path Verification**: Uses a flood-fill algorithm to confirm the player can actually reach the exit and all items.
3. **MLX Setup**: Initializes the connection to the graphical system and creates a new window.
4. **Texture Loading**: Converts .xpm files into image buffers for the wall, floor, player, collectible, and exit.
5. **Game Loop**: Listens for key presses, updates the player position, and redraws the map accordingly.
6. **Clean Exit**: Destroys all images and the window properly when the player wins or closes the game.

## Key Learnings
* Working with the MiniLibX graphical library.
* Implementing window management and event handling.
* Using flood-fill algorithms for pathfinding validation.
* Managing graphical assets and XPM files in C.
* Ensuring robust error handling for external file inputs.
* Handling real-time user events: Learning to manage asynchronous inputs where the program must respond immediately to player actions.
* Event-driven programming: Shifting from linear code to a system that "waits" for user triggers (keypresses, mouse clicks).
