# Teleword Puzzle Solver

This repository contains a program designed to solve Teleword puzzles. Teleword is a word puzzle found in newspapers worldwide, including the daily Dawn in Pakistan. The goal of the game is to find words within a grid of letters, which may appear in forward or backward directions in rows, columns, or diagonals.

## How to Use

1. **Input File**: Ensure you have a text file named `teleword.txt` containing the Teleword puzzle. The file should have the following format:
   - A grid of letters separated by commas. Rows and column should be of same number
   - An empty line.
   - A list of words separated by commas.

2. **Running the Program**: Execute the program, and it will prompt you to press a key to find the next word. Each key press will reveal the next word in the puzzle.

3. **Solving the Puzzle**: After finding all the words, the program will display the Teleword composed of the leftover letters in the grid.

4. **Viewing Statistics**: Upon completing the puzzle, the program will display various statistics, including the time taken to find each word, the total time to solve the puzzle, the average word length, word distribution (horizontal, vertical, diagonal), and the Teleword scatter.

## Description

The Teleword Puzzle Solver is a C++ program designed to read Teleword puzzles from a text file and solve them efficiently. The program utilizes dynamic arrays to store the grid of letters and the list of words. It then sequentially reveals each word in the puzzle upon user input.

Upon solving the puzzle, the program calculates various statistics, including the time taken to find each word, the average word length, word distribution in terms of directionality (forward, backward) and orientation (horizontal, vertical, diagonal), and the Teleword scatter.

## Files

- **teleword_solver.cpp**: The main C++ source code file containing the implementation of the Teleword Puzzle Solver.
- **teleword.txt**: Example input file containing a Teleword puzzle.
- **README.md**: This file providing instructions and information about the program.

## Requirements

- C++ compiler capable of compiling C++11 standard or higher.

## Usage

1. Compile the program using a C++ compiler.
2. Use command line arguemnets to give the file name
3. Use like this: ./[Executable name] [Name of telewordfile]
4. Teleword.txt should be contains a comma separated grid and comma separated words followed by a line between grid and words
5. Some files are given for demonstration
6. Ensure `teleword.txt` is in the same directory as the compiled executable.
7. Run the executable.
8. Follow the on-screen prompts to solve the Teleword puzzle.

## Contributors

- Syed Muhammad Saad Bukhari
- syed4000saad@gmail.com  

- Feel free to contribute, report issues, or suggest improvements!
