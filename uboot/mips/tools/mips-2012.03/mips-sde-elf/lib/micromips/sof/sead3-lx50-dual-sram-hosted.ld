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
GROUP(-lcs3hal -lgcc -lc -lcs3 -lcs3hosted)

MEMORY
{
  ram (rwx) : ORIGIN = 0x80000000, LENGTH = 4M
  isram (rwx) : ORIGIN = 0x82000000, LENGTH = 64K
  dsram (rwx) : ORIGIN = 0x82020000, LENGTH = 64K
}

/* These force the linker to search for particular symbols from
 * the start of the link process and thus ensure the user's
 * overrides are picked up
 */
EXTERN(__cs3_reset __cs3_reset_sead3_lx50_dual_sram)
EXTERN(__cs3_start_asm _start)
EXTERN(__cs3_start_c main __cs3_stack __cs3_heap_end)
/* force exit to be picked up in a hosted or os environment */
EXTERN(exit atexit)
EXTERN(_cop1_init)
EXTERN(_mcleanup)
EXTERN(__cs3_initialize_args)

/* Provide fall-back values */
PROVIDE(__cs3_heap_start = _end);
PROVIDE(__cs3_heap_end = __cs3_region_start_dsram + __cs3_region_size_dsram);
PROVIDE(__cs3_region_num = (__cs3_regions_end - __cs3_regions) / 20);
/* Ensure that newlib runs the finalizers */
__libc_fini = _fini;
PROVIDE(__cs3_stack = __cs3_region_start_dsram + __cs3_region_size_dsram);
/* Provide a default value for the FP emulation mode */
PROVIDE(__cs3_mips_float_type = 0);

SECTIONS
{
  .text :
  {
    CREATE_OBJECT_SYMBOLS
    __cs3_region_start_isram = .;
    _ftext = .;
    *(.cs3.region-head.isram)
    ASSERT (. == __cs3_region_start_isram, ".cs3.region-head.isram not permitted");

    PROVIDE(__cs3_reset = __cs3_reset_sead3_lx50_dual_sram);
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
  } >isram
  .eh_frame_hdr : ALIGN (4)
  {
    KEEP (*(.eh_frame_hdr))
    *(.eh_frame_entry .eh_frame_entry.*)
  } >isram
  .eh_frame : ALIGN (4)
  {
    KEEP (*(.eh_frame)) *(.eh_frame.*)
  } >isram
  /* MDI semihosting uses a pointer in this section.  */
  /* .sdeosabi is ALLOC to keep it safe from stripping.  */
  /* We add KEEP here to foil --gc-sections.  */
  .sdeosabi : ALIGN (4)
  {
    KEEP(*(.sdeosabi))
  } >isram
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
    *(.isram)
    *(.isram.b .bss.isram)
    _etext = .;
  } >isram
  /* __cs3_region_end_isram is deprecated */
  __cs3_region_end_isram = __cs3_region_start_isram + LENGTH(isram);
  __cs3_region_size_isram = LENGTH(isram);
  __cs3_region_init_isram = LOADADDR (.text);
  __cs3_region_init_size_isram = _etext - ADDR (.text);
  __cs3_region_zero_size_isram = 0;

  .cs3.ram : ALIGN (8)
  {
    __cs3_region_start_ram = .;
    *(.cs3.region-head.ram)
    *(.ram)
    . = ALIGN (8);
  } >ram
  .cs3.ram.bss :
  {
    *(.ram.b .bss.ram)
    . = ALIGN (8);
  } >ram
  /* __cs3_region_end_ram is deprecated */
  __cs3_region_end_ram = __cs3_region_start_ram + LENGTH(ram);
  __cs3_region_size_ram = LENGTH(ram);
  __cs3_region_init_ram = LOADADDR (.cs3.ram);
  __cs3_region_init_size_ram = LOADADDR (.cs3.ram.bss) - LOADADDR (.cs3.ram);
  __cs3_region_zero_size_ram = SIZEOF(.cs3.ram.bss);

  .data : ALIGN (8)
  {
    __cs3_region_start_dsram = .;
    *(.cs3.region-head.dsram)
    *(.got.plt) *(.got)
    *(.shdata)
    *(.data .data.* .gnu.linkonce.d.*)
    . = ALIGN(8);
    _gp = . + 0x8000;
    *(.lit8)
    *(.lit4)
    *(.sdata .sdata.* .gnu.linkonce.s.*)
    . = ALIGN (8);
    *(.dsram)
    . = ALIGN (8);
    _edata = .;
  } >dsram
  .bss : ALIGN (8)
  {
    *(.sbss .sbss.* .gnu.linkonce.sb.*)
    *(.scommon)
    *(.shbss)
    *(.bss .bss.* .gnu.linkonce.b.*)
    *(COMMON)
    . = ALIGN (8);
    *(.dsram.b .bss.dsram)
    . = ALIGN (8);
    _end = .;
    __end = .;
  } >dsram
  /* __cs3_region_end_dsram is deprecated */
  __cs3_region_end_dsram = __cs3_region_start_dsram + LENGTH(dsram);
  __cs3_region_size_dsram = LENGTH(dsram);
  __cs3_region_init_dsram = LOADADDR (.data);
  __cs3_region_init_size_dsram = _edata - ADDR (.data);
  __cs3_region_zero_size_dsram = _end - _edata;

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
/* checksum: 6b48c3eb21d78a5b3694f */
