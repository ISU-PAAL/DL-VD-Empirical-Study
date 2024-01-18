// commit message qemu@42a6686b2f (target=0, prob=0.29814833, correct=True): target/arm: Make FAULTMASK register banked for v8M
/*0   */ void HELPER(v7m_msr)(CPUARMState *env, uint32_t maskreg, uint32_t val)     // (2) 0.05859
/*2   */ {                                                                          // (26) 0.001953
/*4   */     /* We're passed bits [11..0] of the instruction; extract               // (12) 0.03516
/*6   */      * SYSm and the mask bits.                                             // (19) 0.02344
/*8   */      * Invalid combinations of SYSm and mask are UNPREDICTABLE;            // (9) 0.03711
/*10  */      * we choose to treat them as if the mask bits were valid.             // (13) 0.03516
/*12  */      * NB that the pseudocode 'mask' variable is bits [11..10],            // (6) 0.04297
/*14  */      * whereas ours is [11..8].                                            // (18) 0.02539
/*16  */      */                                                                    // (24) 0.009766
/*18  */     uint32_t mask = extract32(maskreg, 8, 4);                              // (10) 0.03711
/*20  */     uint32_t reg = extract32(maskreg, 0, 8);                               // (11) 0.03711
/*24  */     if (arm_current_el(env) == 0 && reg > 7) {                             // (8) 0.04102
/*26  */         /* only xPSR sub-fields may be written by unprivileged */          // (5) 0.04492
/*28  */         return;                                                            // (22) 0.01758
/*30  */     }                                                                      // (25) 0.007812
/*34  */     switch (reg) {                                                         // (23) 0.01562
/*36  */     case 0 ... 7: /* xPSR sub-fields */                                    // (16) 0.03125
/*38  */         /* only APSR is actually writable */                               // (15) 0.03125
/*40  */         if (!(reg & 4)) {                                                  // (17) 0.0293
/*42  */             uint32_t apsrmask = 0;                                         // (7) 0.04297
/*46  */             if (mask & 8) {                                                // (14) 0.03516
/*48  */                 apsrmask |= XPSR_NZCV | XPSR_Q;                            // (1) 0.06641
/*50  */             }                                                              // (20) 0.02344
/*52  */             if ((mask & 4) && arm_feature(env, ARM_FEATURE_THUMB_DSP)) {   // (0) 0.07227
/*54  */                 apsrmask |= XPSR_GE;                                       // (3) 0.05273
/*56  */             }                                                              // (21) 0.02344
/*58  */             xpsr_write(env, val, apsrmask);                                // (4) 0.05078
/*60  */         }                                                                  // 0.0
/*62  */         break;                                                             // 0.0
/*64  */     case 8: /* MSP */                                                      // 0.0
/*66  */         if (env->v7m.control & R_V7M_CONTROL_SPSEL_MASK) {                 // 0.0
/*68  */             env->v7m.other_sp = val;                                       // 0.0
/*70  */         } else {                                                           // 0.0
/*72  */             env->regs[13] = val;                                           // 0.0
/*74  */         }                                                                  // 0.0
/*76  */         break;                                                             // 0.0
/*78  */     case 9: /* PSP */                                                      // 0.0
/*80  */         if (env->v7m.control & R_V7M_CONTROL_SPSEL_MASK) {                 // 0.0
/*82  */             env->regs[13] = val;                                           // 0.0
/*84  */         } else {                                                           // 0.0
/*86  */             env->v7m.other_sp = val;                                       // 0.0
/*88  */         }                                                                  // 0.0
/*90  */         break;                                                             // 0.0
/*92  */     case 16: /* PRIMASK */                                                 // 0.0
/*94  */         env->v7m.primask[env->v7m.secure] = val & 1;                       // 0.0
/*96  */         break;                                                             // 0.0
/*98  */     case 17: /* BASEPRI */                                                 // 0.0
/*100 */         env->v7m.basepri[env->v7m.secure] = val & 0xff;                    // 0.0
/*102 */         break;                                                             // 0.0
/*104 */     case 18: /* BASEPRI_MAX */                                             // 0.0
/*106 */         val &= 0xff;                                                       // 0.0
/*108 */         if (val != 0 && (val < env->v7m.basepri[env->v7m.secure]           // 0.0
/*110 */                          || env->v7m.basepri[env->v7m.secure] == 0)) {     // 0.0
/*112 */             env->v7m.basepri[env->v7m.secure] = val;                       // 0.0
/*114 */         }                                                                  // 0.0
/*116 */         break;                                                             // 0.0
/*118 */     case 19: /* FAULTMASK */                                               // 0.0
/*120 */         env->v7m.faultmask = val & 1;                                      // 0.0
/*122 */         break;                                                             // 0.0
/*124 */     case 20: /* CONTROL */                                                 // 0.0
/*126 */         /* Writing to the SPSEL bit only has an effect if we are in        // 0.0
/*128 */          * thread mode; other bits can be updated by any privileged code.  // 0.0
/*130 */          * switch_v7m_sp() deals with updating the SPSEL bit in            // 0.0
/*132 */          * env->v7m.control, so we only need update the others.            // 0.0
/*134 */          */                                                                // 0.0
/*136 */         if (!arm_v7m_is_handler_mode(env)) {                               // 0.0
/*138 */             switch_v7m_sp(env, (val & R_V7M_CONTROL_SPSEL_MASK) != 0);     // 0.0
/*140 */         }                                                                  // 0.0
/*142 */         env->v7m.control &= ~R_V7M_CONTROL_NPRIV_MASK;                     // 0.0
/*144 */         env->v7m.control |= val & R_V7M_CONTROL_NPRIV_MASK;                // 0.0
/*146 */         break;                                                             // 0.0
/*148 */     default:                                                               // 0.0
/*150 */         qemu_log_mask(LOG_GUEST_ERROR, "Attempt to write unknown special"  // 0.0
/*152 */                                        " register %d\n", reg);             // 0.0
/*154 */         return;                                                            // 0.0
/*156 */     }                                                                      // 0.0
/*158 */ }                                                                          // 0.0
