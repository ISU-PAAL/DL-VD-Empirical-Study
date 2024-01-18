// commit message qemu@a8170e5e97 (target=0, prob=0.0045152223, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint64_t mmio_ide_status_read(void *opaque, target_phys_addr_t addr,  // (1) 0.2617
/*2  */                                      unsigned size)                          // (0) 0.3645
/*4  */ {                                                                            // (4) 0.009346
/*6  */     MMIOState *s= opaque;                                                    // (3) 0.1122
/*8  */     return ide_status_read(&s->bus, 0);                                      // (2) 0.1495
/*10 */ }                                                                            // (5) 0.009346
