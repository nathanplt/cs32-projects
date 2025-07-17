# UCLA CS 32 – Data Structures & Algorithms

This repository contains my solutions to the programming assignments and projects for **CS 32: Data Structures & Algorithms** at UCLA (Winter 2025). Throughout the quarter I implemented a variety of abstract data types, recursive algorithms, graph traversals, and object-oriented designs in C++.

## Overview

| Assignment     | Topics Covered                                                  | Key Files                                                                                  |
|---------------:|-----------------------------------------------------------------|--------------------------------------------------------------------------------------------|
| **Homework 1** | Array-based Sequence ADT, TurnoutList ADT, unit testing         | `Homework 1/Sequence.h/.cpp`, `Homework 1/TurnoutList.h/.cpp`, test drivers                |
| **Homework 2** | Stack & queue implementations, maze traversal, expression eval   | `Homework 2/mazequeue.cpp`, `Homework 2/mazestack.cpp`, `Homework 2/eval.cpp`               |
| **Homework 3** | Recursive landmark detection, linear list ops, maze exploration, binary trees | `Homework 3/landmark.cpp`, `Homework 3/linear.cpp`, `Homework 3/maze.cpp`, `Homework 3/tree.cpp` |
| **Homework 4** | Debugging list & vector ADTs, odd/even filters, sorting         | `Homework 4/list.cpp/.h`, `Homework 4/badlist.cpp`, `Homework 4/oddvector.cpp`, `Homework 4/sorts.cpp` |
| **Project 1**  | OOP design & simulation (Bee game)                              | `Project 1/Game.cpp/.h`, `Project 1/Bee.cpp/.h`, `Project 1/History.cpp/.h`, `Project 1/main.cpp` |
| **Project 2**  | Sequence ADT extension & test harness                           | `Project 2/Sequence.cpp/.h`, `Project 2/testSequence.cpp`, `Project 2/report.txt`           |
| **Project 5**  | File I/O, flight-map parser, graph search (A* with caching)             | `Project 5/fm.cpp/.h`, `Project 5/bstset.h`, `Project 5/tp.cpp/.h`, `Project 5/airports.txt`, `Project 5/all_flights.txt` |

## Building & Running

All code targets **C++11** and was tested on macOS (clang++) and Linux (g++). From any assignment or project folder:

```bash
# compile all .cpp files
clang++ -std=c++11 -Wall -Werror *.cpp -o main

# run
./main
```
