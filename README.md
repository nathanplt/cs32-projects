# UCLA CS 32 – Data Structures & Algorithms

This repository contains my solutions to the programming assignments and projects for **CS 32: Data Structures & Algorithms** at UCLA (Winter 2025). Throughout the quarter I implemented a variety of abstract data types, recursive algorithms, graph traversals, and object-oriented designs in C++.

## Overview

| Assignment        | Topics Covered                                           | Key Files                                   |
|------------------:|-----------------------------------------------------------|---------------------------------------------|
| **Homework&nbsp;1** | Sequence ADT (array-based), TurnoutList ADT, unit tests   | `Sequence.{h,cpp}`, `TurnoutList.h`, `testSequence.cpp` |
| **Homework&nbsp;2** | Stacks/queues, maze traversal, expression eval            | `mazequeue.cpp`, `mazestack.cpp`, `eval.cpp` |
| **Homework&nbsp;3** | Recursion, linear ops, maze exploration, binary trees     | `landmark.cpp`, `maze.cpp`, `tree.cpp`       |
| **Homework&nbsp;4** | Debugging list/vector ADTs, odd/even filters, sorting     | `list.cpp`, `oddvector.cpp`, `sorts.cpp`     |
| **Project&nbsp;1**  | OOP design & simulation (Bee game)                        | `Game.cpp`, `Bee.cpp`, `main.cpp`            |
| **Project&nbsp;2**  | Sequence ADT extension & test harness                      | `Sequence.cpp`, `testSequence.cpp`           |
| **Project&nbsp;5**  | Flight-map parser, graph search (A* w/ caching), file I/O  | `fm.cpp`, `tp.cpp`, `bstset.h`               |
## Building & Running

All code targets **C++11** and was tested on macOS (clang++) and Linux (g++). From any assignment or project folder:

```bash
# compile all .cpp files
clang++ -std=c++11 -Wall -Werror *.cpp -o main

# run
./main
```