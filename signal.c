#include "main.h"

extern pid_t pid;

void signal_handler(int sig_num)
{
    if(pid > 0)  // If a child process is running
    {
        if(sig_num == SIGINT)
        {
            // Terminate the process
            kill(pid, SIGKILL);
            printf("\n");
        }
        else if(sig_num == SIGTSTP)
        {
            // Stop a process
            kill(pid, SIGSTOP); 
        }
    }
    // If no foreground process exists ---> rediplay the prompt
    else if (pid == 0) // If no child process
    {
        if (sig_num == SIGINT)
        {
            printf("\n");
            // Display the prompt
            printf(ANSI_COLOR_RED"[%s]$:"ANSI_COLOR_RESET, PROMPT);
            fflush(stdout);
        }
    }
}