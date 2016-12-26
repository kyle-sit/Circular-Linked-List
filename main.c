#include <stdio.h>
#include <getopt.h>
#include "calc.h"
#include "mylib.h"
#include "stack.h"

int main (int argc, char *const* argv) {

        Stack * main_stack;     /* to store the postfix expression */
        int option;            /* each command line option */

        /* initialize debug states */
        set_debug_off();

        /* check command line options for debug display */
        while ((option = getopt (argc, argv, "x")) != EOF) {

                switch (option) {
                        case 'x': set_debug_on(); break;
                }
        }

        main_stack = new_Stack (0, delete_CalcWord, write_CalcWord);

        while (1) {
                writeline ("\nPlease enter an expression to calculate:  ");
                if (intopost (main_stack) == EOF)
                        break;
                
                writeline ("\nThe expression in postfix order is:  ");
                write_Stack (main_stack, stdout);

                writeline ("\n which evaluates to:  ");
                fprintf (stdout, "%ld", eval (main_stack));
        }

        delete_Stack (&main_stack);
        newline ();
        return 0;
}
