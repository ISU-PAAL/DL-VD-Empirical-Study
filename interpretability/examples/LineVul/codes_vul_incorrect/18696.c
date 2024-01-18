// commit message qemu@f85da3081d (target=1, prob=0.25569767, correct=False): target/sh4: Use cmpxchg for movco when parallel_cpus
/*0   */ void sh4_translate_init(void)                                                   // (12) 0.02148
/*2   */ {                                                                               // (15) 0.001953
/*4   */     int i;                                                                      // (13) 0.01172
/*6   */     static const char * const gregnames[24] = {                                 // (10) 0.03125
/*8   */         "R0_BANK0", "R1_BANK0", "R2_BANK0", "R3_BANK0",                         // (6) 0.07617
/*10  */         "R4_BANK0", "R5_BANK0", "R6_BANK0", "R7_BANK0",                         // (7) 0.07617
/*12  */         "R8", "R9", "R10", "R11", "R12", "R13", "R14", "R15",                   // (8) 0.07617
/*14  */         "R0_BANK1", "R1_BANK1", "R2_BANK1", "R3_BANK1",                         // (9) 0.07617
/*16  */         "R4_BANK1", "R5_BANK1", "R6_BANK1", "R7_BANK1"                          // (5) 0.07617
/*18  */     };                                                                          // (14) 0.007813
/*20  */     static const char * const fregnames[32] = {                                 // (11) 0.03125
/*22  */          "FPR0_BANK0",  "FPR1_BANK0",  "FPR2_BANK0",  "FPR3_BANK0",             // (0) 0.0918
/*24  */          "FPR4_BANK0",  "FPR5_BANK0",  "FPR6_BANK0",  "FPR7_BANK0",             // (1) 0.0918
/*26  */          "FPR8_BANK0",  "FPR9_BANK0", "FPR10_BANK0", "FPR11_BANK0",             // (3) 0.08789
/*28  */         "FPR12_BANK0", "FPR13_BANK0", "FPR14_BANK0", "FPR15_BANK0",             // (4) 0.08398
/*30  */          "FPR0_BANK1",  "FPR1_BANK1",  "FPR2_BANK1",  "FPR3_BANK1",             // (2) 0.0918
/*32  */          "FPR4_BANK1",  "FPR5_BANK1",  "FPR6_BANK1",  "FPR7_BANK1",             // 0.0
/*34  */          "FPR8_BANK1",  "FPR9_BANK1", "FPR10_BANK1", "FPR11_BANK1",             // 0.0
/*36  */         "FPR12_BANK1", "FPR13_BANK1", "FPR14_BANK1", "FPR15_BANK1",             // 0.0
/*38  */     };                                                                          // 0.0
/*42  */     for (i = 0; i < 24; i++) {                                                  // 0.0
/*44  */         cpu_gregs[i] = tcg_global_mem_new_i32(cpu_env,                          // 0.0
/*46  */                                               offsetof(CPUSH4State, gregs[i]),  // 0.0
/*48  */                                               gregnames[i]);                    // 0.0
/*50  */     }                                                                           // 0.0
/*52  */     memcpy(cpu_gregs + 24, cpu_gregs + 8, 8 * sizeof(TCGv));                    // 0.0
/*56  */     cpu_pc = tcg_global_mem_new_i32(cpu_env,                                    // 0.0
/*58  */                                     offsetof(CPUSH4State, pc), "PC");           // 0.0
/*60  */     cpu_sr = tcg_global_mem_new_i32(cpu_env,                                    // 0.0
/*62  */                                     offsetof(CPUSH4State, sr), "SR");           // 0.0
/*64  */     cpu_sr_m = tcg_global_mem_new_i32(cpu_env,                                  // 0.0
/*66  */                                       offsetof(CPUSH4State, sr_m), "SR_M");     // 0.0
/*68  */     cpu_sr_q = tcg_global_mem_new_i32(cpu_env,                                  // 0.0
/*70  */                                       offsetof(CPUSH4State, sr_q), "SR_Q");     // 0.0
/*72  */     cpu_sr_t = tcg_global_mem_new_i32(cpu_env,                                  // 0.0
/*74  */                                       offsetof(CPUSH4State, sr_t), "SR_T");     // 0.0
/*76  */     cpu_ssr = tcg_global_mem_new_i32(cpu_env,                                   // 0.0
/*78  */                                      offsetof(CPUSH4State, ssr), "SSR");        // 0.0
/*80  */     cpu_spc = tcg_global_mem_new_i32(cpu_env,                                   // 0.0
/*82  */                                      offsetof(CPUSH4State, spc), "SPC");        // 0.0
/*84  */     cpu_gbr = tcg_global_mem_new_i32(cpu_env,                                   // 0.0
/*86  */                                      offsetof(CPUSH4State, gbr), "GBR");        // 0.0
/*88  */     cpu_vbr = tcg_global_mem_new_i32(cpu_env,                                   // 0.0
/*90  */                                      offsetof(CPUSH4State, vbr), "VBR");        // 0.0
/*92  */     cpu_sgr = tcg_global_mem_new_i32(cpu_env,                                   // 0.0
/*94  */                                      offsetof(CPUSH4State, sgr), "SGR");        // 0.0
/*96  */     cpu_dbr = tcg_global_mem_new_i32(cpu_env,                                   // 0.0
/*98  */                                      offsetof(CPUSH4State, dbr), "DBR");        // 0.0
/*100 */     cpu_mach = tcg_global_mem_new_i32(cpu_env,                                  // 0.0
/*102 */                                       offsetof(CPUSH4State, mach), "MACH");     // 0.0
/*104 */     cpu_macl = tcg_global_mem_new_i32(cpu_env,                                  // 0.0
/*106 */                                       offsetof(CPUSH4State, macl), "MACL");     // 0.0
/*108 */     cpu_pr = tcg_global_mem_new_i32(cpu_env,                                    // 0.0
/*110 */                                     offsetof(CPUSH4State, pr), "PR");           // 0.0
/*112 */     cpu_fpscr = tcg_global_mem_new_i32(cpu_env,                                 // 0.0
/*114 */                                        offsetof(CPUSH4State, fpscr), "FPSCR");  // 0.0
/*116 */     cpu_fpul = tcg_global_mem_new_i32(cpu_env,                                  // 0.0
/*118 */                                       offsetof(CPUSH4State, fpul), "FPUL");     // 0.0
/*122 */     cpu_flags = tcg_global_mem_new_i32(cpu_env,                                 // 0.0
/*124 */ 				       offsetof(CPUSH4State, flags), "_flags_");                            // 0.0
/*126 */     cpu_delayed_pc = tcg_global_mem_new_i32(cpu_env,                            // 0.0
/*128 */ 					    offsetof(CPUSH4State, delayed_pc),                                     // 0.0
/*130 */ 					    "_delayed_pc_");                                                       // 0.0
/*132 */     cpu_delayed_cond = tcg_global_mem_new_i32(cpu_env,                          // 0.0
/*134 */                                               offsetof(CPUSH4State,             // 0.0
/*136 */                                                        delayed_cond),           // 0.0
/*138 */                                               "_delayed_cond_");                // 0.0
/*140 */     cpu_ldst = tcg_global_mem_new_i32(cpu_env,                                  // 0.0
/*142 */ 				      offsetof(CPUSH4State, ldst), "_ldst_");                               // 0.0
/*146 */     for (i = 0; i < 32; i++)                                                    // 0.0
/*148 */         cpu_fregs[i] = tcg_global_mem_new_i32(cpu_env,                          // 0.0
/*150 */                                               offsetof(CPUSH4State, fregs[i]),  // 0.0
/*152 */                                               fregnames[i]);                    // 0.0
/*154 */ }                                                                               // 0.0
