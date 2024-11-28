set disassemble-next-line on
layout split
b _start
b sched.c:89
b user.c:15
b user.c:30
b user.c:24
b isr.c:94
target remote :1234
c