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
#include <unistd.h>
#include <stdint.h>
#include "data.h"
#include "interpreter.h"
#include "errors.h"

#define VERSION "1.1"
#define AUTHOR  "frp <_frp@outlook.com>"
#define YEAR "2013"

int main(int argc, char *argv[]) {
    FILE* input = NULL;
    Queue *source = initq();
    int option;
    while ((option = getopt(argc, argv, "hv")) != EOF) {
        switch (option) {
            case 'h':
                usage();
                break;
            case 'v':
                printf("bf version %s\nCopyright (c) %s, %s\nX11 license\n", VERSION, YEAR, AUTHOR);
                exit(0);
                break;
            default:
                usage();
                break;
        }
    }
    if (argv[optind] == NULL)
        usage();
    else if ((input = fopen(argv[1], "r")) == NULL) {
        error(NO_FILE, "main");
    } else {
        readInput(input, source);
        fclose(input);
        execute(source);
        delq(source);
    }
    return 0;
}

