// commit message qemu@81907a5829 (target=1, prob=0.23658712, correct=False): target-arm: In v8, make illegal AArch32 mode changes set PSTATE.IL
/*0   */ void cpsr_write(CPUARMState *env, uint32_t val, uint32_t mask,                   // (0) 0.04883
/*2   */                 CPSRWriteType write_type)                                        // (3) 0.04492
/*4   */ {                                                                                // (29) 0.001953
/*6   */     uint32_t changed_daif;                                                       // (20) 0.02344
/*10  */     if (mask & CPSR_NZCV) {                                                      // (17) 0.02734
/*12  */         env->ZF = (~val) & CPSR_Z;                                               // (9) 0.04102
/*14  */         env->NF = val;                                                           // (18) 0.02539
/*16  */         env->CF = (val >> 29) & 1;                                               // (11) 0.03711
/*18  */         env->VF = (val << 3) & 0x80000000;                                       // (6) 0.04492
/*20  */     }                                                                            // (26) 0.007812
/*22  */     if (mask & CPSR_Q)                                                           // (21) 0.02344
/*24  */         env->QF = ((val & CPSR_Q) != 0);                                         // (5) 0.04492
/*26  */     if (mask & CPSR_T)                                                           // (22) 0.02344
/*28  */         env->thumb = ((val & CPSR_T) != 0);                                      // (4) 0.04492
/*30  */     if (mask & CPSR_IT_0_1) {                                                    // (14) 0.0332
/*32  */         env->condexec_bits &= ~3;                                                // (12) 0.03516
/*34  */         env->condexec_bits |= (val >> 25) & 3;                                   // (7) 0.04492
/*36  */     }                                                                            // (27) 0.007812
/*38  */     if (mask & CPSR_IT_2_7) {                                                    // (15) 0.0332
/*40  */         env->condexec_bits &= 3;                                                 // (13) 0.0332
/*42  */         env->condexec_bits |= (val >> 8) & 0xfc;                                 // (1) 0.04883
/*44  */     }                                                                            // (28) 0.007812
/*46  */     if (mask & CPSR_GE) {                                                        // (19) 0.02539
/*48  */         env->GE = (val >> 16) & 0xf;                                             // (10) 0.03906
/*50  */     }                                                                            // (25) 0.007812
/*54  */     /* In a V7 implementation that includes the security extensions but does     // (16) 0.03125
/*56  */      * not include Virtualization Extensions the SCR.FW and SCR.AW bits control  // (8) 0.04297
/*58  */      * whether non-secure software is allowed to change the CPSR_F and CPSR_A    // (2) 0.04687
/*60  */      * bits respectively.                                                        // (23) 0.01562
/*62  */      *                                                                           // (24) 0.009766
/*64  */      * In a V8 implementation, it is permitted for privileged software to        // 0.0
/*66  */      * change the CPSR A/F bits regardless of the SCR.AW/FW bits.                // 0.0
/*68  */      */                                                                          // 0.0
/*70  */     if (write_type != CPSRWriteRaw && !arm_feature(env, ARM_FEATURE_V8) &&       // 0.0
/*72  */         arm_feature(env, ARM_FEATURE_EL3) &&                                     // 0.0
/*74  */         !arm_feature(env, ARM_FEATURE_EL2) &&                                    // 0.0
/*76  */         !arm_is_secure(env)) {                                                   // 0.0
/*80  */         changed_daif = (env->daif ^ val) & mask;                                 // 0.0
/*84  */         if (changed_daif & CPSR_A) {                                             // 0.0
/*86  */             /* Check to see if we are allowed to change the masking of async     // 0.0
/*88  */              * abort exceptions from a non-secure state.                         // 0.0
/*90  */              */                                                                  // 0.0
/*92  */             if (!(env->cp15.scr_el3 & SCR_AW)) {                                 // 0.0
/*94  */                 qemu_log_mask(LOG_GUEST_ERROR,                                   // 0.0
/*96  */                               "Ignoring attempt to switch CPSR_A flag from "     // 0.0
/*98  */                               "non-secure world with SCR.AW bit clear\n");       // 0.0
/*100 */                 mask &= ~CPSR_A;                                                 // 0.0
/*102 */             }                                                                    // 0.0
/*104 */         }                                                                        // 0.0
/*108 */         if (changed_daif & CPSR_F) {                                             // 0.0
/*110 */             /* Check to see if we are allowed to change the masking of FIQ       // 0.0
/*112 */              * exceptions from a non-secure state.                               // 0.0
/*114 */              */                                                                  // 0.0
/*116 */             if (!(env->cp15.scr_el3 & SCR_FW)) {                                 // 0.0
/*118 */                 qemu_log_mask(LOG_GUEST_ERROR,                                   // 0.0
/*120 */                               "Ignoring attempt to switch CPSR_F flag from "     // 0.0
/*122 */                               "non-secure world with SCR.FW bit clear\n");       // 0.0
/*124 */                 mask &= ~CPSR_F;                                                 // 0.0
/*126 */             }                                                                    // 0.0
/*130 */             /* Check whether non-maskable FIQ (NMFI) support is enabled.         // 0.0
/*132 */              * If this bit is set software is not allowed to mask                // 0.0
/*134 */              * FIQs, but is allowed to set CPSR_F to 0.                          // 0.0
/*136 */              */                                                                  // 0.0
/*138 */             if ((A32_BANKED_CURRENT_REG_GET(env, sctlr) & SCTLR_NMFI) &&         // 0.0
/*140 */                 (val & CPSR_F)) {                                                // 0.0
/*142 */                 qemu_log_mask(LOG_GUEST_ERROR,                                   // 0.0
/*144 */                               "Ignoring attempt to enable CPSR_F flag "          // 0.0
/*146 */                               "(non-maskable FIQ [NMFI] support enabled)\n");    // 0.0
/*148 */                 mask &= ~CPSR_F;                                                 // 0.0
/*150 */             }                                                                    // 0.0
/*152 */         }                                                                        // 0.0
/*154 */     }                                                                            // 0.0
/*158 */     env->daif &= ~(CPSR_AIF & mask);                                             // 0.0
/*160 */     env->daif |= val & CPSR_AIF & mask;                                          // 0.0
/*164 */     if (write_type != CPSRWriteRaw &&                                            // 0.0
/*166 */         (env->uncached_cpsr & CPSR_M) != CPSR_USER &&                            // 0.0
/*168 */         ((env->uncached_cpsr ^ val) & mask & CPSR_M)) {                          // 0.0
/*170 */         if (bad_mode_switch(env, val & CPSR_M)) {                                // 0.0
/*172 */             /* Attempt to switch to an invalid mode: this is UNPREDICTABLE.      // 0.0
/*174 */              * We choose to ignore the attempt and leave the CPSR M field        // 0.0
/*176 */              * untouched.                                                        // 0.0
/*178 */              */                                                                  // 0.0
/*180 */             mask &= ~CPSR_M;                                                     // 0.0
/*182 */         } else {                                                                 // 0.0
/*184 */             switch_mode(env, val & CPSR_M);                                      // 0.0
/*186 */         }                                                                        // 0.0
/*188 */     }                                                                            // 0.0
/*190 */     mask &= ~CACHED_CPSR_BITS;                                                   // 0.0
/*192 */     env->uncached_cpsr = (env->uncached_cpsr & ~mask) | (val & mask);            // 0.0
/*194 */ }                                                                                // 0.0
