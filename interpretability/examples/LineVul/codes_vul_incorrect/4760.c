// commit message qemu@9633fcc6a0 (target=1, prob=0.4454913, correct=False): PPC: Fix L2CR write accesses
/*0   */ static void init_proc_power5plus(CPUPPCState *env)                    // (15) 0.0332
/*2   */ {                                                                     // (25) 0.001953
/*4   */     gen_spr_ne_601(env);                                              // (16) 0.02539
/*6   */     gen_spr_7xx(env);                                                 // (17) 0.02344
/*8   */     /* Time base */                                                   // (24) 0.01367
/*10  */     gen_tbl(env);                                                     // (18) 0.01953
/*12  */     /* Hardware implementation registers */                           // (23) 0.01563
/*14  */     /* XXX : not implemented */                                       // (19) 0.01758
/*16  */     spr_register(env, SPR_HID0, "HID0",                               // (11) 0.03906
/*18  */                  SPR_NOACCESS, SPR_NOACCESS,                          // (4) 0.05469
/*20  */                  &spr_read_generic, &spr_write_clear,                 // (0) 0.05859
/*22  */                  0x60000000);                                         // (10) 0.04102
/*24  */     /* XXX : not implemented */                                       // (20) 0.01758
/*26  */     spr_register(env, SPR_HID1, "HID1",                               // (12) 0.03906
/*28  */                  SPR_NOACCESS, SPR_NOACCESS,                          // (5) 0.05469
/*30  */                  &spr_read_generic, &spr_write_generic,               // (1) 0.05859
/*32  */                  0x00000000);                                         // (13) 0.03906
/*34  */     /* XXX : not implemented */                                       // (21) 0.01758
/*36  */     spr_register(env, SPR_750FX_HID2, "HID2",                         // (8) 0.04492
/*38  */                  SPR_NOACCESS, SPR_NOACCESS,                          // (6) 0.05469
/*40  */                  &spr_read_generic, &spr_write_generic,               // (2) 0.05859
/*42  */                  0x00000000);                                         // (14) 0.03906
/*44  */     /* XXX : not implemented */                                       // (22) 0.01758
/*46  */     spr_register(env, SPR_970_HID5, "HID5",                           // (9) 0.04297
/*48  */                  SPR_NOACCESS, SPR_NOACCESS,                          // (7) 0.05469
/*50  */                  &spr_read_generic, &spr_write_generic,               // (3) 0.05859
/*52  */                  POWERPC970_HID5_INIT);                               // 0.0
/*54  */     /* XXX : not implemented */                                       // 0.0
/*56  */     spr_register(env, SPR_L2CR, "L2CR",                               // 0.0
/*58  */                  SPR_NOACCESS, SPR_NOACCESS,                          // 0.0
/*60  */                  &spr_read_generic, NULL,                             // 0.0
/*62  */                  0x00000000);                                         // 0.0
/*64  */     /* Memory management */                                           // 0.0
/*66  */     /* XXX: not correct */                                            // 0.0
/*68  */     gen_low_BATs(env);                                                // 0.0
/*70  */     /* XXX : not implemented */                                       // 0.0
/*72  */     spr_register(env, SPR_MMUCFG, "MMUCFG",                           // 0.0
/*74  */                  SPR_NOACCESS, SPR_NOACCESS,                          // 0.0
/*76  */                  &spr_read_generic, SPR_NOACCESS,                     // 0.0
/*78  */                  0x00000000); /* TOFIX */                             // 0.0
/*80  */     /* XXX : not implemented */                                       // 0.0
/*82  */     spr_register(env, SPR_MMUCSR0, "MMUCSR0",                         // 0.0
/*84  */                  SPR_NOACCESS, SPR_NOACCESS,                          // 0.0
/*86  */                  &spr_read_generic, &spr_write_generic,               // 0.0
/*88  */                  0x00000000); /* TOFIX */                             // 0.0
/*90  */     spr_register(env, SPR_HIOR, "SPR_HIOR",                           // 0.0
/*92  */                  SPR_NOACCESS, SPR_NOACCESS,                          // 0.0
/*94  */                  &spr_read_hior, &spr_write_hior,                     // 0.0
/*96  */                  0x00000000);                                         // 0.0
/*98  */     spr_register(env, SPR_CTRL, "SPR_CTRL",                           // 0.0
/*100 */                  SPR_NOACCESS, SPR_NOACCESS,                          // 0.0
/*102 */                  &spr_read_generic, &spr_write_generic,               // 0.0
/*104 */                  0x00000000);                                         // 0.0
/*106 */     spr_register(env, SPR_UCTRL, "SPR_UCTRL",                         // 0.0
/*108 */                  SPR_NOACCESS, SPR_NOACCESS,                          // 0.0
/*110 */                  &spr_read_generic, &spr_write_generic,               // 0.0
/*112 */                  0x00000000);                                         // 0.0
/*114 */     spr_register(env, SPR_VRSAVE, "SPR_VRSAVE",                       // 0.0
/*116 */                  &spr_read_generic, &spr_write_generic,               // 0.0
/*118 */                  &spr_read_generic, &spr_write_generic,               // 0.0
/*120 */                  0x00000000);                                         // 0.0
/*122 */ #if !defined(CONFIG_USER_ONLY)                                        // 0.0
/*124 */     env->slb_nr = 64;                                                 // 0.0
/*126 */ #endif                                                                // 0.0
/*128 */     init_excp_970(env);                                               // 0.0
/*130 */     env->dcache_line_size = 128;                                      // 0.0
/*132 */     env->icache_line_size = 128;                                      // 0.0
/*134 */     /* Allocate hardware IRQ controller */                            // 0.0
/*136 */     ppc970_irq_init(env);                                             // 0.0
/*138 */     /* Can't find information on what this should be on reset.  This  // 0.0
/*140 */      * value is the one used by 74xx processors. */                   // 0.0
/*142 */     vscr_init(env, 0x00010000);                                       // 0.0
/*144 */ }                                                                     // 0.0
