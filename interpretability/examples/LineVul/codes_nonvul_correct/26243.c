// commit message qemu@b854bc196f (target=0, prob=0.008439979, correct=True): Make accesses with wrong width also work as apparently real hardware allows them when the fault is disabled. Fix DMA register writes if target_phys_addr_t is 64-bit. Make more functions static. A timer hack to make PalmOS run in finite time (uses very short timer periods, much shorter than clocksource tick). Re-calculate internal clock rates on start-up.
/*0  */ static void omap_pwt_init(target_phys_addr_t base, struct omap_mpu_state_s *s,  // (0) 0.1553
/*2  */                 omap_clk clk)                                                   // (4) 0.1117
/*4  */ {                                                                               // (9) 0.004854
/*6  */     int iomemtype;                                                              // (8) 0.04369
/*10 */     s->pwt.base = base;                                                         // (7) 0.05825
/*12 */     s->pwt.clk = clk;                                                           // (5) 0.06796
/*14 */     omap_pwt_reset(s);                                                          // (6) 0.06311
/*18 */     iomemtype = cpu_register_io_memory(0, omap_pwt_readfn,                      // (3) 0.1311
/*20 */                     omap_pwt_writefn, s);                                       // (1) 0.1456
/*22 */     cpu_register_physical_memory(s->pwt.base, 0x800, iomemtype);                // (2) 0.1311
/*24 */ }                                                                               // (10) 0.004854
