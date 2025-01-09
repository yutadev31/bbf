#ifndef _H_PARSER_
#define _H_PARSER_

#include <tokenaizer.h>

typedef enum
{
  IK_ROOT,
  IK_LOOP,
  IK_LESS_THAN,
  IK_GREATER_THAN,
  IK_PLUS,
  IK_MINUS,
  IK_DOT,
} InstructionKind;

typedef struct _Instruction
{
  InstructionKind kind;
  struct _Instruction *child;
  struct _Instruction *next;
} Instruction;

extern Instruction *parse(Token *token);

#endif
