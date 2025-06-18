#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textlcd.h"

void print_help() {
    printf("Usage:\n");
    printf("  textlcdtest <lineNum> <string>\n");
    printf("    lineNum: 1 or 2\n");
    printf("    string : text to display on the line\n");
    printf("Examples:\n");
    printf("  textlcdtest 1 HelloWorld\n");
    printf("  textlcdtest 2 'Embedded Linux'\n");
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        print_help();
        return -1;
    }

    int lineNum = atoi(argv[1]);
    const char* text = argv[2];

    if (lineNum == 1) {
        lcdTextWrite(text, "", CMD_DATA_WRITE_LINE_1);
    } else if (lineNum == 2) {
        lcdTextWrite("", text, CMD_DATA_WRITE_LINE_2);
    } else {
        printf("Invalid line number. Use 1 or 2.\n");
        return -1;
    }

    return 0;
}
