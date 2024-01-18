// commit message qemu@a8170e5e97 (target=0, prob=0.010393472, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void subpage_write(void *opaque, target_phys_addr_t addr,  // (4) 0.07292
/*2  */                           uint64_t value, unsigned len)           // (0) 0.1181
/*4  */ {                                                                 // (16) 0.003472
/*6  */     subpage_t *mmio = opaque;                                     // (9) 0.04514
/*8  */     unsigned int idx = SUBPAGE_IDX(addr);                         // (7) 0.05903
/*10 */     MemoryRegionSection *section;                                 // (13) 0.03125
/*12 */ #if defined(DEBUG_SUBPAGE)                                        // (11) 0.03819
/*14 */     printf("%s: subpage %p len %d addr " TARGET_FMT_plx           // (3) 0.08681
/*16 */            " idx %d value %"PRIx64"\n",                           // (2) 0.09028
/*18 */            __func__, mmio, len, addr, idx, value);                // (1) 0.09028
/*20 */ #endif                                                            // (14) 0.006944
/*24 */     section = &phys_sections[mmio->sub_section[idx]];             // (5) 0.07292
/*26 */     addr += mmio->base;                                           // (12) 0.03472
/*28 */     addr -= section->offset_within_address_space;                 // (8) 0.05208
/*30 */     addr += section->offset_within_region;                        // (10) 0.04514
/*32 */     io_mem_write(section->mr, addr, value, len);                  // (6) 0.06597
/*34 */ }                                                                 // (15) 0.003472
