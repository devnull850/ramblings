#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <capstone/capstone.h>

#ifndef LEN
#define LEN 2
#endif

int main(void) {
  uint8_t code[LEN];
  csh handle;
  cs_insn *insn;
  size_t count;

  code[0] = 0xd1;

  cs_open(CS_ARCH_X86, CS_MODE_32, &handle);

  for (size_t i = 0; i < 0x100; ++i) {
    code[1] = i & 0xff;

    count = cs_disasm(handle, code, LEN, 0, 0, &insn);

    for (size_t j = 0; j < count; ++j) {
      printf("0x%0lx\t0x%02x 0x%02x\t\t%s\t%s\n", i, code[0], code[1],
          insn[j].mnemonic, insn[j].op_str);
    }

    cs_free(insn, count);
  }

  cs_close(&handle);

  return EXIT_SUCCESS;
}
