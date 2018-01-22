#include <stdint.h>
#include <stdio.h>

int main(int argc, char const *argv[]) {
  uint16_t whole = 0x1122;
  uint8_t first_part = uint8_t(whole >> 8);
  uint8_t second_part = uint8_t(whole);
  printf("first part: %x, second part: %x\n", first_part, second_part);
  return 0;
}
