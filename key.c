#include <stdio.h>

#ifndef LEN
#define LEN 0xe
#endif

int main(void) {
    char s0[LEN], s1[LEN];
    FILE *fd;

    fd = fopen("code", "rb");

    fseek(fd, 0xe, SEEK_SET);
    fread(s0, 1, 8, fd);

    fseek(fd, 7, SEEK_CUR);
    fread(s0 + 8, 1, 4, fd);

    fseek(fd, 4, SEEK_CUR);
    fread(s0 + 0xc, 1, 2, fd);

    fseek(fd, 2, SEEK_CUR);
    fread(s1, 1, 8, fd);

    fseek(fd, 7, SEEK_CUR);
    fread(s1 + 8, 1, 4, fd);

    fseek(fd, 4, SEEK_CUR);
    fread(s1 + 0xc, 1, 2, fd);

    for (size_t i = 0; i < LEN; ++i) {
        putchar((s0[i] ^ s1[i]) & 0xff);
    }

    putchar(0xa);

    return 0;
}
