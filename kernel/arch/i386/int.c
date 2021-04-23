#include <stddef.h>
#include <stdint.h>

#include "desc.h"
#include "int.h"
#include "isr.h"

#define ATTR_P32INT (INT_32INTEGATE | INT_ATTR_PRES(1))

__attribute__ ((visibility("hidden")))
uint64_t interrupt_descriptor_table[0x100];

void interrupt_initialize() {
	interrupt_descriptor_table[0x00] = INT_DESC((uint32_t) isr_exception_de, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x01] = INT_DESC((uint32_t) isr_exception_db, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x03] = INT_DESC((uint32_t) isr_exception_bp, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x04] = INT_DESC((uint32_t) isr_exception_of, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x05] = INT_DESC((uint32_t) isr_exception_br, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x06] = INT_DESC((uint32_t) isr_exception_ud, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x07] = INT_DESC((uint32_t) isr_exception_nm, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x08] = INT_DESC((uint32_t) isr_exception_df, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x0a] = INT_DESC((uint32_t) isr_exception_ts, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x0b] = INT_DESC((uint32_t) isr_exception_np, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x0c] = INT_DESC((uint32_t) isr_exception_ss, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x0d] = INT_DESC((uint32_t) isr_exception_gp, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x0e] = INT_DESC((uint32_t) isr_exception_pf, SEL_PL0_CODE, ATTR_P32INT);
	interrupt_descriptor_table[0x21] = INT_DESC((uint32_t) isr_keyboard, SEL_PL0_CODE, ATTR_P32INT);
}
