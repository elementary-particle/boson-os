#ifndef _ARCH_I386_INT_H
#define _ARCH_I386_INT_H

#define INT_ATTR_GATE(x)    ((x) << 0x00) // Gate Type
#define INT_ATTR_STOR(x)    ((x) << 0x04) // Storage Segment
#define INT_ATTR_PRIV(x)    ((x) << 0x05) // Descriptor Privilege Level
#define INT_ATTR_PRES(x)    ((x) << 0x07) // Present

#define INT_32TASKGATE 0x5
#define INT_16INTEGATE 0x6
#define INT_16TRAPGATE 0x7
#define INT_32INTEGATE 0xE
#define INT_32TRAPGATE 0xF

#define INT_DESC(o, s, t) (((0x0000FFFF & ((o) << 0 )) |\
                            (0xFFFF0000 & ((s) << 16)) ) |\
                           (uint64_t)\
                           ((0x000000FF & ((0) << 0 )) |\
                            (0x0000FF00 & ((t) << 8 )) |\
                            (0xFFFF0000 & ((o) << 0 )) ) << 32)

extern uint64_t interrupt_descriptor_table[0x100];
void interrupt_initialize();

#endif
