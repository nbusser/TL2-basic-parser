/* Implementation of "lexer.h" */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lexer.h"

/* NB: allocation below requires that END is the last token 
   TAKE CARE to synchronize token_name with token type of lexer.h
*/
static const char* token_name[END+1] = {
        "a",
        "b",
        "c",
        "<END>"
};

void display(token t) {
        printf("%s", token_name[t]);               
}

void unexpected(token t, const char *mesg) {
        printf("ERROR: unexpected token ");
        display(t);
        if (mesg[0] != 0) {
                printf(" in %s", mesg);
        }
        printf("\n");
        exit(1);
}

static char current;

static void update_current() {
        current = fgetc(stdin);
}

/* Boolean variable indicating whether "current" has been initialized or not
   NB: this variable is only used in "next".
 */ 
static int init = 0;

token next() {
        if (! init) {
                update_current();
                init = 1;
        }
        for ( ; ; ) {
                switch (current) {
                case 'a':
                        update_current();
                        return a;
                case 'b':
                        update_current();
                        return b;
                case 'c':
                        update_current();
                        return c;
                case '$':
                        return END;
                case 'q':
                        printf("Bye\n");
                        exit(0);
                case ' ':
                        update_current();
                        break;
                case '\n':
                        update_current();
                        break;
                default:
                        printf("WARNING: ignoring invalid character '%c'\n", current);
                        update_current();
                }
        }
}
