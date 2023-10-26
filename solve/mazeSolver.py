import sys
from Spot import Spot

def importMaze(path):
    try:
        with open(path, "r") as inputFile:
            start = None
            goal = None
            maze = []
            dim = 0
            i = 0
            for line in inputFile:
                j = 0
                row = []
                while j < len(line) and line[j] != '\n':
                    s = Spot(i, j, line[j])
                    if line[j] == 'I':
                        start = s
                    elif line[j] == 'X':
                        goal = s
                    row.append(s)
                    j += 1
                i += 1
                dim += 1
                maze.append(row)
            return (maze, start, goal, dim)
    except FileNotFoundError:
        print("File does not exist")

# Euclidean distance could have been used
def heuristic(a, b):
    return (abs(a.i - b.i) + abs(a.j - b.j))

def getCurrent(openSet):
    winner = openSet[0]
    for el in openSet:
        if el.fScore < winner.fScore:
            winner = el
    return winner

def A_Star(maze, start, goal, dim):
    path = []
    closedSet = []
    openSet = [start]
    
    start.gScore = 0
    start.hScore = heuristic(start, goal)
    start.fScore = start.hScore

    while len(openSet) > 0:
        current = getCurrent(openSet)
        if current == goal:
            print("DONE!")
            path = [goal]
            temp = current.previous
            while temp:
                path.append(temp)
                temp = temp.previous
            path.reverse()
            return path
        openSet.remove(current)
        closedSet.append(current)
        current.getNeighbors(maze, dim)
        for n in current.neighbors:
            if n not in closedSet:
                tempGScore = current.gScore + 1
                if n in openSet:
                    if tempGScore < n.gScore:
                        n.gScore = tempGScore
                        n.fScore = n.hScore + n.gScore
                else:
                    n.gScore = tempGScore
                    n.hScore = heuristic(n, goal)
                    n.fScore = n.gScore + n.hScore
                    n.previous = current
                    openSet.append(n)
    print("No solution")
    return 1
        

def main():
    # If maze.txt not provided or more arguments than necessary then return 1
    if(len(sys.argv) != 2):
        print("Invalid number of arguments")
        return 1
    (maze, start, goal, dim) = importMaze(sys.argv[1]) # Obtain maze, start spot, goal spot, and dimensions of the maze 
    r = A_Star(maze, start, goal, dim) # Solve the maze and obtain the best path from start to goal
    
    # Print maze with its solution
    if r != 1:
        for i in range(0, len(maze)):
            for j in range(0, len(maze[i])):
                if maze[i][j] in r:
                    print("\033[32m"+maze[i][j].symbol+"\033[0m", end='')
                else:
                    print(maze[i][j].symbol, end='')
            print()
    return 0

if __name__ == "__main__":
    main()  
