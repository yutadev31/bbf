#include <stdio.h>
#include <parser.h>

void parse(Token *token)
{
  switch (token->kind)
  {
  case TK_LEFT_BRACKET:
  case TK_RIGHT_BRACKET:
    break;
  }

  token = token->next;
}
