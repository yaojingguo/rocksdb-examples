#include "stdio.h"

int main(int argc, char const *argv[]) {
  char c = 10;
  int *p = (int*) &c;
  *p = 5;
  
  return 0;
}