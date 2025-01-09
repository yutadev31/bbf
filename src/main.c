#include <stdio.h>
#include <stdlib.h>
#include <tokenaizer.h>
#include <parser.h>
#include <inst2bin.h>

#define N 256

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Error: Missing file name. Usage: %s <file_name>\n", argv[0]);
    return 1;
  }

  const char *file_name = argv[1];

  FILE *fp;
  fp = fopen(file_name, "r");
  if (fp == NULL)
  {
    printf("%s file not open!\n", file_name);
    return 1;
  }

  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  rewind(fp);

  char *code = (char *)malloc(file_size + 1);
  if (code == NULL)
  {
    printf("Error: Memory allocation failed.\n");
    fclose(fp);
    return 1;
  }

  size_t read_size = fread(code, 1, file_size, fp);
  code[read_size] = '\0';
  fclose(fp);

  Token *token = tokenize(code);

  free(code);

  Instruction *root = parse(token);

  unsigned char *bin = calloc(1, BIN_SIZE);
  unsigned char *memory = calloc(1, MEMORY_SIZE);
  int binIndex = 0;
  int pointer = 0;

  inst2bin(root, bin, &binIndex, memory, &pointer);

  FILE *output_fp;
  output_fp = fopen("output.bin", "w");
  if (output_fp == NULL)
  {
    printf("%s file not open!\n", file_name);
    return 1;
  }

  fwrite(bin, BIN_SIZE, 1, output_fp);
  fclose(output_fp);
}
