.section .text
.align 4

.global _outb
.type _outb, @function

_outb:
  mov 8(%esp), %al # second param data
  mov 4(%esp), %dx # first param port
  outb %al, %dx

