/**
 * Creates a table of step rates, one for each MIDI note.
 */

#include <stdio.h>
#include <stdint.h>

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
    printf("static const uint16_t notestable[] {");

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

    int len = createtable(32000, table);
    writesource(table, len);

    return 0;
}

