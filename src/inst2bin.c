#include <stdlib.h>
#include <inst2bin.h>

void inst2bin(Instruction *root, unsigned char *bin, int *binIndex, unsigned char *memory, int *pointer)
{
  Instruction *inst = root->child;

  while (inst)
  {
    switch (inst->kind)
    {
    case IK_ROOT:
      exit(3);
    case IK_LOOP:
      while (memory[*pointer] != 0)
      {
        inst2bin(inst, bin, binIndex, memory, pointer);
      }
      break;
    case IK_LESS_THAN:
      (*pointer)--;
      break;
    case IK_GREATER_THAN:
      (*pointer)++;
      break;
    case IK_PLUS:
      memory[*pointer]++;
      break;
    case IK_MINUS:
      memory[*pointer]--;
      break;
    case IK_DOT:
      unsigned char data = memory[*pointer];
      bin[*binIndex] = data;
      (*binIndex)++;
      break;
    }

    inst = inst->next;
  }
}
