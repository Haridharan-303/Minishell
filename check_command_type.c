#include "main.h"

int check_command_type(char *command)
{
    // Check whether the command is internal or external
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval", "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source", "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help", NULL};

    // Cehck if the user presses the enter key
    if(strcmp(command, "\0") == 0)
    {
        return NO_COMMAND;
    }

    // Check if the command is builtin
    for(int i = 0; builtins[i] != NULL; i++)
    {
        if(strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN;
        }
    }

    // To extract external command
    char *external_commands[155] = {NULL};
    extract_external_commands(external_commands);

    // Check if the command is an external command
    for(int i = 0; external_commands[i] != NULL; i++)
    {
        if(strncmp(command, external_commands[i], strlen(command)) == 0)
        {
            return EXTERNAL;
        }
    }
}
