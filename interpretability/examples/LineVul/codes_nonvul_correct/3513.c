// commit message qemu@bec93d7283 (target=0, prob=0.020996584, correct=True): target-i386: introduce CCPrepare
/*0  */ static void gen_compute_eflags_o(DisasContext *s, TCGv reg)  // (0) 0.2637
/*2  */ {                                                            // (5) 0.01099
/*4  */     gen_compute_eflags(s);                                   // (3) 0.1538
/*6  */     tcg_gen_shri_tl(reg, cpu_cc_src, 11);                    // (1) 0.2527
/*8  */     tcg_gen_andi_tl(reg, reg, 1);                            // (2) 0.1978
/*10 */ }                                                            // (4) 0.01099
