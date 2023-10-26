#include "utils.h"

// Function to remove all spaces and newline charactres from a string, and puts '\0' at the end of the string
void remove_spaces_and_newline(char *str) {
    int non_space_count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\n' && str[i] != '\n' && str[i] != '\r')
        {
            str[non_space_count] = str[i];
            non_space_count++;
        }    
    }
     
    str[non_space_count] = '\0';
}
