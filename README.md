<div align="center">
  <h1>CHESS</h1>
  <div>A chess engine built in <strong>C++</strong> using the <strong>SDL library</strong>, featuring a graphical interface.</div>
  <div>This project is the direct evolution of my earlier project <strong>C Chess</strong>, which was a terminal-only chess engine written in <strong>C</strong>.</div>
<br>
  <div>
    <img src="https://img.shields.io/badge/language-C++-blue.svg" alt="C++" style="display:inline-block; margin:2px;">
    <img src="https://img.shields.io/badge/library-SDL2-green.svg" alt="SDL2" style="display:inline-block; margin:2px;">
    <img src="https://img.shields.io/badge/License-MIT-yellow.svg" alt="License: MIT" style="display:inline-block; margin:2px;">
    <img src="https://img.shields.io/badge/contributions-OPEN-brightgreen.svg" alt="Contributions Open" style="display:inline-block; margin:2px;">
  </div>
</div>


---

## Table of Contents
1. [Features](#-features)  
2. [Project Structure](#-project-structure)  
3. [Requirements](#-requirements)  
4. [Usage](#-usage)  
5. [Contributions](#-contributions)  
6. [About](#-about)
7. [Licence](#-licence)


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

`assets/`
* `images/`: Images for the game, including backgrounds, button designs, and game pieces.
* `gifs/`: GIFs used in the project's README file.

`include/`
* `utils.h`: Header file for utility functions.
* `board.h`: Header file for the `Board` class.

`src/`
* `main.cc`: The main source file that implements the game's interface and core loop.
* `utils.cc`: The source file for utility functions, primarily related to SDL output and input.
* `board.cc`: The source file for the `Board` class, which contains the game logic, AI methods, and import/export functionality.

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
- OOP Paradigm
- SDL for graphical interfaces  
- Basic AI in board games  
- File handling

While this project works, it is not fully object-oriented. It follows a more imperative style due to my learning stage at the time. Future projects will be built with stronger OOP principles.

## Licence

This project is licenced under the MIT licence.
