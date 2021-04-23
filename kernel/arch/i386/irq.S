.macro outbyte byte dev 
mov \byte, %al
out %al, \dev
.endm

.set PCI_EOI, 0x20
.set PIC0, 0x20
.set PIC1, 0xA0
.set PIC0_COMMAND, PIC0
.set PIC1_COMMAND, PIC1
.set PIC0_DATA, (PIC0 + 1)
.set PIC1_DATA, (PIC1 + 1)
