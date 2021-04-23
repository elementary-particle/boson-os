#include <stdint.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/mem.h>
extern uint64_t global_descriptor_table[], interrupt_descriptor_table[];
uint32_t *table;

void kernel_main(void) {
	uint32_t i, u;
	terminal_initialize();
	memory_initialize();
	table = (uint32_t *) global_descriptor_table;
	printf("GDT@%x\n", global_descriptor_table);
	for(i = 0; i < 5; i++) {
	  printf("%x%x\n", table[(i << 1) | 1], table[(i << 1)]);
	}
	table = (uint32_t *) interrupt_descriptor_table;
	printf("IDT@%x\n", interrupt_descriptor_table);
	for(i = 0; i < 0x10; i++) {
	  printf("%x%x\n", table[(i << 1) | 1], table[(i << 1)]);
	}
	// asm("idiv %0": : "b"(0): );
	while(1) {
		asm("hlt");
  }
}

