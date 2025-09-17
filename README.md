# CHESS
A chess engine built in **C++** using the **SDL library**, featuring a graphical interface.  
This project is the direct evolution of my earlier project **C Chess**, which was a terminal-only chess engine written in **C**.

![C++](https://img.shields.io/badge/language-C++-blue.svg)  
![SDL2](https://img.shields.io/badge/library-SDL2-green.svg)  
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)  
![Contributions Open](https://img.shields.io/badge/contributions-OPEN-brightgreen.svg)  


---

## Table of Contents
1. [Features](#-features)  
2. [Project Structure](#-project-structure)  
3. [Usage](#-usage)  
4. [Motivation](#-motivation)  
5. [Getting Started](#-getting-started)  
6. [Contributing](#-contributing)  
7. [License](#-license)  


---

## Features
- **Board Class** implementation in C++ with:
  - Legal move generation & move execution  
  - Match import/export (save & load games)  
  - AI methods that return movements  

- **Graphical Interface** using SDL with:
  - Main menu with settings & options  
  - Single-player mode against AI  
  - Multiplayer (local) mode  
  - Game review mode (analyze past games)  
  - Forfeit options  

---

## Project Structure

assets
  images # Images included in the game such  as the backgrounds, the button designs, the pieces, etc...
  gifs # Gifs used in the readme.
include
  utils.h # Utilities header.
  board.h # Board header.
src  
  main.cc # Main code, contains the implementation of the game and the interface.
  utils.cc # Utility functions mainly related with SDL ouput and input.
  board.cc # Class containing game logics, export/imports methods and AI related methods.

---

## Requirements
- C++17 or higher  
- SDL2  

---

## Usage

### Main Menu
![Main Menu GIF](./docs/gifs/main-menu.gif)

### Single Player
![Single Player GIF](./docs/gifs/single-player.gif)

### Multiplayer
![Multiplayer GIF](./docs/gifs/multiplayer.gif)

### Review Games Mode
![Review Games GIF](./docs/gifs/review-games.gif)
 

---

## Contributions 
Contributions are welcome and greatly appreciated, whether it's a bug fix or a new mechanic. To contribute, follow these steps:

1. **Fork** the repository.
```bash
git clone https://github.com/alejandromolton/Chess.git
cd Chess.git
```

2. **Create a branch** for your feature or bugfix.
```bash
git checkout -b feature-name
```

3. **Make your changes** and **commit them**.
```bash
git commit -m "Add a descriptive message"
```

4. **Push to your branch.**
```bash
git push origin feature-name
```

5. **Open a Pull Request here on GitHub and describe your changes.**
   Go to the fork you created and generate a pull request, provided with a clear title and description of your changes.

## About

The objective of this project is **purely educational**.  
Through it, I learned a lot about:  
- C++ and the transition from C  
- SDL for graphical interfaces  
- Basic AI in board games  
- File handling  

While this project works, it is not fully object-oriented. It follows a more imperative style due to my learning stage at the time. Future projects will be built with stronger OOP principles.
