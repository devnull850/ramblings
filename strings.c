#include <stdio.h>

#ifndef LEN
#define LEN 0x26
#endif

int main(void) {
  char buf[LEN];
  FILE *fd;

  fd = fopen("crackme5.exe", "rb");
  fseek(fd, 0xbf3, SEEK_SET);

  for (unsigned i = 0; i < LEN; ++i) {
    fseek(fd, 3, SEEK_CUR);
    buf[i] = fgetc(fd);
    if (buf[i]) buf[i] ^= 0x22;
  }

  fclose(fd);

  for (unsigned i = 0; i < LEN; ++i) {
    if (buf[i]) {
      putchar(buf[i]);
    }
  }

  putchar(0xa);

  return 0;
}
