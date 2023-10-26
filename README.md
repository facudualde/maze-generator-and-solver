# maze-generator-and-solver
A versatile Python and C library for generating and solving mazes. It allows you to create nxn mazes with fixed and random obstacles, and a starting and ending point. The library includes a maze generator written in C, a maze solver implemented in Python using the A* algorithm, and some utility functions.
## Features
* Generate mazes based on a text file input, specifying dimensions, obstacles, and starting/ending points.
* Create custom mazes with a simple text format.
* Solve mazes using the A* algorithm in Python.
* Visualize the solved maze, highlighting the optimal path in green (if one exists).
* Efficiently manage obstacle data with a singly-linked list data structure.
## Usage
1. Maze Generator:
Prepare an input text file describing your maze (see the input format section for details).
Run the mazeGenerator executable giving the path of the input text file as argument to generate the maze.
```bash
make
make clean
./mazeGenerator input.txt
```
2. Maze Solver:
Use the mazeSolver.py script to solve the maze generated by the mazeGenerator.
The solved maze with the optimal path (if found) will be displayed.
```python
python mazeSolver.py maze.txt
```
## Input format
```yaml
dimension:
[positive integer]
fixed obstacles:
[list of coordinates]
random obstacles:
[nonnegative integer]
initial position:
[coordinate]
objective:
[coordinate]
```
Example:
```yaml
dimension:
20
fixed obstacles:
(1,2)
(1,5)
(2,4)
(7,5)
(3,4)
(3,2)
random obstacles:
100
initial position:
(1,1)
objective:
(16,15)
```
## License
This library is released under the MIT License.
