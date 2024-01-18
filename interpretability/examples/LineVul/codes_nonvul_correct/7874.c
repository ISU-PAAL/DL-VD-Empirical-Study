// commit message qemu@a8170e5e97 (target=0, prob=0.0052307714, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void mv88w8618_flashcfg_write(void *opaque, target_phys_addr_t offset,  // (1) 0.175
/*2  */                                      uint64_t value, unsigned size)            // (0) 0.2813
/*4  */ {                                                                              // (8) 0.00625
/*6  */     mv88w8618_flashcfg_state *s = opaque;                                      // (2) 0.1188
/*10 */     switch (offset) {                                                          // (6) 0.05
/*12 */     case MP_FLASHCFG_CFGR0:                                                    // (3) 0.09375
/*14 */         s->cfgr0 = value;                                                      // (4) 0.09375
/*16 */         break;                                                                 // (5) 0.05625
/*18 */     }                                                                          // (7) 0.025
/*20 */ }                                                                              // (9) 0.00625
