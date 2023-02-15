#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <capstone/capstone.h>

#ifndef LEN
#define LEN 0xc5
#endif

int main(void) {
    uint8_t buf[LEN];
    FILE *fd;

    csh handle;
    cs_insn *insn;
    size_t count;

    fd = fopen("code", "rb");
    fread(buf, 1, LEN, fd);
    fclose(fd);

    cs_open(CS_ARCH_X86, CS_MODE_64, &handle);
    cs_option(handle, CS_OPT_SYNTAX, CS_OPT_SYNTAX_ATT);

    count = cs_disasm(handle, buf, LEN, 0, 0, &insn);

    for (size_t i = 0; i < count; ++i) {
        printf("0x%0lx:\t%s\t\t%s\n", insn[i].address, insn[i].mnemonic,
                insn[i].op_str);
    }

    cs_free(insn, count);

    cs_close(&handle);

    return 0;
}
