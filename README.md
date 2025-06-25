🎴 Terminal Solitaire (C++)
https://img.shields.io/badge/C++-00599C?logo=c%252B%252B&logoColor=white
https://img.shields.io/badge/Platform-Windows%2520%257C%2520Linux%2520%257C%2520macOS-blue

A classic Klondike Solitaire game with keyboard-based controls, implemented in C++ for terminal environments.

📥 Installation
Windows
bash
git clone https://github.com/yourusername/terminal-solitaire.git
cd terminal-solitaire
g++ -o solitaire solitaire.cpp
.\solitaire.exe
Linux/macOS
bash
git clone https://github.com/yourusername/terminal-solitaire.git
cd terminal-solitaire
g++ -o solitaire solitaire.cpp
./solitaire
🕹️ Game Controls
Main Menu
text
[1] New Game
[2] Resume Game
[3] How to Play
[4] Quit
Use number keys to navigate

Game Controls
text
WASD/Arrow Keys  : Move cursor
Enter/Space      : Select card
F                : Move to Foundation
T                : Move to Tableau
D                : Draw from Stock
U                : Undo move
M                : Return to Menu
H                : Hint
🎮 How to Play
Objective: Move all cards to foundation piles (top-right) sorted by suit from Ace to King

Tableau: Build down in alternating colors

Foundations: Build up by same suit

Stock: Click 'D' to draw new cards

🖥️ Code Structure
cpp
solitaire.cpp
├── main()
│   ├── initGame()
│   ├── displayMenu()
│   ├── gameLoop()
│   │   ├── handleInput()
│   │   ├── validateMove()
│   │   ├── checkWinCondition()
│   │   └── renderGame()
├── Card class
│   ├── Suit (enum)
│   ├── Rank (enum)
│   ├── isFaceUp
│   └── toString()
└── GameState struct
    ├── tableau[7][19]
    ├── foundation[4][13]
    ├── stock[24]
    └── waste[24]
📊 Game Preview
text
=====================================
  SOLITAIRE   Moves: 42   Hints: 3
=====================================

Stock: [XX]  Waste: [K♦]

Foundations:
[  ] [  ] [  ] [  ]

Tableau:
1: [A♠] 
2: [XX] [7♥] 
3: [XX] [XX] [Q♣] 
4: [XX] [XX] [XX] [2♦] 
5: [XX] [XX] [XX] [XX] [10♠] 
6: [XX] [XX] [XX] [XX] [XX] [3♣] 
7: [XX] [XX] [XX] [XX] [XX] [XX] [J♦] 

Controls: [WASD] Move  [SPACE] Select  [F] Foundation  [M] Menu
🛠️ Dependencies
C++17 or newer

Standard Library Only (No external dependencies)

✅ Features
Complete Klondike Solitaire rules

Undo/Redo functionality

Hint system

Save/Load game state

Color-coded card display (for supported terminals)

Win detection with animation

Adaptive difficulty levels

🚀 Future Improvements
Add scoring system

Implement different solitaire variants

Add terminal theming support

Create animated card movements

Add timed game mode

📝 License
MIT License
