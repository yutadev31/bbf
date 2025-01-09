#ifndef _H_TOKENIZER_
#define _H_TOKENIZER_

typedef enum
{
  TK_LESS_THAN,
  TK_GREATER_THAN,
  TK_PLUS,
  TK_MINUS,
  TK_DOT,
  TK_LEFT_BRACKET,
  TK_RIGHT_BRACKET,
  TK_END,
} TokenKind;

typedef struct _Token
{
  TokenKind kind;
  struct _Token *next;
} Token;

extern Token *tokenize(char *code);

#endif
