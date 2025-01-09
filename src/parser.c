#include <stdio.h>
#include <stdlib.h>
#include <parser.h>

typedef struct
{
  Token *token;
  Instruction *cur;
} TokenAndCursor;

Instruction *createInstruction(InstructionKind kind)
{
  Instruction *inst = (Instruction *)calloc(1, sizeof(Instruction));
  inst->kind = kind;
  return inst;
}

Instruction *createInstructionAndSetNext(InstructionKind kind, Instruction *cur)
{
  Instruction *inst = createInstruction(kind);
  cur->next = inst;
  return inst;
}

extern TokenAndCursor *parseInLoop(Token *token, Instruction *cur);

TokenAndCursor *parseInstruction(Token *token, Instruction *cur)
{
  switch (token->kind)
  {
  case TK_RIGHT_BRACKET:
    exit(1);
  case TK_LEFT_BRACKET:
    TokenAndCursor *tac = parseInLoop(token, cur);
    cur = tac->cur;
    token = tac->token;
    free(tac);
    break;
  case TK_LESS_THAN:
    cur = createInstructionAndSetNext(IK_LESS_THAN, cur);
    break;
  case TK_GREATER_THAN:
    cur = createInstructionAndSetNext(IK_GREATER_THAN, cur);
    break;
  case TK_PLUS:
    cur = createInstructionAndSetNext(IK_PLUS, cur);
    break;
  case TK_MINUS:
    cur = createInstructionAndSetNext(IK_MINUS, cur);
    break;
  case TK_DOT:
    cur = createInstructionAndSetNext(IK_DOT, cur);
    break;
  }

  token = token->next;

  TokenAndCursor *tac = calloc(1, sizeof(TokenAndCursor));
  tac->cur = cur;
  tac->token = token;
  return tac;
}

TokenAndCursor *parseInLoop(Token *token, Instruction *cur)
{
  while (token)
  {
    if (token->kind == TK_RIGHT_BRACKET)
    {
      break;
    }
    else
    {
      TokenAndCursor *tac = parseInstruction(token, cur);
      cur = tac->cur;
      token = tac->token;
      free(tac);
    }
  }

  TokenAndCursor *tac = calloc(1, sizeof(TokenAndCursor));
  tac->cur = cur;
  tac->token = token;
  return tac;
}

Instruction *parse(Token *token)
{
  Instruction *root = createInstruction(IK_ROOT);
  Instruction first;
  Instruction *cur = &first;

  while (token)
  {
    TokenAndCursor *tac = parseInstruction(token, cur);
    cur = tac->cur;
    token = tac->token;
    free(tac);
  }

  root->child = first.next;

  return root;
}
