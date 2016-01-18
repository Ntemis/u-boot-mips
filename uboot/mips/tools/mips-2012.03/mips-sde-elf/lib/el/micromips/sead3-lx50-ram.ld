/* Linker script for MIPS SEAD-3 LX50
 *
 * Version: Sourcery CodeBench Lite 2012.03-64
 * Support: https://support.codesourcery.com/GNUToolchain/
 *
 * Copyright (c) 2007, 2008, 2009, 2010 CodeSourcery, Inc.
 *
 * The authors hereby grant permission to use, copy, modify, distribute,
 * and license this software and its documentation for any purpose, provided
 * that existing copyright notices are retained in all copies and that this
 * notice is included verbatim in any distributions.  No written agreement,
 * license, or royalty fee is required for any of the authorized uses.
 * Modifications to this software may be copyrighted by their authors
 * and need not follow the licensing terms described here, provided that
 * the new terms are clearly indicated on the first page of each file where
 * they apply.
 */
OUTPUT_ARCH(mips)
ENTRY(__cs3_reset)
SEARCH_DIR(.)
GROUP(-lcs3hal -lgcc -lc -lcs3 -lcs3unhosted)

MEMORY
{
  ram (rwx) : ORIGIN = 0x80000000 + 0x1000, LENGTH = 4M - 0x1000
  isram (rwx) : ORIGIN = 0x82000000, LENGTH = 64K
  dsram (rwx) : ORIGIN = 0x82020000, LENGTH = 64K
}

/* These force the linker to search for particular symbols from
 * the start of the link process and thus ensure the user's
 * overrides are picked up
 */
EXTERN(__cs3_reset __cs3_reset_sead3_lx50_ram)
EXTERN(__cs3_start_asm _start)
EXTERN(__cs3_start_c main __cs3_stack __cs3_heap_end)
EXTERN(_cop1_init)
EXTERN(_mcleanup)

/* Provide fall-back values */
PROVIDE(__cs3_heap_start = _end);
PROVIDE(__cs3_heap_end = __cs3_region_start_ram + __cs3_region_size_ram);
PROVIDE(__cs3_region_num = (__cs3_regions_end - __cs3_regions) / 20);
PROVIDE(__cs3_stack = __cs3_region_start_ram + __cs3_region_size_ram);
/* Provide a default value for the FP emulation mode */
PROVIDE(__cs3_mips_float_type = 0);

