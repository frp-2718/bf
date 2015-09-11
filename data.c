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
#include "data.h"
#include "errors.h"

Queue *initq() {
    Queue *q = malloc(sizeof(*q));
    if (q == NULL)
        error(MEMORY, "initq");
    q->first = NULL;
    q->last = NULL;
    return q;
}

void pushq(Queue *q, char opcode, long mod, Token *loop) {
    Token *new = malloc(sizeof(*new));
    if (q == NULL)
        error(NO_CODE, "pushq");
    else if (new == NULL)
        error(MEMORY, "pushq");
    new->opcode = opcode;
    new->mod = mod;
    new->next = NULL;
    new->ref = loop;
    if (q->first == NULL)
        q->first = new;
    if (q->last != NULL)
        q->last->next = new;
    q->last = new;
}

void delq(Queue *q) {
    if (q != NULL) {
        Token *current = q->first;
        Token *remainder = NULL;
        while (current != NULL) {
            remainder = current;
            current = current->next;
            free(remainder);
        }
        free(q);
    }
}

Stack *inits() {
    Stack *s = malloc(sizeof(*s));
    if (s == NULL)
        error(MEMORY, "inits");
    s->first = NULL;
    return s;
}

void pushs(Stack *s, Token* l) {
    StackElem *new = malloc(sizeof(*new));
    if (s == NULL)
        error(NO_REFLIST, "pushs");
    else if (new == NULL)
        error(MEMORY, "pushs");
    new->next = s->first;
    new->label = l;
    s->first = new;
}

Token *pops(Stack *s) {
    StackElem *old;
    Token *result;
    if (s == NULL)
        error(NO_REFLIST, "pops");
    result = s->first->label;
    old = s->first;
    s->first = s->first->next;
    free(old);
    return result;
}

void dels(Stack *s) {
    StackElem *current = s->first;
    StackElem *remainder = NULL;
    while (current != NULL) {
        remainder = current;
        current = current->next;
        free(remainder);
    }
    free(s);
}

