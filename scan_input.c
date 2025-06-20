#include "main.h"

pid_t pid;
int job_index = 0;

Job job_arr[MAX_JOBS];

void scan_input(char *prompt, char *input_string)
{
    // Variable declaration
    char *command = '\0';
    int command_type, ret_status, status;

    // Register the signal handlers for Ctrl+C and Ctrl+Z
    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);

    while(1)
    {
        memset(input_string, '\0', 25);
        // Display the prompt
        printf(ANSI_COLOR_RED"[%s]$:"ANSI_COLOR_RESET,prompt);

        // Clear the output buffer
        fflush(stdout);

        // Read the inpuyt from the user
        scanf("%[^\n]s",input_string);
        // Clear the input buffer
        getchar(); 

        // Customize the prompt
        if(!(strncmp("PS1=", input_string, 4)))
        {
            if(input_string[4] != ' ')
            {
                strcpy(prompt, &input_string[4]);
                // Flush the input_string
                memset(input_string, '0', 25);
                continue;
            }
        }

        // Check for 'jobs' command
        if(strcmp(input_string, "jobs") == 0)
        {
            // Display the stopped process
            print_jobs();
            continue;
        }

        // To get the command
        command = get_command(input_string);
        
        // To check whether the command is internal or external 
        command_type = check_command_type(command);
        // printf("Command type = %d\n", command_type);

        // Execute External command
        if(command_type == EXTERNAL)
        {
            pid = fork();
            if(pid == 0)    
            {
                // child process will execute the command
                ret_status = system(input_string);
                if(ret_status == 0)
                        exit(0);
                else
                        exit(1);
            }
            else if (pid > 0)
            {
                // Parent process
                waitpid(pid, &status, WUNTRACED);

                if (WIFEXITED(status))
                {
                    printf("Child PID %d terminated normally\n", pid);
                }
                else if (WIFSTOPPED(status))
                {
                    printf("\n[%d]\tStopped\t\t%s\n",job_index + 1, input_string);
                    printf("Child PID %d has been stopped...\n", pid);

                    job_arr[job_index].stop_count = job_index + 1;
                    strcpy(job_arr[job_index].status, "Stopped");
                    strcpy(job_arr[job_index].input_name, input_string);

                    // Insert into linked list
                    if(insert_at_last(job_arr[job_index]) == FAILURE)
                    {
                        printf("Failed to add into the linked list\n");
                        exit(1);
                    }

                    // Reset the job_arr index to 0
                    if(job_index++ == MAX_JOBS)
                    {
                        job_index = 0;
                    }
                }

                // Reset pid when the child is done
                pid = 0;
            }
            else
            {
                    printf("fork failed\n");
                    exit(2);
            }
        }

        // Call the function to implement echo commands
        echo(input_string, status);

        // Function to implement internal commands
        execute_internal_commands(input_string);

    }
}