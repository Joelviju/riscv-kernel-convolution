OUTPUT_ARCH(riscv)
ENTRY(entry)

MEMORY
{
  RAM (rwx) : ORIGIN = 0x80000000, LENGTH = 128K
}

SECTIONS
{
  . = ORIGIN(RAM);
  .text : { *(.text*) }
  .rodata : { *(.rodata*) }
  .data : { *(.data*) }
  .bss : { *(.bss*) *(COMMON) }
  __sp = ORIGIN(RAM) + LENGTH(RAM);
}
