#include <malloc.h>
#include <stdio.h>
#include <getopt.h>
#include "mylib.h"
#include "stack.h"

typedef struct {
        long xxx;
} MyRec;

void delete_MyRec (void * vpp) {
        MyRec ** myrecpp = (MyRec **) vpp;
        free (*myrecpp);
        *myrecpp = 0;
}

void * copy_MyRec (void * vp) {
        MyRec * myrecp = (MyRec *) vp;
        MyRec * this_MyRec = (MyRec *) malloc (sizeof(MyRec));
        this_MyRec->xxx = myrecp->xxx;
        return this_MyRec;
}

FILE * write_MyRec (void * vp, FILE * stream) {
        MyRec * myrecp = (MyRec *) vp;
        fprintf (stream, "MyRec has value of:  %ld", myrecp->xxx);
        return stream;
}

static long from_where (void);

int main (int argc, char *const* argv) {

        MyRec element;                  /* to store in the stack */
        MyRec * retval;                 /* to retrieve from the stack */
        Stack * main_stack;             /* the list/stack to test */
        int option;                    /* each command line option */
        long command;                   /* stack command entered by user */
        long status;                    /* return status of stack functions */

        /* initialize debug states */
        set_debug_off();

        /* check command line options for debug display */
        while ((option = getopt (argc, argv, "x")) != EOF) {

                switch (option) {
                        case 'x': set_debug_on(); break;
                }
        }

        /* allocate and initialize */
        main_stack = new_Stack(copy_MyRec, delete_MyRec, write_MyRec);
        
        while (1) {
                command = 0;    /* initialize command, need for loops */
                writeline ("\nThe commands are:\n");
                writeline ("    is(e)mpty, ");
                writeline ("(i)nsert, ");
                writeline ("(p)op, ");
                newline ();
                writeline ("    (a)dvance pre, advance (n)ext, ");
                newline ();
                writeline ("    (r)emove, ");
                writeline ("(t)op, ");
                writeline ("p(u)sh, (v)iew, ");
                newline ();
                writeline ("    (w)rite, (W)rite_reverse,");
                newline ();

                writeline ("\nPlease enter a command:  ");
                command = fgetc (stdin);
                if (command == EOF)     /* are we done? */
                        break;
                clrbuf (command);       /* get rid of extra characters */

                switch (command) {      /* process commands */
                case 'a':               /* advance pre */
                        advance_pre_List (main_stack);
                        break;

                case 'n':               /* advance next */
                        advance_next_List (main_stack);
                        break;

                case 'e':               /* isempty */
                        if (isempty_Stack (main_stack))
                                writeline ("\nStack is empty.");
                        else
                                writeline ("\nStack is not empty.");
                        break;

                case 'i':               /* insert */
                        writeline (
                        "\nPlease enter a number to insert into list:  ");
                        element.xxx = decin ();
                        clrbuf (0);     /* get rid of extra characters */
                        status = insert (main_stack, &element, from_where ());
                        if (! status)
                                fprintf (stderr,
                                "\nWARNING:  insert FAILED\n");
                        break;


                case 'p':               /* pop */
                        retval = (MyRec *) pop (main_stack);
                        if (! retval)
                                fprintf (stderr,
                                        "\nWARNING:  pop FAILED\n");
                        else {
                                element = *retval;
                                writeline (
                                        "\nNumber popped from the stack is:  ");
                                write_MyRec (&element, stdout);
                                delete_MyRec (&retval);
                        }
                        break;

                case 'r':               /* remove */
                        retval = 
                        (MyRec *) remove_List (main_stack, from_where ());
                        if (! retval)
                                fprintf (stderr,
                                "\nWARNING:  remove FAILED\n");
                        else {
                                element = *retval;
                                writeline (
                                "\nNumber removed from list is:  ");
                                write_MyRec (&element, stdout);
                                delete_MyRec (&retval);
                        }
                        break;

                case 't':               /* top */
                        retval = (MyRec *) top (main_stack);
                        if (! retval)
                                fprintf (stderr,
                                        "\nWARNING:  top FAILED\n");
                        else {
                                element = *retval;
                                writeline (
                                        "\nNumber at top of the stack is:  ");
                                write_MyRec (&element, stdout);
                        }
                        break;

                case 'u':               /* push */
                        writeline (
                                "\nPlease enter a number to push to stack:  ");
                        element.xxx = decin ();
                        clrbuf (0);     /* get rid of extra characters */
                        status = push (main_stack, &element);
                        if (! status)
                                fprintf (stderr,
                                        "\nWARNING:  push FAILED\n");
                        break;

                case 'v':               /* view */
                        retval = (MyRec *) view (main_stack, from_where ());
                        if (! retval)
                                fprintf (stderr,
                                        "\nWARNING:  view FAILED\n");
                        else {
                                element = *retval;
                                writeline (
                                "\nNumber viewed from the list is:  ");
                                write_MyRec (&element, stdout);
                        }
                        break;

                case 'w':               /* write */
                        writeline ("\nThe Stack contains:\n");
                        write_Stack (main_stack, stderr);
                        newline ();
                        break;

                case 'W':               /* write */
                        writeline ("\nThe Stack contains (in reverse):\n");
                        write_reverse_List (main_stack, stderr);
                        newline ();
                        break;
                }
        }

        delete_Stack (&main_stack);     /* deallocate stack */
        newline ();
        return 0;
}

/* This function prompts the user where in the list they want to
either insert, remove, or view, depending upon from which part
of the driver the function is called. */
static long from_where (void) {

        int character; 
        long retval;
        writeline ("Specify 1 for FRONT, 0 for END or location number");
        writeline ("\nPlease enter choice:  ");

        if ((character = fgetc(stdin)) == '\n')
                retval = -1;

        else {
                ungetc (character, stdin);
                retval  = decin ();
                clrbuf (0);
        } 

        return retval;
}

