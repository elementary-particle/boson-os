#include <stddef.h>
#include <stdint.h>

#include "seg.h"

#define GDT_CODE_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_CODE_EXRD

#define GDT_DATA_PL0 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(0)     | SEG_DATA_RDWR

#define GDT_CODE_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_CODE_EXRD

#define GDT_DATA_PL3 SEG_DESCTYPE(1) | SEG_PRES(1) | SEG_SAVL(0) | \
                     SEG_LONG(0)     | SEG_SIZE(1) | SEG_GRAN(1) | \
                     SEG_PRIV(3)     | SEG_DATA_RDWR

__attribute__ ((visibility("hidden")))
uint64_t global_descriptor_table[] = {
  SEG_DESC(0, 0, 0),
  SEG_DESC(0x00000000, 0x000FFFFF, (GDT_CODE_PL0)),
  SEG_DESC(0x00000000, 0x000FFFFF, (GDT_DATA_PL0)),
  SEG_DESC(0x00000000, 0x000FFFFF, (GDT_CODE_PL3)),
  SEG_DESC(0x00000000, 0x000FFFFF, (GDT_DATA_PL3)),
};
