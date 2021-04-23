#ifndef ARCH_I386_PAGE_H
#define ARCH_I386_PAGE_H

// page.S
extern uint32_t page_direct[PAGE_INDEX_SIZE], page_tables[PAGE_INDEX_SIZE][PAGE_INDEX_SIZE];
extern void page_map(uint32_t virtual, uint32_t physical,
  uint32_t size, uint32_t flag, uint32_t page_direct[PAGE_INDEX_SIZE],
  uint32_t page_tables[PAGE_INDEX_SIZE][PAGE_INDEX_SIZE]);

#endif

