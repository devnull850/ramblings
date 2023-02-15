#include <stdio.h>

const unsigned short a[] = { 0x7b, 0x1c8, 0x315, 0x3db, 0x28e, 0x141 }; 
const unsigned short b[] = { 0x5c, 0x1d, 0x17c, 0x2, 0x1f1, 0x128 }; 

int main(void) {
    unsigned n, cnt;

    for (unsigned long i = 0; i < 0x100000000; ++i) {
        n = i & 0xffffffff;
        cnt = 0;

        for (unsigned j = 0; j < 6; ++j) {
            if (n % a[j] == b[j]) ++cnt;
        }

        if (cnt == 6) {
            printf("%u %d 0x%0x\n", n, n, n);
        }
    }

    return 0;
}
