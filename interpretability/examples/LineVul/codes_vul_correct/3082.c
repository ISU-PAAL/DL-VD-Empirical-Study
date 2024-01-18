// commit message qemu@9633fcc6a0 (target=1, prob=0.50353265, correct=True): PPC: Fix L2CR write accesses
/*0  */ static void init_proc_750fx (CPUPPCState *env)           // (14) 0.03125
/*2  */ {                                                        // (26) 0.001953
/*4  */     gen_spr_ne_601(env);                                 // (15) 0.02539
/*6  */     gen_spr_7xx(env);                                    // (16) 0.02344
/*8  */     /* XXX : not implemented */                          // (19) 0.01758
/*10 */     spr_register(env, SPR_L2CR, "L2CR",                  // (8) 0.03906
/*12 */                  SPR_NOACCESS, SPR_NOACCESS,             // (2) 0.05469
/*14 */                  &spr_read_generic, NULL,                // (6) 0.04883
/*16 */                  0x00000000);                            // (9) 0.03906
/*18 */     /* Time base */                                      // (24) 0.01367
/*20 */     gen_tbl(env);                                        // (18) 0.01953
/*22 */     /* Thermal management */                             // (25) 0.01367
/*24 */     gen_spr_thrm(env);                                   // (17) 0.02344
/*26 */     /* XXX : not implemented */                          // (20) 0.01758
/*28 */     spr_register(env, SPR_750_THRM4, "THRM4",            // (7) 0.04297
/*30 */                  SPR_NOACCESS, SPR_NOACCESS,             // (3) 0.05469
/*32 */                  &spr_read_generic, &spr_write_generic,  // (0) 0.05859
/*34 */                  0x00000000);                            // (10) 0.03906
/*36 */     /* Hardware implementation registers */              // (23) 0.01563
/*38 */     /* XXX : not implemented */                          // (21) 0.01758
/*40 */     spr_register(env, SPR_HID0, "HID0",                  // (11) 0.03906
/*42 */                  SPR_NOACCESS, SPR_NOACCESS,             // (4) 0.05469
/*44 */                  &spr_read_generic, &spr_write_generic,  // (1) 0.05859
/*46 */                  0x00000000);                            // (12) 0.03906
/*48 */     /* XXX : not implemented */                          // (22) 0.01758
/*50 */     spr_register(env, SPR_HID1, "HID1",                  // (13) 0.03906
/*52 */                  SPR_NOACCESS, SPR_NOACCESS,             // (5) 0.05469
/*54 */                  &spr_read_generic, &spr_write_generic,  // 0.0
/*56 */                  0x00000000);                            // 0.0
/*58 */     /* XXX : not implemented */                          // 0.0
/*60 */     spr_register(env, SPR_750FX_HID2, "HID2",            // 0.0
/*62 */                  SPR_NOACCESS, SPR_NOACCESS,             // 0.0
/*64 */                  &spr_read_generic, &spr_write_generic,  // 0.0
/*66 */                  0x00000000);                            // 0.0
/*68 */     /* Memory management */                              // 0.0
/*70 */     gen_low_BATs(env);                                   // 0.0
/*72 */     /* PowerPC 750fx & 750gx has 8 DBATs and 8 IBATs */  // 0.0
/*74 */     gen_high_BATs(env);                                  // 0.0
/*76 */     init_excp_7x0(env);                                  // 0.0
/*78 */     env->dcache_line_size = 32;                          // 0.0
/*80 */     env->icache_line_size = 32;                          // 0.0
/*82 */     /* Allocate hardware IRQ controller */               // 0.0
/*84 */     ppc6xx_irq_init(env);                                // 0.0
/*86 */ }                                                        // 0.0
