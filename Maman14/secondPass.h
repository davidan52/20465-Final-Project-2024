/*  second_pass.h */
#ifndef SECOND_PASS_H
#define SECOND_PASS_H

/*  Main function for the second pass */
void second_pass(FILE *inputFile);

/*  Function to parse a line during the second pass */
void parse_line_second_pass(char *line, int lineNumber);

#endif /*  SECOND_PASS_H */
