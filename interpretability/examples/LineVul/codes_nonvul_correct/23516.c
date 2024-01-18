// commit message qemu@a8170e5e97 (target=0, prob=0.0044103335, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t omap_mpui_io_read(void *opaque, target_phys_addr_t addr,  // (1) 0.1657
/*2  */                                   unsigned size)                          // (0) 0.2057
/*4  */ {                                                                         // (9) 0.005714
/*6  */     if (size != 2) {                                                      // (6) 0.05714
/*8  */         return omap_badwidth_read16(opaque, addr);                        // (2) 0.1257
/*10 */     }                                                                     // (8) 0.02286
/*14 */     if (addr == OMAP_MPUI_BASE)	/* CMR */                                 // (3) 0.1257
/*16 */         return 0xfe4d;                                                    // (4) 0.08
/*20 */     OMAP_BAD_REG(addr);                                                   // (5) 0.07429
/*22 */     return 0;                                                             // (7) 0.03429
/*24 */ }                                                                         // (10) 0.005714
