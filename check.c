#include <stdio.h>

#ifndef LEN
#define LEN 0x190
#endif

extern void checksum(char, void *, void *);

int main(void) {
  char buf[LEN];
  unsigned x, y;
  FILE *fd;

  fd = fopen("crackme5.exe", "rb");
  fseek(fd, 0x860, SEEK_SET);
  fread(buf, 1, LEN, fd);
  fclose(fd);

  x = 0;
  y = 0;

  for (unsigned i = 0x30; i < LEN; ++i) {
    checksum(buf[i], &x, &y); 
  }

  printf("0x%0x\t\t0x%0x\n", x, y);

  return 0;
}
