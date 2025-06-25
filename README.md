# 🎴 Terminal Solitaire (C++)

![C++](https://img.shields.io/badge/C++-00599C?style=flat&logo=c%2B%2B&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-blue)
![License](https://img.shields.io/badge/License-MIT-green)

> A classic Klondike Solitaire game with keyboard-based controls, implemented in C++ for terminal environments.

## 📥 Installation

### Requirements
- C++17 compatible compiler (GCC, Clang, or MSVC)
- Terminal with ANSI escape code support (for colors)

### Build Instructions
```bash
# Clone repository
git clone https://github.com/yourusername/terminal-solitaire.git
cd terminal-solitaire

# Compile
g++ -std=c++17 -o solitaire main.cpp Card.cpp Game.cpp -O2

# Run
./solitaire   # Linux/macOS
.\solitaire.exe # Windows
# MAIN MENU
[1] New Game
[2] Resume Game
[3] How to Play
[4] Quit
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
