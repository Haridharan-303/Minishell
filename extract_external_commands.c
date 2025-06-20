#include "main.h"

void extract_external_commands(char **external_commands)
{
    // Variable declaration
    char ch;
    char buffer[25] = {'\0'};
    int i = 0, j = 0;

    // Open the file
    int fd = open("external_command.txt", O_RDONLY);
    
    // Error check
    if(fd == -1)
    {
        printf("File Open Failed\n");
        exit(1);
    }
    int c = 0;
    // Read the commands from the file
    while(read(fd, &ch, 1) > 0)
    {
        if(ch != '\n')
        {
            buffer[i++] = ch; 
        }
        else
        {
            // Allocate sufficient memory
            external_commands[j] = calloc(strlen(buffer)+1, sizeof(char));
            // Copy the contents
            strcpy(external_commands[j++], buffer);
            // Append a null  character at the end
            external_commands[j] = NULL;
            // Clear the buffer
            memset(buffer, '\0', 25);
            i = 0;
        }
    }

    // Close the file
    close(fd);
}