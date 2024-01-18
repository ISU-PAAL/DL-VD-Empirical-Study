// commit message qemu@149f54b53b (target=0, prob=0.009519105, correct=True): memory: add address_space_translate
/*0  */ void stl_phys_notdirty(hwaddr addr, uint32_t val)                                       // (15) 0.03711
/*2  */ {                                                                                       // (22) 0.001953
/*4  */     uint8_t *ptr;                                                                       // (18) 0.01953
/*6  */     MemoryRegionSection *section;                                                       // (19) 0.01758
/*10 */     section = phys_page_find(address_space_memory.dispatch, addr >> TARGET_PAGE_BITS);  // (2) 0.06055
/*14 */     if (!memory_region_is_ram(section->mr) || section->readonly) {                      // (7) 0.04687
/*16 */         addr = memory_region_section_addr(section, addr);                               // (12) 0.04102
/*18 */         if (memory_region_is_ram(section->mr)) {                                        // (11) 0.04297
/*20 */             section = &phys_sections[phys_section_rom];                                 // (6) 0.04687
/*22 */         }                                                                               // (20) 0.01562
/*24 */         io_mem_write(section->mr, addr, val, 4);                                        // (9) 0.04492
/*26 */     } else {                                                                            // (21) 0.01172
/*28 */         unsigned long addr1 = (memory_region_get_ram_addr(section->mr)                  // (5) 0.05273
/*30 */                                & TARGET_PAGE_MASK)                                      // (0) 0.07812
/*32 */             + memory_region_section_addr(section, addr);                                // (8) 0.04687
/*34 */         ptr = qemu_get_ram_ptr(addr1);                                                  // (10) 0.04297
/*36 */         stl_p(ptr, val);                                                                // (17) 0.03125
/*40 */         if (unlikely(in_migration)) {                                                   // (16) 0.03516
/*42 */             if (!cpu_physical_memory_is_dirty(addr1)) {                                 // (3) 0.05273
/*44 */                 /* invalidate code */                                                   // (13) 0.03906
/*46 */                 tb_invalidate_phys_page_range(addr1, addr1 + 4, 0);                     // (1) 0.07422
/*48 */                 /* set dirty bit */                                                     // (14) 0.03906
/*50 */                 cpu_physical_memory_set_dirty_flags(                                    // (4) 0.05273
/*52 */                     addr1, (0xff & ~CODE_DIRTY_FLAG));                                  // 0.0
/*54 */             }                                                                           // 0.0
/*56 */         }                                                                               // 0.0
/*58 */     }                                                                                   // 0.0
/*60 */ }                                                                                       // 0.0
