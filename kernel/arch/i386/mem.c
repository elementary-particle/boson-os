#define PAGE_BITS 12
#define PAGE_INDEX_BITS 10
#define PAGE_SIZE (1 << PAGE_BITS)
#define PAGE_INDEX_SIZE (1 << PAGE_INDEX_BITS)
#define PAGE_READWRITE(x) ((x) << 1)
#define PAGE_PRESENT(x) ((x) << 0)

#include <stddef.h>
#include <stdint.h>

#include <kernel/mem.h>

#include "seg.h"
#include "page.h"

int32_t memory_initialize() {
  return 0;
}
