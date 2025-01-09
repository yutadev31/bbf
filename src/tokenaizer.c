#include <stdio.h>
#include <stdlib.h>
#include <tokenaizer.h>

Token *createToken(TokenKind kind, Token *cur)
{
  Token *tk = (Token *)calloc(1, sizeof(Token));
  tk->kind = kind;
  cur->next = tk;
  return tk;
}

Token *tokenize(char *code)
{
  Token first;
  first.next = NULL;
  Token *cur = &first;

  char *p = code;
  while (*p)
  {
    switch (*p)
    {
    case ' ':
    case '\t':
    case '\n':
      break;
    case '<':
      cur = createToken(TK_LESS_THAN, cur);
      break;
    case '>':
      cur = createToken(TK_GREATER_THAN, cur);
      break;
    case '+':
      cur = createToken(TK_PLUS, cur);
      break;
    case '-':
      cur = createToken(TK_MINUS, cur);
      break;
    case '[':
      cur = createToken(TK_LEFT_BRACKET, cur);
      break;
    case ']':
      cur = createToken(TK_RIGHT_BRACKET, cur);
      break;
    case '.':
      cur = createToken(TK_DOT, cur);
      break;
    default:
      printf("Error: Invalid character '%c' found.\n", *p);
      exit(1);
    }
    p++;
  }

  return first.next;
}
