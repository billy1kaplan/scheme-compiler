#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"
#include "tokenizer.h"
#include "token.h"
#include "tokenerror.h"
#include "vector.h"

bool isWhiteSpace(char c) {
  return c == ' '
    || c == '\t'
    || c == '\n'
    || c == '\v'
    || c == '\f'
    || c == '\r'
    || c == EOF;
}

bool isDigit(char c) {
  return c >= '0' && c <= '9';
}

char *vectorToString(Vector *buffer) {
  char *output = (char *)malloc((buffer->size + 1) * sizeof(char));
  for (int i = 0; i < buffer->size; i++) {
    output[i] = buffer->array[i];
  }
  output[buffer->size] = '\0';
  return output;
}

int vectorToInt(Vector *buffer) {
  char *stringRepr = vectorToString(buffer);
  int intRepr = atoi(stringRepr);
  free(stringRepr);
  return intRepr;
}

double vectorToDouble(Vector *buffer) {
  char *stringRepr = vectorToString(buffer);
  double doubleRepr = atof(stringRepr);
  free(stringRepr);
  return doubleRepr;
}

/*
  Converts our character vector buffer into a string token
  Returns a non-zero status code if the string is not terminated before
  reaching the end of the file
*/
int tokenizeString(Vector *buffer, LinkedList *tokens, LinkedList *errors) {
  char charRead = fgetc(stdin);
  while (charRead != EOF && charRead != '"') {
    append(buffer, charRead);
    charRead = fgetc(stdin);
  }

  int errno = 0;
  if (charRead == EOF) {
    TokenError *error = (TokenError *)malloc(sizeof(TokenError));
    error->message = STR_ERR;
    error->detail = vectorToString(buffer);
    appendTokenError(errors, error);
    errno = 1;
  } else {
    Token *stringToken = (Token *)malloc(sizeof(Token));
    stringToken->type = STR_TYPE;
    stringToken->s = vectorToString(buffer);
    appendToken(tokens, stringToken);
  }

  clear(buffer);
  return errno;
}

/* Converts our character vector buffer into a symbol token */
int tokenizeSymbol(Vector *buffer, LinkedList *tokens, LinkedList *error) {
  char charRead = fgetc(stdin);
  while (!isWhiteSpace(charRead)) {
    if (charRead == ')') {
      ungetc(charRead, stdin);
      break;
    } else {
      append(buffer, charRead);
      charRead = fgetc(stdin);
    }
  }

  Token *symbolToken = (Token *)malloc(sizeof(Token));
  symbolToken->type = SYMBOL_TYPE;
  symbolToken->s = vectorToString(buffer);
  appendToken(tokens, symbolToken);
  clear(buffer);
  return 0;
}

/*
  Converts our character vector buffer into a double token
  If a non-digit character appears, we assume that this is actually a
  symbol token.
*/
int tokenizeDouble(Vector *buffer, LinkedList *tokens, LinkedList *error) {
  char charRead = fgetc(stdin);
  while (!isWhiteSpace(charRead)) {
    append(buffer, charRead);
    if (isDigit(charRead)) {
      charRead = fgetc(stdin);
    } else if (charRead == ')') {
      ungetc(charRead, stdin);
      break;
    } else {
      return tokenizeSymbol(buffer, tokens, error);
    }
  }

  Token *doubleToken = (Token *)malloc(sizeof(Token));
  doubleToken->type = DOUBLE_TYPE;
  doubleToken->d = vectorToDouble(buffer);
  appendToken(tokens, doubleToken);
  clear(buffer);
  return 0;
}

/*
  Converts character vector buffer into a boolean
  Accepts #t or #f only, otherwise produces an error.
*/
int tokenizeBoolean(Vector *buffer, LinkedList *tokens, LinkedList *errors) {
  char charRead = fgetc(stdin);
  int errno = 0;
  if (charRead == 't') {
    appendToken(tokens, trueToken());
  } else if (charRead == 'f') {
    appendToken(tokens, falseToken());
  } else {
    while (!isWhiteSpace(charRead)) {
      append(buffer, charRead);
      charRead = fgetc(stdin);
    }

    TokenError *error = (TokenError *)malloc(sizeof(TokenError));
    error->message = BOOL_ERR;
    error->detail = vectorToString(buffer);
    appendTokenError(errors, error);
    errno = 1;
  }
  clear(buffer);
  return errno;
}

