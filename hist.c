#include <stdio.h>
#include <string.h>

#ifndef LEN
#define LEN 0x27
#endif

const int ind[] = { 6, 23, 1, 21, 19, 32, 27, 30, 14, 19, 
                    30, 1, 8, 23, 11, 21, 20, 8, 34, 33, 
                    20, 10, 13, 7, 10, 16, 11, 7, 29, 36, 
                    21, 20, 33, 17, 27, 2, 35, 23, 29, 5, 
                    10, 25, 24, 30, 33, 14, 17, 21, 29, 2 };

int main(void) {
  int a[LEN];

  memset(a, 0, LEN * sizeof(int));

  for (unsigned i = 0; i < 0x32; ++i) {
    ++a[ind[i]];
  }

  for (unsigned i = 0; i < LEN; ++i) {
    printf("%u\t\t%d\n", i, a[i]);
  }

  return 0;
}
