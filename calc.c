#include <ctype.h>
#include <malloc.h>
#include <stdio.h>
#include "calc.h"
#include "mylib.h"
#include "stack.h"

/* define the word to be placed on the stack */
typedef struct CalcWord {

        /* operator fields */
        char ascii;             /* ascii character of operator */
        long index;             /* index in parallel arrays */
        long priority;          /* priority of operator */

        long value;             /* value of interest */
} CalcWord;

static char operators[] = "()+-*/^ !";

static long add (long, long);
static long divide (long, long);
static long exponent (long, long);
static long fact (long, long);
static char isoperator (CalcWord *);
static long mult (long, long);
static long sub (long, long);

static long (*functions[]) (long, long) =
        { NULL, NULL, add, sub, mult, divide, exponent, NULL, fact };

static CalcWord * new_CalcWord (long ascii, long value);

void delete_CalcWord (void * vpp) {
        CalcWord ** wpp = (CalcWord **) vpp;
        free (*wpp);
        *wpp = 0;
}


long eval (Stack * stack1) {
        CalcWord * op1, * op2;          /* the operands */
        CalcWord * operation;           /* the operation being performed */
        long result;                    /* result of computation */
        Stack * stack2;                 /* needed second stack */

        stack2 = new_Stack (0, delete_CalcWord, write_CalcWord);

        /* reverse stack1 onto stack2 */
        while (!isempty_Stack (stack1))
                push (stack2, pop (stack1));

        while (!isempty_Stack (stack2)) {

                /* digits go to stack1 */
                if (!isoperator ((CalcWord *) top (stack2)))
                        push (stack1, pop (stack2));
                
                /* operand found */
                else {
                        operation = (CalcWord *) pop (stack2);
                        
                        /* get operands */
                        op1 = (CalcWord *) pop (stack1);
                        if (operation->ascii != '!')
                                op2 = (CalcWord *) pop (stack1);
                        else
                                op2 = op1;

                        /* evaluate expression and push to stack1 */
                        result = functions[operation->index]
                                (op1->value, op2->value);

                        /* free up memory */
                        delete_CalcWord (&op1);
                        if (operation->ascii != '!')
                                delete_CalcWord (&op2);
                        delete_CalcWord (&operation);

                        push (stack1, new_CalcWord (0, result));
                }
        }

        op1 = (CalcWord *) pop (stack1);
        result = op1->value;

        /* free up memory */
        delete_CalcWord (&op1);
        delete_Stack (&stack2);

        return result;
}


long intopost (Stack * stack1) {
        long character;                 /* character input from the user */
        CalcWord * www;                 /* a CalcWord for the stack */
        Stack * stack2;                 /* needed second stack */

        stack2 = new_Stack (0, delete_CalcWord, write_CalcWord);
        
        while ((character = getchar()) != '\n') {

                /* check for termination of input */
                if (character == EOF) {
                        delete_Stack (&stack2);
                        return EOF;
                }

                /* ignore blanks */
                if (isspace (character))
                        continue;
                
                if (isdigit (character)) {

                        /* for decin call */
                        ungetc ((int) character, stdin);

                        /* place any numbers onto stack1 */

                        push (stack1, new_CalcWord (0, decin ()));
                }

                else if (character == '(') {

                        /* open parenthesis go onto stack2 */

                        push (stack2, new_CalcWord ('(', 0));
                
                }
                else if (character == ')') {

                        /* pop stack2 to stack1 until matching
                                parenthesis is found */
                        while (www = (CalcWord *) pop (stack2), 
                                                        www->ascii != '(')
                                push (stack1, www);

                        /* free up memory */
                        delete_CalcWord (&www);
                }

                /* operator must be encountered */
                else {
                        www = new_CalcWord (character, 0);/* to store on stack*/

                        /* pop stack2 to stack1 until empty or lower priority */
                        while (!isempty_Stack (stack2) &&
                                ((CalcWord *)top (stack2))->priority >= 
                                                                www->priority)
                                        push (stack1, pop (stack2));

                        /* finally place operator on stack2 */
                        push (stack2, www);
                }
        }

        /* place any remaining stack2 items to stack1 ==> done */
        while (!isempty_Stack (stack2))
                push (stack1, pop (stack2));
        
        /* remove old stack */
        delete_Stack (&stack2);

        return 1;
}


CalcWord * new_CalcWord (long ascii, long value) {
        
        /* allocate CalcWord to return */
        CalcWord * retval = (CalcWord *) malloc (sizeof (CalcWord));

        retval->ascii = (char)ascii;

        if (ascii) {
                long index = 0; /* index of the operand in character array */

                /* compute function index */
                while (operators[index] != ascii)
                        index++;

                retval->index = index;
                retval->priority = index >> 1;
        }
        else
                retval->value = value;

        return retval;
}


FILE * write_CalcWord (void * vp, FILE * stream) {

        CalcWord * w = (CalcWord *) vp;
        if (w->ascii) {

                /* output debugging info if output to stderr */
                if (stream == stderr) {
                        fprintf (stderr, "Function index is %ld, ",
                                w->index);
                        fprintf (stderr, "Priority is %ld, ",
                                w->priority);
                        fprintf (stderr, "Ascii character is %c.",
                                w->ascii);
                }
                else
                        fprintf (stream, "%c ", w->ascii);
        }
        else {
                fprintf (stream, "%ld ", w->value);
        }

        return stream;
}
        

static long add (long addendx, long addendy) {
        return addendx + addendy;
}

static long divide (long divisor, long dividend) {
        return dividend / divisor;
}

static long exponent (long power, long base) {
        long retval = 1;

        while (power > 0) {
                retval *= base;
                power--;
        }
        
        while (power < 0) {
                retval /= base;
                power++;
        }

        return retval;
}

static long fact (long xxx, long ignored) {
        return (xxx <= 1) ? 1 : xxx * fact (xxx - 1, ignored);
}

static char isoperator (CalcWord * word) {
        return word->ascii;
}

static long mult (long factorx, long factory) {
        return factorx * factory;
}

static long sub (long subtrahend, long minuend) {
        return minuend - subtrahend;
}
