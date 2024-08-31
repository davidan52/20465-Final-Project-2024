/*  parser.h */
#ifndef PARSER_H
#define PARSER_H

/*  Function to check if a line is empty or a comment */
int is_empty_or_comment(const char *line);

/*  Function to extract a label from the line */
char *extract_label(char *line);

/*  Function to parse instruction and operands */
void parse_instruction(char *line, char **instruction, char **operands);

#endif /*  PARSER_H */
