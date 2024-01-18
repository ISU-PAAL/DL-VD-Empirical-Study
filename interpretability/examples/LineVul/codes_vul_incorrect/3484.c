// commit message qemu@ee71c98434 (target=1, prob=0.008468013, correct=False): hw/arm_timer.c: Fix bounds check for Integrator timer accesses
/*0  */ static uint64_t icp_pit_read(void *opaque, target_phys_addr_t offset,  // (1) 0.134
/*2  */                              unsigned size)                            // (0) 0.1598
/*4  */ {                                                                      // (10) 0.005155
/*6  */     icp_pit_state *s = (icp_pit_state *)opaque;                        // (3) 0.1186
/*8  */     int n;                                                             // (8) 0.03093
/*12 */     /* ??? Don't know the PrimeCell ID for this device.  */            // (5) 0.09278
/*14 */     n = offset >> 8;                                                   // (7) 0.04639
/*16 */     if (n > 3) {                                                       // (6) 0.05155
/*18 */         hw_error("sp804_read: Bad timer %d\n", n);                     // (2) 0.134
/*20 */     }                                                                  // (9) 0.02062
/*24 */     return arm_timer_read(s->timer[n], offset & 0xff);                 // (4) 0.1082
/*26 */ }                                                                      // (11) 0.005155
