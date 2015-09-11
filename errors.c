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
#include "errors.h"

void error(int code, const char *function) {
    fprintf(stderr, "%s: ", function);
    switch (code) {
        case MEMORY:
            fprintf(stderr, "Out of memory\n");
            break;
        case EMPTY_CODE:
            fprintf(stderr, "Empty queue\n");
            break;
        case EMPTY_REFLIST:
            fprintf(stderr, "Empty stack\n");
            break;
        case NO_CODE:
            fprintf(stderr, "Unitialized queue\n");
            break;
        case NO_REFLIST:
            fprintf(stderr, "Unitialized stack\n");
            break;
        case SYNTAX:
            fprintf(stderr, "Brackets don't match\n");
            break;
        case NO_FILE:
            fprintf(stderr, "File doesn't exist\n");
            break;
        case INPUT:
            fprintf(stderr, "Input string is too short\n");
        default:
            break;
    }
    exit(code);
}

void usage(void) {
    fprintf(stderr, "usage: bf [options] file\n");
    fprintf(stderr, "Options :\n");
    fprintf(stderr, "\t-h\tPrints a short help message.\n");
    fprintf(stderr, "\t-v\tDisplays version and license informations.\n");
    exit(1);
}


