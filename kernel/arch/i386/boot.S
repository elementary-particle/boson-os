# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot
.set STACKSIZE, 1<<14
.set KERNALPAGEFLAGS, 3         # PAGEFLAGPRESENT | PAGEFLAGWRITE

.set kernal_base, 3<<30

.macro physical vaddr
.set address, (\vaddr - kernal_base)
.endm

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip STACKSIZE # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	physical stack_top
	mov $address, %esp

# kernel->identity
  physical page_tables
  pushl $address
  physical page_direct
  pushl $address
	pushl $KERNALPAGEFLAGS
	physical kernel_end
	pushl $address
	pushl $0
	pushl $0
	call page_map
	
# kernel->kernel_base
  physical page_tables
  pushl $address
  physical page_direct
  pushl $address
	pushl $KERNALPAGEFLAGS
	physical kernel_end
	pushl $address
	pushl $0
	pushl $kernel_base
	call page_map
  
enable_page:
  physical page_direct
  mov $address, %eax
  mov %eax, %cr3
  
  mov %cr0, %eax
  or $0x80000001, %eax
  mov %eax, %cr0

  lea virtual, %ecx
  jmp *%ecx

virtual:
	pushl page_tables
	pushl page_direct
	physical kernel_end
	pushl $address
	pushl $0
	call page_unmap

	cli
	call segment_setup
	call interrupt_setup
	sti

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
.global kernal_abort
.type kernal_abort, @function
kernal_abort:
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
