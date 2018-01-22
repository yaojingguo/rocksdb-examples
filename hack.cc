#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char *argv[]) {
  char* ptr = (char*) malloc(100);
  assert(ptr != NULL);

  ptr[0] = 'A';
  ptr[1] = 'B';
  ptr[2] = 'C';
  ptr[3] = '\0';

  printf("ptr: %s\n", ptr);

  free(ptr);
  return 0;
}
