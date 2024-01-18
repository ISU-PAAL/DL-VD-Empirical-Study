// commit message qemu@149f54b53b (target=0, prob=0.008153202, correct=True): memory: add address_space_translate
/*0  */ static inline void stw_phys_internal(hwaddr addr, uint32_t val,                         // (12) 0.03906
/*2  */                                      enum device_endian endian)                         // (0) 0.08594
/*4  */ {                                                                                       // (26) 0.001953
/*6  */     uint8_t *ptr;                                                                       // (18) 0.01953
/*8  */     MemoryRegionSection *section;                                                       // (19) 0.01758
/*12 */     section = phys_page_find(address_space_memory.dispatch, addr >> TARGET_PAGE_BITS);  // (2) 0.06055
/*16 */     if (!memory_region_is_ram(section->mr) || section->readonly) {                      // (4) 0.04687
/*18 */         addr = memory_region_section_addr(section, addr);                               // (11) 0.04102
/*20 */         if (memory_region_is_ram(section->mr)) {                                        // (9) 0.04297
/*22 */             section = &phys_sections[phys_section_rom];                                 // (3) 0.04688
/*24 */         }                                                                               // (20) 0.01563
/*26 */ #if defined(TARGET_WORDS_BIGENDIAN)                                                     // (15) 0.0293
/*28 */         if (endian == DEVICE_LITTLE_ENDIAN) {                                           // (7) 0.04492
/*30 */             val = bswap16(val);                                                         // (14) 0.03906
/*32 */         }                                                                               // (22) 0.01562
/*34 */ #else                                                                                   // (25) 0.003906
/*36 */         if (endian == DEVICE_BIG_ENDIAN) {                                              // (10) 0.04297
/*38 */             val = bswap16(val);                                                         // (13) 0.03906
/*40 */         }                                                                               // (21) 0.01562
/*42 */ #endif                                                                                  // (24) 0.003906
/*44 */         io_mem_write(section->mr, addr, val, 2);                                        // (6) 0.04492
/*46 */     } else {                                                                            // (23) 0.01172
/*48 */         unsigned long addr1;                                                            // (16) 0.02344
/*50 */         addr1 = (memory_region_get_ram_addr(section->mr) & TARGET_PAGE_MASK)            // (1) 0.06836
/*52 */             + memory_region_section_addr(section, addr);                                // (5) 0.04687
/*54 */         /* RAM case */                                                                  // (17) 0.02148
/*56 */         ptr = qemu_get_ram_ptr(addr1);                                                  // (8) 0.04297
/*58 */         switch (endian) {                                                               // 0.0
/*60 */         case DEVICE_LITTLE_ENDIAN:                                                      // 0.0
/*62 */             stw_le_p(ptr, val);                                                         // 0.0
/*64 */             break;                                                                      // 0.0
/*66 */         case DEVICE_BIG_ENDIAN:                                                         // 0.0
/*68 */             stw_be_p(ptr, val);                                                         // 0.0
/*70 */             break;                                                                      // 0.0
/*72 */         default:                                                                        // 0.0
/*74 */             stw_p(ptr, val);                                                            // 0.0
/*76 */             break;                                                                      // 0.0
/*78 */         }                                                                               // 0.0
/*80 */         invalidate_and_set_dirty(addr1, 2);                                             // 0.0
/*82 */     }                                                                                   // 0.0
/*84 */ }                                                                                       // 0.0
