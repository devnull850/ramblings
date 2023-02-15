#include <stdio.h>

#ifndef LEN
#define LEN 0xc5
#endif

const unsigned val = 0x8000203d;

int main(void) {
    char buf[LEN], ch;
    unsigned n, checksum;
    FILE *fd;

    fd = fopen("hidden_password", "rb");

    fseek(fd, 0x11b5, SEEK_SET);

    for (unsigned i = 0; i < 0x10; i += 2) {
        fread(buf + i * 8, 1, 8, fd);
        fseek(fd, 2, SEEK_CUR);
        fread(buf + (i + 1) * 8, 1, 8, fd);
        fseek(fd, 0x10, SEEK_CUR);
    }

    for (unsigned i = 0; i < 8; i += 2) {
        fread(buf + (i + 0x10) * 8, 1, 8, fd);
        fseek(fd, 2, SEEK_CUR);
        fread(buf + (i + 1 + 0x10) * 8, 1, 8, fd);
        fseek(fd, 0xa, SEEK_CUR);
    }

    fseek(fd, 1, SEEK_CUR);
    fread(buf + 0xc0, 1, 4, fd);

    fseek(fd, 3, SEEK_CUR);
    fread(buf + 0xc4, 1, 1, fd);

    fclose(fd);

    n = val;
    checksum = 0;

    for (unsigned i = 0; i < LEN; ++i) {
        n *= 0x41c64e6d;
        n += 0x3039;

        ch = (n >> 0x10) & 0xff;
        buf[i] ^= ch;

        checksum = checksum + i * (buf[i] & 0xff);
    }

    if (checksum == 0x201b0f) {
        fd = fopen("code", "wb");
        fwrite(buf, 1, LEN, fd);
        fclose(fd);
    }

    return 0;
}
