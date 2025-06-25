# Solitaire Game - C++ Implementation

## Overview
This is a simple Solitaire game implementation in C++. The game is based on the standard rules of Solitaire (Klondike). It uses a deck of 52 playing cards and involves moving cards between columns, stock, waste piles, and foundations to achieve the objective of building up all four foundations from Ace to King in each suit.

## Features
- **Card Movement**: Move cards between columns, stock, waste piles, and foundations.
- **Undo Feature**: Undo the last move made.
- **Shuffle and Deal**: The deck is shuffled at the start, and cards are dealt into the tableau.
- **Display**: The current state of the game is displayed after every move, showing the stock, waste, foundations, and tableau.

## Classes and Structure
### Card
- Represents a single card with a suit (Hearts, Diamonds, Clubs, Spades) and a value (Ace, 2-9, 10, Jack, Queen, King).
- Supports flipping the card, displaying the card, and checking for its rank and color.

### List
- A custom doubly linked list implementation for managing the tableau columns.
- Supports basic list operations like inserting, removing, and iterating through elements.

### Stack
- A stack implementation that uses the `List` class.
- Supports basic stack operations like pushing and popping cards.

### Command
- A command structure that stores the details of a move, such as source column, destination column, number of cards, and move direction.
- Supports executing and reversing moves.

### Game
- The main class managing the game state.
- Handles deck initialization, shuffling, dealing, and the rules for moving cards between different piles (tableau, stock, waste, and foundations).
- Includes logic for checking if the game has been won and for displaying the game state.

## How to Play
1. **Game Start**: The game starts with a shuffled deck and the cards are dealt into 7 tableau columns.
2. **Making Moves**: You can move cards between tableau columns, the stock, waste pile, and foundations.
   - You can move cards from tableau to tableau by following the alternating color and descending rank rule.
   - Cards can be moved from the waste pile to a tableau or foundation if the move follows the rules.
3. **Undo**: You can undo your last move at any time by entering `-1` when prompted.
4. **Winning the Game**: The game is won when all cards are placed in the foundations, from Ace to King in each suit.

## Compilation and Execution
1. **Compile the Game**: You can compile the game using a C++ compiler.
   ```bash
   g++ -o solitaire solitaire.cpp
