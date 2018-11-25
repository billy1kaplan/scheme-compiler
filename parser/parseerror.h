#ifndef _PARSEERROR
#define _PARSEERROR

#define OPEN_ERR "Unexpected open pair"
#define CLOSE_ERR "Too many closing parentheses"

struct ParseError {
  char *message;
  char *detail;
};

typedef struct ParseError ParseError;

/* print out the error message */
void displayError(ParseError *error);

/* Clean up all memory allocated for the error */
void cleanupError(ParseError *error);

#endif
