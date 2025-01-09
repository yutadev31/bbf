#include <stdio.h>
#include <stdlib.h>
#include <parser.h>

typedef struct
{
  Token *token;
  Instruction *cur;
} ParserResult;

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

extern ParserResult *parseInLoop(Token *token, Instruction *cur);

ParserResult *parseInstruction(Token *token, Instruction *cur)
{
  switch (token->kind)
  {
  case TK_RIGHT_BRACKET:
    break;
  case TK_LEFT_BRACKET:
    ParserResult *tac = parseInLoop(token, cur);
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

  ParserResult *result = calloc(1, sizeof(ParserResult));
  result->cur = cur;
  result->token = token;
  return result;
}

ParserResult *parseInLoop(Token *token, Instruction *cur)
{
  token = token->next;

  while (token)
  {
    if (token->kind == TK_RIGHT_BRACKET)
    {
      token = token->next;
      break;
    }
    else
    {
      ParserResult *result = parseInstruction(token, cur);
      cur = result->cur;
      token = result->token;
      free(result);
    }
  }

  ParserResult *result = calloc(1, sizeof(ParserResult));
  result->cur = cur;
  result->token = token;
  return result;
}

Instruction *parse(Token *token)
{
  Instruction *root = createInstruction(IK_ROOT);
  Instruction first;
  Instruction *cur = &first;

  while (token)
  {
    ParserResult *result = parseInstruction(token, cur);
    cur = result->cur;
    token = result->token;
    free(result);
  }

  root->child = first.next;

  return root;
}
