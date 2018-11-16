#include "tokenerror.h"

#include <stdio.h>
#include <stdlib.h>

void initError(TokenError *error) {
    error->message = "";
    error->detail = (char *)malloc(sizeof(char));
    error->detail[0] = '\0';
}

void setDetail(TokenError *error, char *detail) {
    free(error->detail);
    error->detail = detail;
}

void displayError(TokenError *error) {
    fprintf(stderr, "%s: %s", error->message, error->detail);
}

void cleanupError(TokenError *error) {
    free(error->detail);
    free(error);
}