/*
  Converts character vector buffer into a number.

  This token could turn out to be either an integer or a double depending on the rest
  of the input. We could also produce a symbol token if the number contains multiple non-
  digit characters.
*/
int tokenizeNumber(Vector *buffer, LinkedList *tokens, LinkedList *errors) {
  char charRead = fgetc(stdin);
  while (!isWhiteSpace(charRead)) {
    append(buffer, charRead);
    if (isDigit(charRead)) {
      charRead = fgetc(stdin);
    } else if (charRead == '.') {
      return tokenizeDouble(buffer, tokens, errors);
    } else if (charRead == ')') {
      ungetc(charRead, stdin);
      break;
    } else {
      return tokenizeSymbol(buffer, tokens, errors);
    }
  }

  Token *intToken = (Token *)malloc(sizeof(Token));
  intToken->type = INT_TYPE;
  intToken->i = vectorToInt(buffer);
  appendToken(tokens, intToken);
  clear(buffer);

  return 0;
}

/* Ignores comments until reaching the next line or the end of the file */
void ignoreComment() {
  char charRead = fgetc(stdin);
  while (charRead != '\n' && charRead != '\r' && charRead != EOF) {
    charRead = fgetc(stdin);
  }
}

/* Handles tokenizing the minus character by either */
int handleMinus(Vector *buffer, LinkedList *tokens, LinkedList *errors) {
  char charRead = fgetc(stdin);
  append(buffer, charRead);

  charRead = fgetc(stdin);
  ungetc(charRead, stdin);
  if (isDigit(charRead)) {
    return tokenizeNumber(buffer, tokens, errors);
  } else {
    return tokenizeSymbol(buffer, tokens, errors);
  }
}

/* Dispatch token tokenizers based on the current input */
int dispatchTokenizer(LinkedList *tokens, LinkedList *errors) {
  Vector *buffer = (Vector *)malloc(sizeof(Vector));
  init(buffer, 8);

  int errno = 0;
  char charRead = fgetc(stdin);
  while (charRead != EOF) {
    if (isWhiteSpace(charRead)) {
    } else if (charRead == '-') {
      ungetc(charRead, stdin);
      errno |= handleMinus(buffer, tokens, errors);
    } else if (charRead == ';') {
      ignoreComment();
    } else if (charRead == '"') {
      errno |= tokenizeString(buffer, tokens, errors);
    } else if (charRead == '(') {
      appendToken(tokens, openToken());
    } else if (charRead == ')') {
      appendToken(tokens, closeToken());
    } else if (isDigit(charRead)) {
      ungetc(charRead, stdin);
      errno |= tokenizeNumber(buffer, tokens, errors);
    } else if (charRead == '#') {
      errno |= tokenizeBoolean(buffer, tokens, errors);
    } else {
      ungetc(charRead, stdin);
      errno |= tokenizeSymbol(buffer, tokens, errors);
    }

    charRead = fgetc(stdin);
  }

  cleanup(buffer);
  return errno;
}


/*
  Reads from stdin and produces a stream of tokens to stdout if the input stream is valid.
  Exits with a non-zero status code and prints to stderr if there is an issue while tokenizing.
*/
void tokenize() {
  LinkedList *tokens = (LinkedList *)malloc(sizeof(LinkedList));
  initLinkedList(tokens);

  LinkedList *errors = (LinkedList *)malloc(sizeof(LinkedList));
  initLinkedList(errors);

  int errno = dispatchTokenizer(tokens, errors);
  if (errno) {
    displayTokenErrors(errors);
  }  else {
    displayLinkedList(tokens);
  }

  cleanupLinkedList(tokens);
  cleanupErrorList(errors);

  exit(errno);
}
