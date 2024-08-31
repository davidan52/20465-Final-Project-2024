#include "global.h"

/* Define the supported registers */
const char *REGISTERS[] = {
    "@r0", "@r1", "@r2", "@r3", "@r4", "@r5", "@r6", "@r7"
};

/* Define the number of supported registers */
const int REG_COUNT = sizeof(REGISTERS) / sizeof(REGISTERS[0]);
