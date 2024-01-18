// commit message qemu@a8170e5e97 (target=0, prob=0.0059216917, correct=True): Rename target_phys_addr_t to hwaddr
/*0  */ static uint32_t gic_dist_readw(void *opaque, target_phys_addr_t offset)  // (0) 0.2784
/*2  */ {                                                                        // (5) 0.01031
/*4  */     uint32_t val;                                                        // (3) 0.09278
/*6  */     val = gic_dist_readb(opaque, offset);                                // (2) 0.1856
/*8  */     val |= gic_dist_readb(opaque, offset + 1) << 8;                      // (1) 0.2474
/*10 */     return val;                                                          // (4) 0.06186
/*12 */ }                                                                        // (6) 0.01031
