.set PAGEINDEXBITS, 10
.set PAGEBITS, 12
.set PAGEINDEX, 1<<PAGEINDEXBITS
.set PAGESIZE, 1<<PAGEBITS
.set PAGEFLAGWRITE, 1<<1
.set PAGEFLAGPRESENT, 1<<0

.section .bss
.global page_direct
.align PAGESIZE
page_direct:
.skip 4*PAGEINDEX

.global page_tables
.align PAGESIZE
page_tables:
.skip 4*PAGEINDEX*PAGEINDEX

.section .text
.global page_map
.type page_map, @function
.align 4
page_map:
  add $4, %esp
	pop %edi
	pop %esi
	pop %edx
	pop %ebx
	or %ebx, %esi
	add %edi, %edx
	shr $(PAGEBITS - 2), %edi
	shr $(PAGEBITS - 2), %edx
	mov %edi, %eax
	shr $PAGEINDEXBITS, %eax
	pop %ecx
	add %ecx, %eax
	pop %ecx
	add %ecx, %edi
	add %ecx, %edx
map_table:
	mov %edi, (%eax)
	or %ebx, (%eax)
	xor %ecx, %ecx
map_entry:
	mov %esi, (%edi)
	add $PAGESIZE, %esi
	add $4, %edi
	add $1, %ecx
	cmp %edx, %edi
	jge map_end
	cmp $PAGEINDEX, %ecx
	jl map_entry
	add $4, %eax
	jmp map_table
map_end:
	sub $28, %esp
  ret
.size page_map, . - page_map

.global page_unmap
.type page_unmap, @function
.align 4
page_unmap:
  add $4, %esp
	pop %edi
	pop %edx
	add %edi, %edx
	shr $(PAGEBITS - 2), %edi
	shr $(PAGEBITS - 2), %edx
	mov %edi, %eax
	shr $PAGEINDEXBITS, %eax
	pop %ecx
	add %ecx, %eax
	pop %ecx
	add %ecx, %edi
	add %ecx, %edx
unmap_table:
	mov $0, (%eax)
	xor %ecx, %ecx
unmap_entry:
	mov $0, (%edi)
	add $4, %edi
	add $1, %ecx
	cmp %edx, %edi
	jge unmap_end
	cmp $PAGEINDEX, %ecx
	jl unmap_entry
	add $4, %eax
	jmp unmap_table
unmap_end:
	sub $20, %esp
  ret
.size page_unmap, . - page_unmap
