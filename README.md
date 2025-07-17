# UCLA CS 32 – Data Structures & Algorithms

This repository contains my solutions to the programming assignments and projects for **CS 32: Data Structures & Algorithms** at UCLA (Winter 2025). Throughout the quarter I implemented a variety of abstract data types, recursive algorithms, graph traversals, and object-oriented designs in C++.

## Overview

| Assignment     | Topics Covered                                                  | Key Files                                                     |
|---------------:|-----------------------------------------------------------------|---------------------------------------------------------------|
| **Homework 1** | Array-based Sequence ADT, TurnoutList ADT, unit testing         | `Sequence.h`, `Sequence.cpp`, `TurnoutList.h`, `testSequence.cpp` |
| **Homework 2** | Stack & queue implementations, maze traversal, expression eval   | `mazequeue.cpp`, `mazestack.cpp`, `eval.cpp`                  |
| **Homework 3** | Recursive landmark detection, linear list ops, maze exploration, binary trees | `landmark.cpp`, `linear.cpp`, `maze.cpp`, `tree.cpp`           |
| **Homework 4** | Debugging list & vector ADTs, odd/even filters, sorting         | `list.cpp`, `badlist.cpp`, `oddvector.cpp`, `sorts.cpp`       |
| **Project 1**  | OOP design & simulation (Bee game)                              | `Game.cpp`, `Bee.cpp`, `History.cpp`, `main.cpp`              |
| **Project 2**  | Sequence ADT extension & test harness                           | `Sequence.cpp`, `testSequence.cpp`, `report.txt`              |
| **Project 5**  | File I/O, flight-map parser, graph search (A* with caching)     | `fm.cpp`, `bstset.h`, `tp.cpp`                                |

## Building & Running

All code targets **C++11** and was tested on macOS (clang++) and Linux (g++). From any assignment or project folder:

```bash
# compile all .cpp files
clang++ -std=c++11 -Wall -Werror *.cpp -o main

# run
./main
```