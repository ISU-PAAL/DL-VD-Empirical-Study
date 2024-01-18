// commit message qemu@149f54b53b (target=0, prob=0.010413866, correct=True): memory: add address_space_translate
/*0  */ static inline uint64_t ldq_phys_internal(hwaddr addr,                                   // (13) 0.0332
/*2  */                                          enum device_endian endian)                     // (0) 0.09375
/*4  */ {                                                                                       // (23) 0.001953
/*6  */     uint8_t *ptr;                                                                       // (17) 0.01953
/*8  */     uint64_t val;                                                                       // (19) 0.01758
/*10 */     MemoryRegionSection *section;                                                       // (18) 0.01758
/*14 */     section = phys_page_find(address_space_memory.dispatch, addr >> TARGET_PAGE_BITS);  // (3) 0.06055
/*18 */     if (!(memory_region_is_ram(section->mr) ||                                          // (12) 0.03711
/*20 */           memory_region_is_romd(section->mr))) {                                        // (8) 0.04492
/*22 */         /* I/O case */                                                                  // (15) 0.02539
/*24 */         addr = memory_region_section_addr(section, addr);                               // (11) 0.04102
/*28 */         /* XXX This is broken when device endian != cpu endian.                         // (10) 0.04102
/*30 */                Fix and add "endian" variable check */                                   // (7) 0.04687
/*32 */ #ifdef TARGET_WORDS_BIGENDIAN                                                           // (14) 0.02539
/*34 */         val = io_mem_read(section->mr, addr, 4) << 32;                                  // (5) 0.05078
/*36 */         val |= io_mem_read(section->mr, addr + 4, 4);                                   // (6) 0.05078
/*38 */ #else                                                                                   // (22) 0.003906
/*40 */         val = io_mem_read(section->mr, addr, 4);                                        // (9) 0.04492
/*42 */         val |= io_mem_read(section->mr, addr + 4, 4) << 32;                             // (4) 0.05664
/*44 */ #endif                                                                                  // (21) 0.003906
/*46 */     } else {                                                                            // (20) 0.01172
/*48 */         /* RAM case */                                                                  // (16) 0.02148
/*50 */         ptr = qemu_get_ram_ptr((memory_region_get_ram_addr(section->mr)                 // (2) 0.06445
/*52 */                                 & TARGET_PAGE_MASK)                                     // (1) 0.08008
/*54 */                                + memory_region_section_addr(section, addr));            // 0.0
/*56 */         switch (endian) {                                                               // 0.0
/*58 */         case DEVICE_LITTLE_ENDIAN:                                                      // 0.0
/*60 */             val = ldq_le_p(ptr);                                                        // 0.0
/*62 */             break;                                                                      // 0.0
/*64 */         case DEVICE_BIG_ENDIAN:                                                         // 0.0
/*66 */             val = ldq_be_p(ptr);                                                        // 0.0
/*68 */             break;                                                                      // 0.0
/*70 */         default:                                                                        // 0.0
/*72 */             val = ldq_p(ptr);                                                           // 0.0
/*74 */             break;                                                                      // 0.0
/*76 */         }                                                                               // 0.0
/*78 */     }                                                                                   // 0.0
/*80 */     return val;                                                                         // 0.0
/*82 */ }                                                                                       // 0.0
