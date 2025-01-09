#include <stdio.h>
#include <stdlib.h>
#include <tokenaizer.h>
#include <parser.h>

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

  parse(token);
}
