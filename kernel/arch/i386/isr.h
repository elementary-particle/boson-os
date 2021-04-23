#ifndef ARCH_I386_ISR_H
#define ARCH_I386_ISR_H

#include <stdbool.h>

typedef struct frame_t {
	uint32_t eip;
	uint32_t cs;
} frame_t;

void isr_exception_de(frame_t *); // Divide Error
void isr_exception_db(frame_t *); // Debug Exception
void isr_exception_bp(frame_t *); // Breakpoint
void isr_exception_of(frame_t *); // Overflow
void isr_exception_br(frame_t *); // BOUND Range Exceeded
void isr_exception_ud(frame_t *); // Invalid Opcode (Undefined Opcode)
void isr_exception_nm(frame_t *); // Device Not Available (No Math Coprocessor)
void isr_exception_df(frame_t *, uint32_t code); // Double Fault
void isr_exception_ts(frame_t *, uint32_t code); // Invalid TSS
void isr_exception_np(frame_t *, uint32_t code); // Segment Not Present
void isr_exception_ss(frame_t *, uint32_t code); // Stack-Segment Fault
void isr_exception_gp(frame_t *, uint32_t code); // General Protection
void isr_exception_pf(frame_t *, uint32_t code); // Page Fault
void isr_keyboard(frame_t *); // Key IRQ 1 => INT 0x21

void isr_write_eoi_slave();
void isr_write_eoi();
uint8_t isr_read_key();
#endif
