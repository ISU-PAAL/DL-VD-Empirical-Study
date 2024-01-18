// commit message qemu@18b21a2f83 (target=0, prob=0.04931939, correct=True): target-ppc: retain l{w,d}arx loaded value
/*0   */ void ppc_translate_init(void)                                                                  // (15) 0.02148
/*2   */ {                                                                                              // (24) 0.001953
/*4   */     int i;                                                                                     // (22) 0.01172
/*6   */     char* p;                                                                                   // (21) 0.01367
/*8   */     size_t cpu_reg_names_size;                                                                 // (13) 0.02734
/*10  */     static int done_init = 0;                                                                  // (16) 0.02148
/*14  */     if (done_init)                                                                             // (19) 0.01758
/*16  */         return;                                                                                // (20) 0.01758
/*20  */     cpu_env = tcg_global_reg_new_ptr(TCG_AREG0, "env");                                        // (4) 0.05469
/*24  */     p = cpu_reg_names;                                                                         // (17) 0.02148
/*26  */     cpu_reg_names_size = sizeof(cpu_reg_names);                                                // (8) 0.03711
/*30  */     for (i = 0; i < 8; i++) {                                                                  // (11) 0.03125
/*32  */         snprintf(p, cpu_reg_names_size, "crf%d", i);                                           // (5) 0.05469
/*34  */         cpu_crf[i] = tcg_global_mem_new_i32(TCG_AREG0,                                         // (2) 0.06641
/*36  */                                             offsetof(CPUState, crf[i]), p);                    // (0) 0.1094
/*38  */         p += 5;                                                                                // (18) 0.02148
/*40  */         cpu_reg_names_size -= 5;                                                               // (10) 0.0332
/*42  */     }                                                                                          // (23) 0.007812
/*46  */     for (i = 0; i < 32; i++) {                                                                 // (12) 0.03125
/*48  */         snprintf(p, cpu_reg_names_size, "r%d", i);                                             // (6) 0.05273
/*50  */         cpu_gpr[i] = tcg_global_mem_new(TCG_AREG0,                                             // (3) 0.06055
/*52  */                                         offsetof(CPUState, gpr[i]), p);                        // (1) 0.1016
/*54  */         p += (i < 10) ? 3 : 4;                                                                 // (9) 0.03711
/*56  */         cpu_reg_names_size -= (i < 10) ? 3 : 4;                                                // (7) 0.04883
/*58  */ #if !defined(TARGET_PPC64)                                                                     // (14) 0.02344
/*60  */         snprintf(p, cpu_reg_names_size, "r%dH", i);                                            // 0.0
/*62  */         cpu_gprh[i] = tcg_global_mem_new_i32(TCG_AREG0,                                        // 0.0
/*64  */                                              offsetof(CPUState, gprh[i]), p);                  // 0.0
/*66  */         p += (i < 10) ? 4 : 5;                                                                 // 0.0
/*68  */         cpu_reg_names_size -= (i < 10) ? 4 : 5;                                                // 0.0
/*70  */ #endif                                                                                         // 0.0
/*74  */         snprintf(p, cpu_reg_names_size, "fp%d", i);                                            // 0.0
/*76  */         cpu_fpr[i] = tcg_global_mem_new_i64(TCG_AREG0,                                         // 0.0
/*78  */                                             offsetof(CPUState, fpr[i]), p);                    // 0.0
/*80  */         p += (i < 10) ? 4 : 5;                                                                 // 0.0
/*82  */         cpu_reg_names_size -= (i < 10) ? 4 : 5;                                                // 0.0
/*86  */         snprintf(p, cpu_reg_names_size, "avr%dH", i);                                          // 0.0
/*88  */ #ifdef HOST_WORDS_BIGENDIAN                                                                    // 0.0
/*90  */         cpu_avrh[i] = tcg_global_mem_new_i64(TCG_AREG0,                                        // 0.0
/*92  */                                              offsetof(CPUState, avr[i].u64[0]), p);            // 0.0
/*94  */ #else                                                                                          // 0.0
/*96  */         cpu_avrh[i] = tcg_global_mem_new_i64(TCG_AREG0,                                        // 0.0
/*98  */                                              offsetof(CPUState, avr[i].u64[1]), p);            // 0.0
/*100 */ #endif                                                                                         // 0.0
/*102 */         p += (i < 10) ? 6 : 7;                                                                 // 0.0
/*104 */         cpu_reg_names_size -= (i < 10) ? 6 : 7;                                                // 0.0
/*108 */         snprintf(p, cpu_reg_names_size, "avr%dL", i);                                          // 0.0
/*110 */ #ifdef HOST_WORDS_BIGENDIAN                                                                    // 0.0
/*112 */         cpu_avrl[i] = tcg_global_mem_new_i64(TCG_AREG0,                                        // 0.0
/*114 */                                              offsetof(CPUState, avr[i].u64[1]), p);            // 0.0
/*116 */ #else                                                                                          // 0.0
/*118 */         cpu_avrl[i] = tcg_global_mem_new_i64(TCG_AREG0,                                        // 0.0
/*120 */                                              offsetof(CPUState, avr[i].u64[0]), p);            // 0.0
/*122 */ #endif                                                                                         // 0.0
/*124 */         p += (i < 10) ? 6 : 7;                                                                 // 0.0
/*126 */         cpu_reg_names_size -= (i < 10) ? 6 : 7;                                                // 0.0
/*128 */     }                                                                                          // 0.0
/*132 */     cpu_nip = tcg_global_mem_new(TCG_AREG0,                                                    // 0.0
/*134 */                                  offsetof(CPUState, nip), "nip");                              // 0.0
/*138 */     cpu_msr = tcg_global_mem_new(TCG_AREG0,                                                    // 0.0
/*140 */                                  offsetof(CPUState, msr), "msr");                              // 0.0
/*144 */     cpu_ctr = tcg_global_mem_new(TCG_AREG0,                                                    // 0.0
/*146 */                                  offsetof(CPUState, ctr), "ctr");                              // 0.0
/*150 */     cpu_lr = tcg_global_mem_new(TCG_AREG0,                                                     // 0.0
/*152 */                                 offsetof(CPUState, lr), "lr");                                 // 0.0
/*156 */     cpu_xer = tcg_global_mem_new(TCG_AREG0,                                                    // 0.0
/*158 */                                  offsetof(CPUState, xer), "xer");                              // 0.0
/*162 */     cpu_reserve = tcg_global_mem_new(TCG_AREG0,                                                // 0.0
/*164 */                                      offsetof(CPUState, reserve), "reserve");                  // 0.0
/*168 */     cpu_fpscr = tcg_global_mem_new_i32(TCG_AREG0,                                              // 0.0
/*170 */                                        offsetof(CPUState, fpscr), "fpscr");                    // 0.0
/*174 */     cpu_access_type = tcg_global_mem_new_i32(TCG_AREG0,                                        // 0.0
/*176 */                                              offsetof(CPUState, access_type), "access_type");  // 0.0
/*180 */     /* register helpers */                                                                     // 0.0
/*182 */ #define GEN_HELPER 2                                                                           // 0.0
/*184 */ #include "helper.h"                                                                            // 0.0
/*188 */     done_init = 1;                                                                             // 0.0
/*190 */ }                                                                                              // 0.0
