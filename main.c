#include "main.h"

int main()
{

    // clear the output screen
    system("clear");

    // Declare an array to store input
    char input_string[25];

    // Initialize the array to 0
    memset(input_string, '0', 25);

    // Declare an array to store the prompt
    char prompt[25] = PROMPT;

    // Scan the input 
    scan_input(prompt, input_string);



    return 0;
}