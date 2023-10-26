class Spot:
    def __init__(self, i, j, symbol):
        self.i = i # Row, from 0 to n-1
        self.j = j # Column, from 0 to n-1
        self.symbol = symbol # Character of the spot
        self.gScore = None # Distance between current and start
        self.hScore = None # Distance between current and goal
        self.fScore = None # f = g + h
        self.neighbors = []
        self.previous = None
    
    def __str__(self):
        return f"{self.i}, {self.j}, {self.symbol}"
    
    def __eq__(self, other):
        return (self.i == other.i and self.j == other.j and self.symbol == other.symbol)
    
    def getNeighbors(self, maze, dim): # Clearly this is not a very efficient way to get the neighbors...
        # Horizontal and vertical neighbors
        if self.i < dim - 1: # Lower neighbor
            if maze[self.i+1][self.j].symbol != '1':
                self.neighbors.append(maze[self.i+1][self.j])
        if self.i > 0: # Upper neighbor
            if maze[self.i-1][self.j].symbol != '1':
                self.neighbors.append(maze[self.i-1][self.j])
        if self.j < dim - 1: # Right neighbor
            if maze[self.i][self.j+1].symbol != '1':
                self.neighbors.append(maze[self.i][self.j+1])
        if self.j > 0: # Left neighbor
            if maze[self.i][self.j-1].symbol != '1':
                self.neighbors.append(maze[self.i][self.j-1])

        # Diagonal neighbors
        if self.i < dim - 1 and self.j < dim - 1: # Lower right neighbor
            if maze[self.i+1][self.j+1].symbol != '1':
                self.neighbors.append(maze[self.i+1][self.j+1])
        if self.i < dim - 1 and self.j > 0: # Lower left neighbor
            if maze[self.i+1][self.j-1].symbol != '1':
                self.neighbors.append(maze[self.i+1][self.j-1])
        if self.i > 0 and self.j < dim - 1: # Upper right neighbor
            if maze[self.i-1][self.j+1].symbol != '1':
                self.neighbors.append(maze[self.i-1][self.j+1])
        if self.i > 0 and self.j > 0: # Upper left neighbor
            if maze[self.i-1][self.j-1].symbol != '1':
                self.neighbors.append(maze[self.i-1][self.j-1])
