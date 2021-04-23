/* The bootloader will look at this image and start execution at the symbol
   designated at the entry point. */
ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 1M;
	kernel_base = 3<<30;
	
	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	. += kernel_base;
	kernel_start = .;

	.text ALIGN(4K) : AT(ADDR(.text) - kernel_base)
	{
	  KEEP(*(.multiboot))
		*(.text)
	}
	/* Read-only data. */
	.rodata ALIGN(4K) : AT(ADDR(.rodata) - kernel_base)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data ALIGN(4K) : AT(ADDR(.data) - kernel_base)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss ALIGN(4K) : AT(ADDR(.bss) - kernel_base)
	{
		*(COMMON)
		*(.bss)
	}
	.extra ALIGN(4K) : AT(ADDR(.bss) - kernel_base)
	{
		kernel_end = .;
	}
	/* The compiler may produce other sections, put them in the proper place in
	   in this file, if you'd like to include them in the final kernel. */
}
