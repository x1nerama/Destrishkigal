#include <stdio.h>
#include <stdlib.h>
#include "utils/header.h"

int main(int argc, char *argv[]) {
  char buffer[200] = "/TRUN:";
  int num = strtol(argv[1], NULL, 10);
  generate_buffer(buffer, num);
	printf("%s\n", buffer);
  return 0;
}

