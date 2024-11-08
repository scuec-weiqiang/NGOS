set disassemble-next-line on

b _start
b kernel.c:17
b entry.S:100
b entry.S:109
target remote :1234
c