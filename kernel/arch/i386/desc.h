#ifndef _ARCH_I386_DESC_H
#define _ARCH_I386_DESC_H

extern void segment_setup();
extern void segment_flush();
extern void interrupt_setup();

#define DESC_SELE(e, g, p) (((e) << 3) | ((g) << 2) | (p))

#define SEL_PL0_CODE DESC_SELE(1, 0, 0)
#define SEL_PL0_DATA DESC_SELE(2, 0, 0)
#define SEL_PL3_CODE DESC_SELE(3, 0, 3)
#define SEL_PL3_DATA DESC_SELE(4, 0, 3)

#endif

