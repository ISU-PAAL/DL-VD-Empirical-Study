// commit message qemu@3558f8055f (target=0, prob=0.012986096, correct=True): target-i386: Access segs via TCG registers
/*0  */ static inline void gen_op_movl_seg_T0_vm(int seg_reg)               // (4) 0.1163
/*2  */ {                                                                   // (7) 0.004651
/*4  */     tcg_gen_andi_tl(cpu_T[0], cpu_T[0], 0xffff);                    // (2) 0.1302
/*6  */     tcg_gen_st32_tl(cpu_T[0], cpu_env,                              // (5) 0.1116
/*8  */                     offsetof(CPUX86State,segs[seg_reg].selector));  // (0) 0.1767
/*10 */     tcg_gen_shli_tl(cpu_T[0], cpu_T[0], 4);                         // (3) 0.1256
/*12 */     tcg_gen_st_tl(cpu_T[0], cpu_env,                                // (6) 0.107
/*14 */                   offsetof(CPUX86State,segs[seg_reg].base));        // (1) 0.1628
/*16 */ }                                                                   // (8) 0.004651
