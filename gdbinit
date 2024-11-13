set disassemble-next-line on

b _start
b _start.S:136
b kernel.c:30
b exception.c:62
target remote :1234
c