set disassemble-next-line on

b _start
b start.S:97
b kernel.c:30
b exception.c:62
b isr.c:83
target remote :1234
c