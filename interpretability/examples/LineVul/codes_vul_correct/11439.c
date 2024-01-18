// commit message qemu@2d896b454a (target=1, prob=0.75314987, correct=True): Revert "hw/mips: MIPS Boston board support"
/*0  */ static uint64_t boston_platreg_read(void *opaque, hwaddr addr,               // (8) 0.04688
/*2  */                                     unsigned size)                           // (1) 0.07422
/*4  */ {                                                                            // (24) 0.001953
/*6  */     BostonState *s = opaque;                                                 // (18) 0.01953
/*8  */     uint32_t gic_freq, val;                                                  // (10) 0.0293
/*12 */     if (size != 4) {                                                         // (19) 0.01953
/*14 */         qemu_log_mask(LOG_UNIMP, "%uB platform register read", size);        // (3) 0.05859
/*16 */         return 0;                                                            // (20) 0.01953
/*18 */     }                                                                        // (23) 0.007812
/*22 */     switch (addr & 0xffff) {                                                 // (16) 0.02344
/*24 */     case PLAT_FPGA_BUILD:                                                    // (12) 0.02539
/*26 */     case PLAT_CORE_CL:                                                       // (17) 0.02344
/*28 */     case PLAT_WRAPPER_CL:                                                    // (13) 0.02539
/*30 */         return 0;                                                            // (21) 0.01953
/*32 */     case PLAT_DDR3_STATUS:                                                   // (11) 0.02734
/*34 */         return PLAT_DDR3_STATUS_LOCKED | PLAT_DDR3_STATUS_CALIBRATED;        // (2) 0.07227
/*36 */     case PLAT_MMCM_DIV:                                                      // (14) 0.02539
/*38 */         gic_freq = mips_gictimer_get_freq(s->cps->gic.gic_timer) / 1000000;  // (0) 0.08203
/*40 */         val = gic_freq << PLAT_MMCM_DIV_INPUT_SHIFT;                         // (4) 0.05859
/*42 */         val |= 1 << PLAT_MMCM_DIV_MUL_SHIFT;                                 // (7) 0.05273
/*44 */         val |= 1 << PLAT_MMCM_DIV_CLK0DIV_SHIFT;                             // (5) 0.05664
/*46 */         val |= 1 << PLAT_MMCM_DIV_CLK1DIV_SHIFT;                             // (6) 0.05664
/*48 */         return val;                                                          // (22) 0.01953
/*50 */     case PLAT_BUILD_CFG:                                                     // (15) 0.02539
/*52 */         val = PLAT_BUILD_CFG_PCIE0_EN;                                       // (9) 0.04688
/*54 */         val |= PLAT_BUILD_CFG_PCIE1_EN;                                      // 0.0
/*56 */         val |= PLAT_BUILD_CFG_PCIE2_EN;                                      // 0.0
/*58 */         return val;                                                          // 0.0
/*60 */     case PLAT_DDR_CFG:                                                       // 0.0
/*62 */         val = s->mach->ram_size / G_BYTE;                                    // 0.0
/*64 */         assert(!(val & ~PLAT_DDR_CFG_SIZE));                                 // 0.0
/*66 */         val |= PLAT_DDR_CFG_MHZ;                                             // 0.0
/*68 */         return val;                                                          // 0.0
/*70 */     default:                                                                 // 0.0
/*72 */         qemu_log_mask(LOG_UNIMP, "Read platform register 0x%" HWADDR_PRIx,   // 0.0
/*74 */                       addr & 0xffff);                                        // 0.0
/*76 */         return 0;                                                            // 0.0
/*78 */     }                                                                        // 0.0
/*80 */ }                                                                            // 0.0
