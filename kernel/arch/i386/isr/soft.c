#include <stdint.h>

#include <kernel/tty.h>

#include "../isr.h"

void kernal_abort();

__attribute__((interrupt))
void isr_exception_de(frame_t *frame) {
	printf("Divide Error "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_db(frame_t *frame) {
	printf("Debug Exception "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_bp(frame_t *frame) {
	printf("Breakpoint "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_of(frame_t *frame) {
	printf("Overflow "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_br(frame_t *frame) {
	printf("BOUND Range Exceeded "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_ud(frame_t *frame) {
	printf("Invalid Opcode (Undefined Opcode) "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_nm(frame_t *frame) {
	printf("Device Not Available (No Math Coprocessor) "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_df(frame_t *frame, uint32_t code) {
	printf("Double Fault "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_ts(frame_t *frame, uint32_t code) {
	printf("Invalid TSS "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_np(frame_t *frame, uint32_t code) {
	printf("Segment Not Present "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_ss(frame_t *frame, uint32_t code) {
	printf("Stack-Segment Fault "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_gp(frame_t *frame, uint32_t code) {
	printf("General Protection "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}

__attribute__((interrupt))
void isr_exception_pf(frame_t *frame, uint32_t code) {
	printf("Page Fault "
		"/CS:%x/EIP:%x\n", frame->cs, frame->eip);
	kernal_abort();
}
