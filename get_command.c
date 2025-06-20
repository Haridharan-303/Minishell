#include "main.h"

// Extract the command until the space is encountered eg: ls -l, ech $
char *get_command(char *input_string)
{
    // Declare an array the to store the command
    static char command[25] = {'\0'};

    int i = 0;

    while(1)
    {
        if(*input_string == ' ' || *input_string == '\0')
                break;
        command[i++] = *input_string;
        input_string++;
    }
    command[i] = '\0';

    return command;
}