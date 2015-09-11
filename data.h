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

#ifndef INC_DATA_H
#define INC_DATA_H

/*
 * Queue of tokens.
 */
typedef struct Token Token;
struct Token {
    int opcode;
    long mod;
    Token *next;
    Token *ref;
};

typedef struct Queue Queue;
struct Queue {
    Token *first;
    Token *last;
};

Queue *initq(void);
void pushq(Queue *, char, long, Token *);
void delq(Queue *);

/*
 * Temporary stack for unclosed references.
 */
typedef struct StackElem StackElem;
struct StackElem {
    Token *label;
    StackElem *next;
};

typedef struct Stack Stack;
struct Stack {
    StackElem *first;
};

Stack *inits();
void pushs(Stack *, Token *);
Token *pops(Stack *);
void dels(Stack *);

#endif /* INC_DATA_H */
