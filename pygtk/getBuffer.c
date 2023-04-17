#include <stdio.h>
#include <stdlib.h>
#include "utils/header.h"

int main(int argc, char *argv[]) {
  char buffer[200];
  int num = strtol(argv[1], NULL, 10);
  printf("%d\n", num);
  return 0;
}

