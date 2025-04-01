# Advent of Code - Solutions

This project contains the solutions for the Advent of Code challenges. The solutions are written in C++ and will cover multiple years starting from 2024.

## Project Structure

```
advent-of-code/
│
├── <year>/
│   ├── <day>.cpp      # C++ source file for the solution of a specific day
├── a.out              # Compiled executable
├── in.txt             # Input file with data for the challenges

```

- `<year>`: This will be the directory for a specific year's solutions.
- `<day>`: This represents the day in the Advent of Code challenge, where each day's solution is stored in a separate `.cpp` file.
- `a.out`: The compiled executable.
- `in.txt`: The input file with data that the program will process.

## Description

This repository contains C++ solutions to the problems provided in the Advent of Code challenges. The solutions will be organized by year, starting from 2024, and will be added as new challenges are solved.

## How to Run

1. **Clone the repository**:

```bash
git clone https://github.com/sothearo-kay/advent-of-code.git
cd advent-of-code
```

2. **Compile the C++ code**: To compile the C++ solution, use the following command:

```bash
g++ -std=c++17 <year>/<day>.cpp -o output && ./output
```

3. **Input**: The program reads input from the file `in.txt`, which contains the data for the challenge.
4. **Output**: After executing the command, the program will output the result to the terminal.

## Example

Given an `in.txt` file containing the following input:

```
7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9
```

The program will process the levels, apply the rules, and print the result.
