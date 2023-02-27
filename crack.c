#include <stdio.h>

#ifndef LEN
#define LEN 0x26
#endif

const int ind[] = { 6, 23, 1, 21, 19, 32, 27, 30, 14, 19, 
                    30, 1, 8, 23, 11, 21, 20, 8, 34, 33, 
                    20, 10, 13, 7, 10, 16, 11, 7, 29, 36, 
                    21, 20, 33, 17, 27, 2, 35, 23, 29, 5, 
                    10, 25, 24, 30, 33, 14, 17, 21, 29, 2 };

const int op[] = { 2, 2, 2, 3, 3, 3, 0, 1, 2, 3, 
                   2, 1, 2, 0, 1, 0, 1, 0, 1, 1, 
                   3, 2, 0, 3, 1, 3, 0, 3, 3, 0, 
                   1, 1, 0, 0, 0, 3, 1, 3, 3, 0, 
                   1, 1, 3, 3, 0, 0, 3, 2, 1, 2 };

int main(void) {
  char buf[LEN+1];
  unsigned n;
  FILE *fd;

  fd = fopen("crackme5.exe", "rb");
  fseek(fd, 0x1e040, SEEK_SET);
  fread(buf, 1, LEN+1, fd);
  fclose(fd);

  for (int i = 0; i < 0x32; ++i) {
    if (op[i] == 1) {
      n = buf[ind[i]] & 0xff;
      n ^= 0x2f;
      buf[ind[i]] = n & 0xff;
    }
    else if (op[i] <= 1) {
      if (!op[i]) {
        buf[ind[i]] += 1;
      }
    }
    else if (op[i] == 2) {
      n = buf[ind[i]] & 0xff;
      n -= 0x33;
      buf[ind[i]] = n & 0xff;
    }
    else if (op[i] == 3) {
      n = buf[ind[i]] & 0xff;
      n <<= 1;
      buf[ind[i]] = n & 0xff;
      buf[ind[i]] += 1;
    }
  }

  puts(buf);

  return 0;
}
