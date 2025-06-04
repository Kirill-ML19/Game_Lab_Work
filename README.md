# Dungeon Adventure

A console game in the genre of dungeon crawler with RPG elements. Explore dungeons, fight monsters and find powerful artifacts!

## Game Features

- **Turn-based battles** with different types of enemies
- **Inventory system** with equipment and consumables
- **Character progression** - increasing levels and stats
- **Dungeon generation** with unique rooms and enemies
- **Potion system** - healing, temporary buffs
- **Saving and loading** game progress

## Management

| Key | Action |
|---------|----------|
| W       | Moving up |
| A       | Move to the left |
| S       | Moving Down |
| D       | Move to the right |
| I       | Open inventory |
| E       | Equipment menu |
| U       | Use item |
| C       | Show characteristics |
| Q       | Quit the game |

## System Requirements

- **OS**: Linux, Windows (via WSL), macOS
- **Compiler**: GCC 9+ / Clang 10+
- **Libraries**: C++17 Standard Library

## Installation and launch

```bash
1. Clone the repository:
git clone https://github.com/Kirill-ML19/Game_Lab_Work
cd Game_Lab_Work


2. Build the project:

mkdir -p build
cd build/
cmake .. 


3. Starting the game:
 
cmake --build . --target run_game 


4. Running tests:
cmake --build . --target run_tests
```