🐍 Eunectes murinus - Snake Game in C++
Created by: Sara Hisham - Rayan Gurashi

1. DESCRIPTION

Eunectes murinus is a console-based Snake game developed in C++ using 
Object-Oriented Programming (OOP) principles.

The player controls a snake that moves around the screen to eat food. 
Each time the snake eats, it grows longer. The goal is to survive as 
long as possible without crashing into the walls or the snake's own body.

The name Eunectes murinus refers to the green anaconda, one of the 
largest snakes in the world - just like your snake in the game can 
grow to great lengths!

-------
2. HOW TO RUN

REQUIREMENTS:
• Windows OS (uses conio.h and Windows.h)
• C++ Compiler:
  - GCC (MinGW)
  - Microsoft Visual Studio

STEPS:
1. Open terminal/command prompt
2. Navigate to folder containing main.cpp
3. Compile: g++ main.cpp -o snake.exe
4. Run: ./snake.exe

Note: Ensure your C++ compiler is properly configured in system PATH.

-------
3. CONTROLS

KEY    ACTION
----   ------------------
W      Move Up
A      Move Left
S      Move Down
D      Move Right
P      Pause/Resume
X      Exit Game

-------
4. FEATURES

✓ Snake movement and growth system
✓ Wall and self-collision detection
✓ Scoring system (increases per food)
✓ Pause/Resume functionality (P key)
✓ Wrap-around map edges
✓ Clean console interface
✓ Object-oriented design (C++ classes)
