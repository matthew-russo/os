.section .text
.align 4

.global outb
.type outb, @function

outb:
  mov 8(%esp), %al # second param data
  mov 4(%esp), %dx # first param port
  outb %al, %dx


.global outw
.type outw, @function

outw:
  mov 8(%esp), %ax # second param data
  mov 4(%esp), %dx # first param port
  outw %ax, %dx


.global outl
.type outl, @function

outl:
  mov 8(%esp), %eax # second param data
  mov 4(%esp), %dx # first param port
  outl %eax, %dx


.global inb
.type inb, @function

inb:
  mov 4(%esp), %dx # first param port
  subl %eax, %eax # zero eax reg
  inb %dx
  ret


.global inw
.type inw, @function

inw:
  mov 4(%esp), %dx # first param port
  subl %eax, %eax # zero eax reg
  inw %dx
  ret


.global inl
.type inl, @function

inl:
  mov 4(%esp), %dx # first param port
  subl %eax, %eax # zero eax reg
  inl %dx
  ret
