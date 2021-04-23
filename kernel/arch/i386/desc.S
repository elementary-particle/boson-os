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

.section .data
gdtrecord:
.global global_descriptor_table
.word 8*5
# current gdt
# 0000000000000000
# 00cf9a000000ffff
# 00cf93000000ffff
# 00cffa000000ffff
# 00cff2000000ffff
.long global_descriptor_table

idt_record:
.global interrupt_descriptor_table
.word 8*0x100
.long interrupt_descriptor_table

.section .text
.global interrupt_setup
.type interrupt_setup, @function
interrupt_setup:
	outbyte $0x11, $PIC0_COMMAND
	outbyte $0x11, $PIC1_COMMAND
	outbyte $0x20, $PIC0_DATA
	outbyte $0x28, $PIC1_DATA
	outbyte $0x04, $PIC0_DATA
	outbyte $0x02, $PIC1_DATA
	outbyte $0x01, $PIC0_DATA
	outbyte $0x01, $PIC1_DATA
	outbyte $0xfd, $PIC0_DATA
	outbyte $0xff, $PIC1_DATA
	call interrupt_initialize
	mov $idt_record, %eax
	lidt (%eax)
	ret
.size interrupt_setup, . - interrupt_setup

.section .text
.global segment_setup
.type segment_setup, @function
segment_setup:
	mov $gdtrecord, %eax
	lgdt (%eax)
	jmp segment_flush
.size segment_setup, . - segment_setup

.global segment_flush
.type segment_flush, @function
segment_flush:
	ljmp $0x08,$reload_segdata
reload_segdata:
	mov $0x10, %eax
	mov %eax, %ds
	mov %eax, %es
	mov %eax, %fs
	mov %eax, %gs
	mov %eax, %ss
	ret
.size segment_flush, . - segment_flush
