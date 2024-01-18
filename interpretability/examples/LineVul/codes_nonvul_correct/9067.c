// commit message qemu@a8170e5e97 (target=0, prob=0.004624533, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t elcr_ioport_read(void *opaque, target_phys_addr_t addr,  // (1) 0.2842
/*2  */                                  unsigned size)                          // (0) 0.3684
/*4  */ {                                                                        // (4) 0.01053
/*6  */     PICCommonState *s = opaque;                                          // (2) 0.1263
/*8  */     return s->elcr;                                                      // (3) 0.09474
/*10 */ }                                                                        // (5) 0.01053
