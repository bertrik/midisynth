/**
 * Creates a table of step rates, one for each MIDI note.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include <math.h>

static int createtable(int fs, uint16_t table[])
{
    for (int i = 0; i < 128; i++) {
        double f = 440.0 * pow(2.0, (i - 69.0) / 12.0) / fs;
        table[i] = (int)round(f * 65536);
    }

    return 128;
}

static void writesource(const uint16_t table[], int len)
{
    printf("#include <stdint.h>\n\n");
    printf("static const uint16_t notestable[] {\n");

    const char *notes[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B"};
    printf("/*");
    for (int i = 0; i < 12; i++) {
        printf("%7s", notes[i]);
    }
    printf(" */");

    for (int i = 0; i < len; i++) {
        if ((i % 12) == 0) {
            printf("\n    ");
        }
        printf("%5d", table[i]);
        if (i < (len - 1)) {
            printf(", ");
        }
    }

    printf("\n};\n");
}

int main(int argc, char *argv[])
{
    uint16_t table[128];

    (void)argc;
    (void)argv;

    if (argc != 2) {
        fprintf(stderr, "Usage: gennotes <samplerate>\n");
        return -1;
    }

    int fs = atoi(argv[1]);
    int len = createtable(fs, table);
    writesource(table, len);

    return 0;
}

