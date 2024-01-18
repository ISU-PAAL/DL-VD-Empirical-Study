// commit message qemu@5c55ff99fa (target=0, prob=0.012247711, correct=True): Replace ELF section hack with normal table
/*0 */ static always_inline void gen_store_spr(int reg, TCGv t)      // (1) 0.3276
/*2 */ {                                                             // (2) 0.01724
/*4 */     tcg_gen_st_tl(t, cpu_env, offsetof(CPUState, spr[reg]));  // (0) 0.5
/*6 */ }                                                             // (3) 0.01724
