#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char CHARSET[] = "0123456789ABCDEFGHIJKLMNOPQRSTU"
                       "VWXYZabcdefghijklmnopqrstuvwxyz";

unsigned a[] = { 0x4344484a, 0x4444224d, 0x202f };

int main(void) {
  srand(time(NULL));
  *((char *)(a+2)) = CHARSET[rand() % 0x3a];
  puts((char *)a);
  return 0;
}
