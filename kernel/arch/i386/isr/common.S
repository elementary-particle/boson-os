.set PCI_EOI, 0x20
.set PIC0, 0x20
.set PIC1, 0xA0
.set PIC0_COMMAND, PIC0
.set PIC1_COMMAND, PIC1
.set PIC0_DATA, (PIC0 + 1)
.set PIC1_DATA, (PIC1 + 1)

.macro outbyte byte dev 
mov \byte, %al
out %al, \dev
.endm

.section .text
.global isr_write_eoi_slave
.type isr_write_eoi_slave, @function
isr_write_eoi_slave:
	outbyte $PCI_EOI, $PIC1_COMMAND, 
	outbyte $PCI_EOI, $PIC0_COMMAND
	ret
.size isr_write_eoi_slave, . - isr_write_eoi_slave

.global isr_write_eoi
.type isr_write_eoi, @function
isr_write_eoi:
	outbyte $PCI_EOI, $PIC0_COMMAND 
	ret
.size isr_write_eoi, . - isr_write_eoi

.global isr_read_key
.type isr_read_key, @function
isr_read_key:
	outbyte $PCI_EOI, $PIC0_COMMAND
	outbyte $PCI_EOI, $0x61
	in $0x60, %al
	ret
.size isr_read_key, . - isr_read_key
