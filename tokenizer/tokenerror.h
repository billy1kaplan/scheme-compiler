#ifndef _TOKENERROR
#define _TOKENERROR

#ifndef STR_ERR
#define STR_ERR "Unexpected end of file while processing String"
#endif

struct TokenError {
    char *message;
    char *detail;
};

typedef struct TokenError TokenError;

/* Initialize the error with a null message */
void initError(TokenError *error);

/* Set error detail to a given message */
void setDetail(TokenError *error, char *detail);

/* print out the error message */
void displayError(TokenError *error);

/* Clean up all memory allocated for the error */
void cleanupError(TokenError *error);

#endif
