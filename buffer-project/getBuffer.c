#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/header.h"

int main() {
  int size = 0; // `buffer` dizisinin boyutu
  char buffer[62];
  printf(">> ");
  scanf("%s", buffer);
  size_t len = strlen(buffer);
  generate_buffer(buffer, 32);
  printf("%s\n", buffer);
  return 0;
}