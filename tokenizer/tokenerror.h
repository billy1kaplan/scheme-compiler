#ifndef _TOKENERROR
#define _TOKENERROR

#define STR_ERR "Unexpected end of file while processing String"
#define BOOL_ERR "Unexpected token while processing Boolean"

struct TokenError {
    char *message;
    char *detail;
};

typedef struct TokenError TokenError;

/* print out the error message */
void displayError(TokenError *error);

/* Clean up all memory allocated for the error */
void cleanupError(TokenError *error);

#endif
