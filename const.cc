#include <stdio.h>

int main() {
  const int myConst = 5;
  int* nonConst = const_cast<int*>(&myConst);
  *nonConst = 10;

  printf("myConst value: %d\n", myConst);
  printf("nonConst value: %ud\n", *nonConst);

  printf("myConst address: %p\n", &myConst);
  printf("nonConst address: %p\n", nonConst);
}
