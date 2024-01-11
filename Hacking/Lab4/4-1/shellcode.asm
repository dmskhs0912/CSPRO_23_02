.text
.globl _start

_start:
    xor %rsi, %rsi
    mov $0x6020f0, %rsi
    callq *0x18(%rbp)
    retq
