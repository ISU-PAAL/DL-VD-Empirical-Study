// commit message qemu@a8170e5e97 (target=0, prob=0.014915602, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ int cpu_memory_rw_debug(CPUArchState *env, target_ulong addr,     // (6) 0.04953
/*2  */                         uint8_t *buf, int len, int is_write)      // (0) 0.08962
/*4  */ {                                                                 // (24) 0.002358
/*6  */     int l;                                                        // (21) 0.01415
/*8  */     target_phys_addr_t phys_addr;                                 // (12) 0.03302
/*10 */     target_ulong page;                                            // (19) 0.02123
/*14 */     while (len > 0) {                                             // (18) 0.02358
/*16 */         page = addr & TARGET_PAGE_MASK;                           // (7) 0.04717
/*18 */         phys_addr = cpu_get_phys_page_debug(env, page);           // (3) 0.05896
/*20 */         /* if no physical page mapped, return an error */         // (8) 0.04245
/*22 */         if (phys_addr == -1)                                      // (9) 0.03774
/*24 */             return -1;                                            // (10) 0.03538
/*26 */         l = (page + TARGET_PAGE_SIZE) - addr;                     // (5) 0.05425
/*28 */         if (l > len)                                              // (13) 0.03066
/*30 */             l = len;                                              // (11) 0.03538
/*32 */         phys_addr += (addr & ~TARGET_PAGE_MASK);                  // (4) 0.0566
/*34 */         if (is_write)                                             // (14) 0.03066
/*36 */             cpu_physical_memory_write_rom(phys_addr, buf, l);     // (2) 0.0684
/*38 */         else                                                      // (20) 0.01887
/*40 */             cpu_physical_memory_rw(phys_addr, buf, l, is_write);  // (1) 0.07311
/*42 */         len -= l;                                                 // (15) 0.02594
/*44 */         buf += l;                                                 // (16) 0.02594
/*46 */         addr += l;                                                // (17) 0.02594
/*48 */     }                                                             // (23) 0.009434
/*50 */     return 0;                                                     // (22) 0.01415
/*52 */ }                                                                 // (25) 0.002358
