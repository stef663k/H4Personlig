/* Linker script for ATmega328PB */

MEMORY
{
  flash (rx) : ORIGIN = 0x0000, LENGTH = 32K  /* Flash memory for program code */
  eeprom (rw) : ORIGIN = 0x0000, LENGTH = 1K  /* EEPROM memory for persistent data */
  ram (rwx) : ORIGIN = 0x0100, LENGTH = 2K    /* RAM memory for data and stack */
}

SECTIONS
{
  .text :
  {
    *(.text)         /* Program code */
  } > flash

  .data :
  {
    *(.data)         /* Initialized data */
  } > ram

  .bss :
  {
    *(.bss)          /* Uninitialized data */
  } > ram

  /* Additional sections as needed */
}
