#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include "TList.h"
#include "utils.h"
#define SIZEBUFF 256

int parse_input_file(FILE *inputFile, int *dimension, TNode **fixedObs, int *randomObs, Tuple *initialPosition, Tuple *objective)
{
    char buff[SIZEBUFF];
    memset(buff, '\0', SIZEBUFF);

    // Dimension
    fgets(buff, SIZEBUFF, inputFile);
    remove_spaces_and_newline(buff);
    while(buff[0] == '\0')
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
    }
    if(strcmp(buff, "dimension:") == 0)
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
        while(buff[0] == '\0')
        {
            fgets(buff, SIZEBUFF, inputFile);
            remove_spaces_and_newline(buff);
        }
        char c;
        if(sscanf(buff, "%d%c", dimension, &c) > 1)
        {
            printf("Error, no dimension provided\n");
            return 1;
        }
        if(*dimension <= 0)
        {
            printf("Error, no dimension provided\n");
            return 1;
        }
    }
    printf("Dimension: %d\n", *dimension);
    
    // Fixed obstacles
    fgets(buff, SIZEBUFF, inputFile);
    remove_spaces_and_newline(buff);
    while(buff[0] == '\0')
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
    }
    printf("%s\n", buff);
    if(strcmp(buff, "fixedobstacles:") == 0)
    {
        while(strcmp(buff, "randomobstacles:") != 0)
        {
            fgets(buff, SIZEBUFF, inputFile);
            remove_spaces_and_newline(buff);
            printf("%s\n", buff);
            if(buff[0] != '\0')
            {
                if(strcmp(buff, "randomobstacles:") != 0)
                {
                    char paren[SIZEBUFF];
                    int x, y;
                    if(sscanf(buff, "(%d,%d%s", &x, &y, paren) != 3 || strcmp(paren, ")") != 0)
                    {
                        printf("Error on fixed obstacle\n");
                        return 1;
                    }
                    if(x <= 0 || y <= 0)
                    {
                        printf("Error on fixed obstacle\n");
                        return 1;
                    }
                    tlist_add_to_the_end(fixedObs, x, y);
                }
            }
        }
    } else
    {
        printf("Syntax error\n");
        return 1;
    }

    printf("Fixed obstacles:\n");
    tlist_print(*fixedObs);

    // Random obstacles
    if(strcmp(buff, "randomobstacles:") == 0)
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
        while(buff[0] == '\0')
        {
            fgets(buff, SIZEBUFF, inputFile);
            remove_spaces_and_newline(buff);
        }
        char c;
        if(sscanf(buff, "%d%c", randomObs, &c) > 1)
        {
            printf("Error, no random obstacles provided\n");
            return 1;
        }
        if(*randomObs < 0 || *randomObs > (*dimension) * (*dimension))
        {
            printf("Error, no random obstacles provided\n");
            return 1;
        }
    } else
    {
        printf("Syntax error\n");
        return 1;
    }    
    printf("Random obstacles: %d\n", *randomObs);

    // Initial position
    fgets(buff, SIZEBUFF, inputFile);
    remove_spaces_and_newline(buff);
    while(buff[0] == '\0')
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
    }
    if(strcmp(buff, "initialposition:") == 0)
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
        while(buff[0] == '\0')
        {
            fgets(buff, SIZEBUFF, inputFile);
            remove_spaces_and_newline(buff);
        }
        char paren[SIZEBUFF];
        if(sscanf(buff, "(%d,%d%s", &initialPosition->x, &initialPosition->y, paren) != 3 || strcmp(paren, ")") != 0)
        {
            printf("Error, no initial position provided\n");
            return 1;
        }
        if(initialPosition->x <= 0 || initialPosition->y <= 0)
        {
            printf("Error, no initial position provided\n");
            return 1;
        }
    } else
    {
        printf("Syntax error\n");
        return 1;
    }
    printf("Initial position:\n");
    printf("(%d,%d)\n", initialPosition->x, initialPosition->y);

    // Objective
    fgets(buff, SIZEBUFF, inputFile);
    remove_spaces_and_newline(buff);
    while(buff[0] == '\0')
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
    }
    if(strcmp(buff, "objective:") == 0)
    {
        fgets(buff, SIZEBUFF, inputFile);
        remove_spaces_and_newline(buff);
        while(buff[0] == '\0')
        {
            fgets(buff, SIZEBUFF, inputFile);
            remove_spaces_and_newline(buff);
        }
        char paren[SIZEBUFF];
        if(sscanf(buff, "(%d,%d%s", &objective->x, &objective->y, paren) != 3 || strcmp(paren, ")") != 0)
        {
            printf("Error, no objective position provided\n");
            return 1;
        }
        if(objective->x <= 0 || objective->y <= 0)
        {
            printf("Error, no objective position provided\n");
            return 1;
        }
    } else
    {
        printf("Syntax error\n");
        return 1;
    }
    printf("Objective:\n"); 
    printf("(%d,%d)\n", objective->x, objective->y);

    return 0;
}

void generate_maze(char ***maze, int dimension, int randomObs, Tuple initialPosition, Tuple objective, TList fixedObs)
{
    *maze = malloc(dimension*sizeof(char*));
    for(int i = 0; i < dimension; i++)
    {
        (*maze)[i] = malloc(dimension*sizeof(char));
        memset((*maze)[i], '\0', dimension);
    }

    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
            (*maze)[i][j] = '0';
    }
    
    for(TNode *temp = fixedObs; temp != NULL; temp = temp->next)
    {
        (*maze)[temp->data.x-1][temp->data.y-1] = '1';
    }

    for(int i = 0; i < randomObs; i++)
    {
        unsigned int x = rand() % dimension + 1;
        unsigned int y = rand() % dimension + 1;
        (*maze)[x-1][y-1] = '1';
    }

    (*maze)[initialPosition.x-1][initialPosition.y-1] = 'I';
    (*maze)[objective.x-1][objective.y-1] = 'X';
}

int main(int argc, char **argv)
{   
    srand(time(NULL));
    int dimension, randomObs;
    Tuple initialPosition, objective;
    TList fixedObs = tlist_create();

    FILE *inputFile = fopen(argv[1], "r"); // Open text file with maze description
    // Parse input file and extract data
    int p = parse_input_file(inputFile, &dimension, &fixedObs, &randomObs, &initialPosition, &objective);
    fclose(inputFile);
    
    // If there was an error on parsing then return 1
    if(p == 1)
        return 1;

    char **maze;
    generate_maze(&maze, dimension, randomObs, initialPosition, objective, fixedObs);
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            printf("%c ", maze[i][j]);
        }
        printf("\n"); // Nueva línea para la siguiente fila
    }

    // Write maze to a text file
    FILE *outputFile = fopen("maze.txt", "w");

    for(int i = 0; i < dimension; i++)
    {
        for(int j = 0; j < dimension; j++)
        {
            fputc(maze[i][j], outputFile);
        }
        if(i < dimension-1)
            fputc('\n', outputFile);
    }

    fclose(outputFile);

    for(int i = 0; i < dimension; i++)
    {
        free(maze[i]);
    }
    free(maze);
    tlist_delete(fixedObs);

    return 0;
}
