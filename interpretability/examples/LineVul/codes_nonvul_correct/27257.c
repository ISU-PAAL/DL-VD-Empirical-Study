// commit message qemu@de9e9d9f17 (target=0, prob=0.0074008144, correct=True): target-sparc: Remove cpu_tmp0 as a global
/*0  */ static inline void gen_op_eval_fbo(TCGv dst, TCGv src,        // (3) 0.1279
/*2  */                                     unsigned int fcc_offset)  // (0) 0.2442
/*4  */ {                                                             // (6) 0.005814
/*6  */     gen_mov_reg_FCC0(dst, src, fcc_offset);                   // (2) 0.1395
/*8  */     gen_mov_reg_FCC1(cpu_tmp0, src, fcc_offset);              // (1) 0.1512
/*10 */     tcg_gen_and_tl(dst, dst, cpu_tmp0);                       // (4) 0.1279
/*12 */     tcg_gen_xori_tl(dst, dst, 0x1);                           // (5) 0.1279
/*14 */ }                                                             // (7) 0.005814
