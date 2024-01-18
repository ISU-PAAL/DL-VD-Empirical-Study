// commit message qemu@a8170e5e97 (target=0, prob=0.007090135, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void lsi_ram_write(void *opaque, target_phys_addr_t addr,  // (1) 0.1122
/*2  */                           uint64_t val, unsigned size)            // (0) 0.1659
/*4  */ {                                                                 // (12) 0.004878
/*6  */     LSIState *s = opaque;                                         // (7) 0.05366
/*8  */     uint32_t newval;                                              // (9) 0.04878
/*10 */     uint32_t mask;                                                // (10) 0.0439
/*12 */     int shift;                                                    // (11) 0.02927
/*16 */     newval = s->script_ram[addr >> 2];                            // (4) 0.07805
/*18 */     shift = (addr & 3) * 8;                                       // (5) 0.06341
/*20 */     mask = ((uint64_t)1 << (size * 8)) - 1;                       // (2) 0.1024
/*22 */     newval &= ~(mask << shift);                                   // (6) 0.06341
/*24 */     newval |= val << shift;                                       // (8) 0.05366
/*26 */     s->script_ram[addr >> 2] = newval;                            // (3) 0.08293
/*28 */ }                                                                 // (13) 0.004878
