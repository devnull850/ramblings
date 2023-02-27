#include <stdio.h>

#ifndef LEN
#define LEN 0x32
#endif

int main(void) {
  char buf[LEN];
  FILE *fd;

  fd = fopen("crackme5.exe", "rb");
  fseek(fd, 0x1e00c, SEEK_SET);
  fread(buf, 1, LEN, fd);
  fclose(fd);

  for (unsigned i = 0; i < LEN; ++i) {
    printf("%d, ", buf[i] - 0x30);
    if (i % 0xa == 9) putchar(0xa);
  }

  return 0;
}
