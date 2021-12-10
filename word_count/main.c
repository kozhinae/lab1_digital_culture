#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int line = 0, byte = 0, word = 0, word_state = 0, i;
    FILE *file = NULL;
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--lines") == 0) {
            line = 1;
        } else if (strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--bytes") == 0) {
            byte = 1;
        } else if (strcmp(argv[i], "-w") == 0 || strcmp(argv[i], "--words") == 0) {
            word = 1;
        } else {
            file = fopen(argv[i], "r");
        }
    }
    int c_lines = 1, c_bytes = 0, c_words = 0;
    char ch;
    while ((ch = (char) fgetc(file)) != EOF) {
        c_bytes++;
        if (ch == '\n') {
            c_lines++;
        }
        if ((ch == ' ' || ch == '\t' || ch == '\n') && word_state) {
            c_words++;
            word_state = 0;
        } else if (!(ch == ' ' || ch == '\t' || ch == '\n')) {
            word_state = 1;
        }
    }
    if (word_state) {
        c_words++;
    }
    if (line) {
        printf("Lines: %d\n", c_lines);
    }
    if (byte) {
        printf("Size: %d\n", c_bytes);
    }
    if (word) {
        printf("Words: %d\n", c_words);
    }
    return 0;
}