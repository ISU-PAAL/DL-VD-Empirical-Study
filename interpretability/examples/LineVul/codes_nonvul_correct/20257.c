// commit message qemu@a8170e5e97 (target=0, prob=0.0054088132, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static void gic_do_cpu_write(void *opaque, target_phys_addr_t addr,  // (1) 0.1773
/*2  */                              uint64_t value, unsigned size)          // (0) 0.2624
/*4  */ {                                                                    // (6) 0.007092
/*6  */     GICState **backref = (GICState **)opaque;                        // (2) 0.1348
/*8  */     GICState *s = *backref;                                          // (5) 0.0922
/*10 */     int id = (backref - s->backref);                                 // (4) 0.1064
/*12 */     gic_cpu_write(s, id, addr, value);                               // (3) 0.1277
/*14 */ }                                                                    // (7) 0.007092
