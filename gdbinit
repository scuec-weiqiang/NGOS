set disassemble-next-line on
layout split
b _start
b kernel.c:26
target remote :1234
c