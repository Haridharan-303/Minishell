#include "main.h"

void execute_internal_commands(char *input_string)
{
    // execute exit, cd, pwd

    // variable declaration
    char *path, *backup_path;

    // Terminate the program -> exit
    if(strncmp("exit", input_string, 4) == 0)
    {
        exit(0);
    }

    // To print present working directory
    if(strncmp("pwd", input_string, 3) == 0)
    {
        system("pwd");
    }

    // Change directory
    if(strncmp("cd", input_string, 2) == 0)
    {
        // cd abc
        // 012345
        // chdir(&input_string[3]);    // Without spaces

        // with space
        path = strtok(input_string, " ");
        while(path != NULL)
        {
            backup_path = path;
            path = strtok(NULL, " ");
        }
        chdir(backup_path);
    }


}