SECTIONS
{
  .text :
  {
    CREATE_OBJECT_SYMBOLS
    __cs3_region_start_ram = .;
    _ftext = .;
    *(.cs3.region-head.ram)
    ASSERT (. == __cs3_region_start_ram, ".cs3.region-head.ram not permitted");

    PROVIDE(__cs3_reset = __cs3_reset_sead3_lx50_ram);
    *(.cs3.reset)
    _start = DEFINED(__cs3_start_asm) ? __cs3_start_asm : _start;

    *(.text.cs3.init)
    *(.text .text.* .gnu.linkonce.t.*)

    . = ALIGN(0x4);
    KEEP (*crtbegin.o(.jcr))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .jcr))
    KEEP (*crtend.o(.jcr))

    . = ALIGN(0x4);
    *(.gcc_except_table .gcc_except_table.*)
    *(.gnu_extab .gnu_extab.*)
  } >ram
  .eh_frame_hdr : ALIGN (4)
  {
    KEEP (*(.eh_frame_hdr))
    *(.eh_frame_entry .eh_frame_entry.*)
  } >ram
  .eh_frame : ALIGN (4)
  {
    KEEP (*(.eh_frame)) *(.eh_frame.*)
  } >ram
  /* MDI semihosting uses a pointer in this section.  */
  /* .sdeosabi is ALLOC to keep it safe from stripping.  */
  /* We add KEEP here to foil --gc-sections.  */
  .sdeosabi : ALIGN (4)
  {
    KEEP(*(.sdeosabi))
  } >ram
  .rodata : ALIGN (4)
  {
    *(.rodata .rodata.* .gnu.linkonce.r.*)

    . = ALIGN(4);
    KEEP(*(.init))

    . = ALIGN(4);
    __preinit_array_start = .;
    KEEP (*(.preinit_array))
    __preinit_array_end = .;

    . = ALIGN(4);
    __init_array_start = .;
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array))
    __init_array_end = .;

    . = ALIGN(4);
    KEEP(*(.fini))

    . = ALIGN(4);
    __fini_array_start = .;
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    __fini_array_end = .;

    . = ALIGN(0x4);
    KEEP (*crtbegin.o(.ctors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*crtend.o(.ctors))

    . = ALIGN(0x4);
    KEEP (*crtbegin.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*crtend.o(.dtors))

    *(.lit)

    . = ALIGN(4);
    __cs3_regions = .;
    LONG (0)
    LONG (__cs3_region_init_ram)
    LONG (__cs3_region_start_ram)
    LONG (__cs3_region_init_size_ram)
    LONG (__cs3_region_zero_size_ram)
    LONG (0)
    LONG (__cs3_region_init_isram)
    LONG (__cs3_region_start_isram)
    LONG (__cs3_region_init_size_isram)
    LONG (__cs3_region_zero_size_isram)
    LONG (0)
    LONG (__cs3_region_init_dsram)
    LONG (__cs3_region_start_dsram)
    LONG (__cs3_region_init_size_dsram)
    LONG (__cs3_region_zero_size_dsram)
    __cs3_regions_end = .;
    . = ALIGN (8);
    _etext = .;
  } >ram

  .cs3.isram : ALIGN (8)
  {
    __cs3_region_start_isram = .;
    *(.cs3.region-head.isram)
    *(.isram)
    . = ALIGN (8);
  } >isram
  .cs3.isram.bss :
  {
    *(.isram.b .bss.isram)
    . = ALIGN (8);
  } >isram
  /* __cs3_region_end_isram is deprecated */
  __cs3_region_end_isram = __cs3_region_start_isram + LENGTH(isram);
  __cs3_region_size_isram = LENGTH(isram);
  __cs3_region_init_isram = LOADADDR (.cs3.isram);
  __cs3_region_init_size_isram = LOADADDR (.cs3.isram.bss) - LOADADDR (.cs3.isram);
  __cs3_region_zero_size_isram = SIZEOF(.cs3.isram.bss);

  .cs3.dsram : ALIGN (8)
  {
    __cs3_region_start_dsram = .;
    *(.cs3.region-head.dsram)
    *(.dsram)
    . = ALIGN (8);
  } >dsram
  .cs3.dsram.bss :
  {
    *(.dsram.b .bss.dsram)
    . = ALIGN (8);
  } >dsram
  /* __cs3_region_end_dsram is deprecated */
  __cs3_region_end_dsram = __cs3_region_start_dsram + LENGTH(dsram);
  __cs3_region_size_dsram = LENGTH(dsram);
  __cs3_region_init_dsram = LOADADDR (.cs3.dsram);
  __cs3_region_init_size_dsram = LOADADDR (.cs3.dsram.bss) - LOADADDR (.cs3.dsram);
  __cs3_region_zero_size_dsram = SIZEOF(.cs3.dsram.bss);

  .data : ALIGN (8)
  {
    *(.got.plt) *(.got)
    *(.shdata)
    *(.data .data.* .gnu.linkonce.d.*)
    . = ALIGN(8);
    _gp = . + 0x8000;
    *(.lit8)
    *(.lit4)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
    . = ALIGN (8);
    *(.ram)
    . = ALIGN (8);
    _edata = .;
  } >ram
  .bss : ALIGN (8)
  {
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
    *(.shbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN (8);
    *(.ram.b .bss.ram)
    . = ALIGN (8);
    _end = .;
    __end = .;
  } >ram
  /* __cs3_region_end_ram is deprecated */
  __cs3_region_end_ram = __cs3_region_start_ram + LENGTH(ram);
  __cs3_region_size_ram = LENGTH(ram);
  __cs3_region_init_ram = LOADADDR (.text);
  __cs3_region_init_size_ram = _edata - ADDR (.text);
  __cs3_region_zero_size_ram = _end - _edata;

  .stab 0 (NOLOAD) : { *(.stab) }
  .stabstr 0 (NOLOAD) : { *(.stabstr) }
  /* DWARF debug sections.
   * Symbols in the DWARF debugging sections are relative to
   * the beginning of the section so we begin them at 0.
   */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* DWARF 2.1 */
  .debug_ranges   0 : { *(.debug_ranges) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
}
/* checksum: 28488f1592455fb4504b0c3 */
