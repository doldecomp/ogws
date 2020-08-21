ENTRY(__start)
_SDA_BASE_ = 0x804C5380;
_SDA2_BASE_ = 0x804C7A20;
PHDRS
{
    text0 PT_LOAD;
    text1 PT_LOAD;
    data0 PT_LOAD;
    data1 PT_LOAD;
    data2 PT_LOAD;
    data3 PT_LOAD;
    data4 PT_LOAD;
    data5 PT_LOAD;
    data6 PT_LOAD;
    data7 PT_LOAD;
    data8 PT_LOAD;
    bss PT_LOAD;
}
SECTIONS
{
    .text0 0x80004000 : { *(.text0) } : text0
    .text1 0x800076E0 : { *(.text1) } : text1
    .data0 0x800064E0 : { *(.data0) } : data0
    .data1 0x80006C20 : { *(.data1) } : data1
    .data2 0x80355080 : { *(.data2) } : data2
    .data3 0x80355260 : { *(.data3) } : data3
    .data4 0x80355280 : { *(.data4) } : data4
    .data5 0x80375780 : { *(.data5) } : data5
    .data6 0x80393A80 : { *(.data6) } : data6
    .data7 0x804BD380 : { *(.data7) } : data7
    .data8 0x804BFA20 : { *(.data8) } : data8
    .bss 0x803CAF00 (NOLOAD) : { *(.bss) } : bss
}
