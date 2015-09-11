/*
 * Copyright (c) 2013, frp
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * The Software is provided "as is", without warranty of any kind, express or
 * implied, including but not limited to the warranties of merchantability,
 * fitness for a particular purpose and noninfringement. In no event shall the
 * authors or copyright holders be liable for any claim, damages or other
 * liability, whether in an action of contract, tort or otherwise, arising from,
 * out of or in connection with the software or the use or other dealings in
 * the Software.
 *
 * Except as contained in this notice, the name of the copyright holders shall
 * not be used in advertising or otherwise to promote the sale, use or other
 * dealings in this Software without prior written authorization from the
 * copyright holders.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "data.h"
#include "errors.h"
#include "interpreter.h"

#define MAXMEM      30000
#define MAXINPUT    100

static char input_string[MAXINPUT] = {0};
static int next_pos = 0;

static void memdisplay(uint16_t *);

void readInput(FILE *input, Queue *q) {
    int current;
    Stack *s = inits();
    Token *temp = NULL;
    while ((current = fgetc(input)) != EOF && current != '!') {
        switch (current) {
            case '+':
            case '-':
            case '<':
            case '>':
                if (q->last != NULL && q->last->opcode == current)
                    q->last->mod++;
                else
                    pushq(q, current, 1, NULL);
                break;
            case '#':
            case '%':
            case ',':
            case '.':
                pushq(q, current, 0, NULL);
                break;
            case '[':
                pushq(q, current, 0, NULL);
                pushs(s, q->last);
                break;
            case ']':
                if (s->first == NULL)
                    error(SYNTAX, "readInput");
                else {
                    pushq(q, current, 0, NULL);
                    temp = pops(s);
                    temp->ref = q->last;
                    q->last->ref = temp;
                }
                break;
            default:
                break;
        }
    }
    if (s->first != NULL) {
        dels(s);
        error(SYNTAX, "readInput");
    }
    dels(s);
    if (current == '!') {
        while ((current = fgetc(input)) != EOF && next_pos < MAXINPUT-1) { 
            input_string[next_pos++] = current;
        }
    }
}

void execute(Queue *source) {
    int ptr = 0;
    int input_char;
    char branch = 0;
    Token *current_token = NULL;
    uint16_t memory[MAXMEM] = {0};
    next_pos = 0;
    if (source == NULL)
        error(NO_CODE, "exec");
    current_token = source->first;
    while (current_token != NULL) {
        branch = 0;
        switch(current_token->opcode) {
            case '+':
                memory[ptr] += current_token->mod;
                break;
            case '-':
                memory[ptr] -= current_token->mod;
                break;
            case '>':
                ptr = (ptr + current_token->mod) % MAXMEM;
                break;
            case '<':
                ptr = (ptr - current_token->mod < 0) ?
                      (MAXMEM - (labs(ptr - current_token->mod) % MAXMEM)) :
                      ptr - current_token->mod;
                break;
            case ',':
                if (input_string[0] == '\0')
                    input_char = getchar();
                else if (next_pos < MAXINPUT-1)
                    input_char = input_string[next_pos++];
                else
                    error(INPUT, "execute");
                memory[ptr] = (input_char == EOF) ? 0 : input_char;
                break;
            case '.':
                putchar(memory[ptr]);
                break;
            case '[':
                if (memory[ptr] == 0) {
                    branch = 1;
                    current_token = current_token->ref->next;
                }
                break;
            case ']':
                if (memory[ptr] != 0) {
                    branch = 1;
                    current_token = current_token->ref->next;
                }
                break;
            case '#':
                memdisplay(memory);
                break;
            case '%':
                fprintf(stdout, "\n%d\n", ptr);
                break;
            default:
                break;
        }
        if (!branch)
            current_token = current_token->next;
    }
}

static void memdisplay(uint16_t *memory) {
    int i, j;
    int current;
    char ascii[13] = {0};
    ascii[0] = ascii[11] = '|';
    for (i=0; i < 10; i++) {
        fprintf(stdout, "\n%03d ", i*10);
        for (j=0; j < 10; j++) {
            current = memory[i*10+j];
            fprintf(stdout, "%5d ", current);
            ascii[j+1] = (current >= 32 && current <= 126) ? current : '.';
        }
        fprintf(stdout, "%s", ascii);
    }
    fprintf(stdout, "\n");
}

