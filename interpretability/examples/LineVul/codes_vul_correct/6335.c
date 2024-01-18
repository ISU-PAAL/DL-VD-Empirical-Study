// commit message qemu@7d1b0095bf (target=1, prob=0.9976158, correct=True): target-arm: Remove ad-hoc leak checking code
/*0 */ static inline void gen_st16(TCGv val, TCGv addr, int index)  // (0) 0.3387
/*2 */ {                                                            // (3) 0.01613
/*4 */     tcg_gen_qemu_st16(val, addr, index);                     // (1) 0.3387
/*6 */     dead_tmp(val);                                           // (2) 0.1452
/*8 */ }                                                            // (4) 0.01613
