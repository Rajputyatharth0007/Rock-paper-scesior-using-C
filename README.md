# Rock Paper Scissors in C

A clean, robust, and interactive console-based implementation of the classic **Rock, Paper, Scissors** game written in C (C11 standard). The player competes against the computer across a configurable number of rounds with automated score tracking and input validation.

---

## Table of Contents

- [Overview](#overview)
- [Objective](#objective)
- [Features](#features)
- [Technologies & Requirements](#technologies--requirements)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Running the Game](#running-the-game)
- [Sample Gameplay](#sample-gameplay)
- [Game Logic & Rules](#game-logic--rules)
- [Error Handling & Input Validation](#error-handling--input-validation)
- [Possible Future Improvements](#possible-future-improvements)

---

## Overview

This project provides a beginner-friendly yet robust terminal game implementing the classic Rock-Paper-Scissors rules. It was designed to demonstrate clean C programming fundamentals, including structured modular design, safe user input processing, random move generation, and clear game-state evaluation.

---

## Objective

The objective of the game is to score more round victories than the computer within a user-defined series of rounds. In each round, the player and the computer simultaneously select one of three moves:
- **Rock** (defeats Scissors, loses to Paper)
- **Paper** (defeats Rock, loses to Scissors)
- **Scissors** (defeats Paper, loses to Rock)

---

## Features

- **Custom Round Length**: Allows the player to choose any positive number of rounds to play.
- **Randomized Computer Opponent**: Uses pseudo-random number generation seeded with the system clock (`time(NULL)`) for unpredictable computer choices.
- **Robust Input Validation**:
  - Handles non-numeric inputs without crashing or entering infinite loops.
  - Validates move range (strictly accepts `0`, `1`, or `2`).
  - Gracefully handles end-of-file (EOF) and stream interrupts.
- **Comprehensive Score Tracking**: Keeps track of player wins, computer wins, and tied rounds across the entire match.
- **Accurate Outcome Determination**: Evaluates every valid move combination accurately and properly identifies ties, player wins, and computer wins.
- **Clean Match Summary**: Displays a detailed breakdown of total wins, ties, and the overall match winner with score differential.

---

## Technologies & Requirements

- **Language**: C (C11 standard compliant)
- **Compiler**: GCC (MinGW / MinGW-w64 on Windows, or standard GCC on Linux/macOS)
- **Standard Libraries**: `<stdio.h>`, `<stdlib.h>`, `<time.h>`
- **OS**: Cross-platform (Windows, Linux, macOS)

---

## Project Structure

```text
Rock-paper-scesior-using-C/
├── rockpaperseccisor.c   # Main C source file containing game logic
├── .gitignore            # Git ignore file for binaries and temp files
└── README.md             # Comprehensive project documentation
```

---

## Compilation

To compile the project with strict warnings and C11 standards using GCC on Windows:

```cmd
gcc -std=c11 -Wall -Wextra -Wpedantic rockpaperseccisor.c -o rockpaperseccisor.exe
```

### Linux / macOS

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic rockpaperseccisor.c -o rockpaperseccisor
```

---

## Running the Game

### Windows

```cmd
.\rockpaperseccisor.exe
```

### Linux / macOS

```bash
./rockpaperseccisor
```

---

## Sample Gameplay

```text
-----! HELLO PLAYER !-----
------ Welcome to Game Rock(0), Paper(1), Scissors(2) -----
Enter the number of rounds: 3

---- Round 1 of 3 start -----
Enter your choice - Rock(0), Paper(1), Scissors(2): 0
Player choice: Rock
Computer Choice is Scissors
Match is win by Player

---- Round 2 of 3 start -----
Enter your choice - Rock(0), Paper(1), Scissors(2): 1
Player choice: Paper
Computer Choice is Paper
Match is tied

---- Round 3 of 3 start -----
Enter your choice - Rock(0), Paper(1), Scissors(2): 2
Player choice: Scissors
Computer Choice is Rock
Match is win by Computer

----- GAME OVER -----
------ Total number of wins by player: 1 ------
------ Total number of wins by computer: 1 ------
------ Total number of tied rounds: 1 ------
======= Overall match is a Tie! =======
```

---

## Game Logic & Rules

Move definitions:
- `0` = Rock
- `1` = Paper
- `2` = Scissors

The outcome evaluation matrix:

| Player Move | Computer Move | Round Outcome |
| :--- | :--- | :--- |
| **Rock (0)** | Rock (0) | Draw |
| **Rock (0)** | Paper (1) | Computer Wins |
| **Rock (0)** | Scissors (2) | **Player Wins** |
| **Paper (1)** | Rock (0) | **Player Wins** |
| **Paper (1)** | Paper (1) | Draw |
| **Paper (1)** | Scissors (2) | Computer Wins |
| **Scissors (2)** | Rock (0) | Computer Wins |
| **Scissors (2)** | Paper (1) | **Player Wins** |
| **Scissors (2)** | Scissors (2) | Draw |

---

## Error Handling & Input Validation

1. **Non-Numeric Characters**: If the user types letters or symbols (e.g. `abc`), `scanf` fails. The program detects the failure, flushes the input buffer using `clear_input_buffer()`, displays an informative error message, and prompts the user again without corrupting the game state.
2. **Out-of-Range Selections**: Inputs outside `{0, 1, 2}` are rejected, prompting the player to re-enter their move for the current round.
3. **Invalid Round Count**: Entering non-positive integers (zero or negative) prompts for re-entry.
4. **Stream Interruption**: If `EOF` is detected (such as via piped input or stream termination), the game exits safely without undefined behavior.

---

## Possible Future Improvements

These enhancements can be explored in future versions:
- Add a choice to play against different AI difficulty levels (e.g., Markov chain move prediction).
- Add persistent high-score tracking using a local file.
- Provide a continuous replay option ("Play again? [y/n]") without restarting the executable.
- Support string inputs (`rock`, `paper`, `scissors`) in addition to numeric inputs (`0`, `1`, `2`).
