/*
Name : Suraj Roy
Date 16/01/2023
Description : Implement a minimalistic shell, mini-shell(msh) as part of the Linux Internal module.
*/

#include"main.h"

int main()
{
       //clear the output screen
       system("clear");

       //declare an array to store the input
       char input_string[25];

       // declare an array to store the prompt
       char prompt[25] = "msh";

       //scan the input
       scan_input(prompt, input_string);

       return 0;

}
