#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include <capstone/capstone.h>

#ifndef LEN
#define LEN 0x13c
#endif

int main(void) {
  uint8_t buf[LEN];
  FILE *fd;
  csh handle;
  cs_insn *insn;
  size_t count;

  if (!(fd = fopen("cm002", "rb"))) {
    puts("error opening file cm002");
    return EXIT_FAILURE;
  }

  fseek(fd, 0xc000, SEEK_SET);
  fread(buf, 1, LEN, fd);

  fclose(fd);

  for (unsigned i = 0, j = 0x7fff74f1; i < LEN; i+=4) {
    *((unsigned *)(buf+i)) ^= j;
    j = (32 * j + 0x1505) | 0x1b0;
  }

  if (cs_open(CS_ARCH_X86, CS_MODE_64, &handle) != CS_ERR_OK) {
    puts("capstone initialization failed");
    return EXIT_FAILURE;
  }

  count = cs_disasm(handle, buf + 0x100, LEN - 0x100, 0x41100, 0x100, &insn);

  for (size_t i = 0; i < count; ++i) {
    printf("0x%0lx:\t%s\t\t%s\n", insn[i].address, insn[i].mnemonic,
        insn[i].op_str);
  }

  cs_free(insn, count);
  cs_close(&handle);

  if (!(fd = fopen("bytes", "wb"))) {
    puts("error opening file bytes");
    return EXIT_FAILURE;
  }

  fwrite(buf, 1, LEN, fd);
  fclose(fd);

  return EXIT_SUCCESS;
}
