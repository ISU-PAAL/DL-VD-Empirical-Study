// commit message qemu@f8ed85ac99 (target=1, prob=0.48939797, correct=False): Fix bad error handling after memory_region_init_ram()
/*0  */ static int integratorcm_init(SysBusDevice *dev)                                 // (21) 0.02734
/*2  */ {                                                                               // (25) 0.001953
/*4  */     IntegratorCMState *s = INTEGRATOR_CM(dev);                                  // (4) 0.03711
/*8  */     s->cm_osc = 0x01000048;                                                     // (19) 0.0293
/*10 */     /* ??? What should the high bits of this value be?  */                      // (13) 0.0332
/*12 */     s->cm_auxosc = 0x0007feff;                                                  // (14) 0.0332
/*14 */     s->cm_sdram = 0x00011122;                                                   // (15) 0.03125
/*16 */     if (s->memsz >= 256) {                                                      // (22) 0.02734
/*18 */         integrator_spd[31] = 64;                                                // (8) 0.03516
/*20 */         s->cm_sdram |= 0x10;                                                    // (5) 0.03711
/*22 */     } else if (s->memsz >= 128) {                                               // (16) 0.03125
/*24 */         integrator_spd[31] = 32;                                                // (9) 0.03516
/*26 */         s->cm_sdram |= 0x0c;                                                    // (3) 0.03906
/*28 */     } else if (s->memsz >= 64) {                                                // (17) 0.03125
/*30 */         integrator_spd[31] = 16;                                                // (10) 0.03516
/*32 */         s->cm_sdram |= 0x08;                                                    // (6) 0.03711
/*34 */     } else if (s->memsz >= 32) {                                                // (18) 0.03125
/*36 */         integrator_spd[31] = 4;                                                 // (11) 0.03516
/*38 */         s->cm_sdram |= 0x04;                                                    // (7) 0.03711
/*40 */     } else {                                                                    // (23) 0.01172
/*42 */         integrator_spd[31] = 2;                                                 // (12) 0.03516
/*44 */     }                                                                           // (24) 0.007812
/*46 */     memcpy(integrator_spd + 73, "QEMU-MEMORY", 11);                             // (2) 0.05078
/*48 */     s->cm_init = 0x00000112;                                                    // (20) 0.0293
/*50 */     s->cm_refcnt_offset = muldiv64(qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL), 24,   // (0) 0.08008
/*52 */                                    1000);                                       // (1) 0.07031
/*54 */     memory_region_init_ram(&s->flash, OBJECT(s), "integrator.flash", 0x100000,  // 0.0
/*56 */                            &error_abort);                                       // 0.0
/*58 */     vmstate_register_ram_global(&s->flash);                                     // 0.0
/*62 */     memory_region_init_io(&s->iomem, OBJECT(s), &integratorcm_ops, s,           // 0.0
/*64 */                           "integratorcm", 0x00800000);                          // 0.0
/*66 */     sysbus_init_mmio(dev, &s->iomem);                                           // 0.0
/*70 */     integratorcm_do_remap(s);                                                   // 0.0
/*72 */     /* ??? Save/restore.  */                                                    // 0.0
/*74 */     return 0;                                                                   // 0.0
/*76 */ }                                                                               // 0.0
